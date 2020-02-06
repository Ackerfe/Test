#include "Cameras.h"
#include <iostream>
namespace Ackerfe
{
	Camera2D::Camera2D(int screenWidth, int screenHeight, glm::vec2 position, float scale) 
		: mScreenWidth(screenWidth), mScreenHeight(screenHeight), mPosition(position), mScale(scale)
	{
		mOrthoMatrix = glm::ortho(0.0f, (float)mScreenWidth, 0.0f, (float)mScreenHeight);

		mOrthoProj = glm::translate(mOrthoMatrix, glm::vec3(mPosition.x, mPosition.y, 0.0f));

		glm::vec3 scaling(mScale, mScale, 0.0f);

		mOrthoProj = glm::scale(glm::mat4(1.0f), scaling) * mOrthoProj;
	}
	Camera2D::~Camera2D()
	{
	}

	void Camera2D::init(int screenWidth, int screenHeight, glm::vec2 position, float scale)
	{
		mScreenWidth = screenWidth;
		mScreenHeight = screenHeight;
		mPosition = position; 
		mScale = scale;

		mOrthoMatrix = glm::ortho(0.0f, (float)mScreenWidth, 0.0f, (float)mScreenHeight);

		mOrthoProj = glm::translate(mOrthoMatrix, glm::vec3(mPosition.x, mPosition.y, 0.0f));

		glm::vec3 scaling(mScale, mScale, 0.0f);

		mOrthoProj = glm::scale(glm::mat4(1.0f), scaling) * mOrthoProj;
	}
	
	Camera3D::Camera3D(int screenWidth, int screenHeight, glm::vec3 position, float fieldOfView, float near, float far, glm::vec3 cameraRoll, CorrespondentManager* corrManager, float hAngle, float vAngle)
		:  mPosition(position), mScreenRatio(screenWidth / screenHeight), mFieldOfView(fieldOfView), mNearClippingDistance(near), mFarClippingDistance(far),  mCameraRoll(cameraRoll), mHAngle(hAngle), mVAngle(vAngle)
	{
		mLookAtPosition = glm::vec3(cos(mVAngle) * sin(mHAngle), sin(mVAngle), cos(mVAngle) * cos(mHAngle));
		
		std::string tempString = "CameraMoveForwardReceiver";
		mForwardReceiver.init(corrManager, tempString);
		tempString = "CameraMoveBackReceiver";
		mBackReceiver.init(corrManager, tempString);
		tempString = "CameraMoveLeftReceiver";
		mLeftReceiver.init(corrManager, tempString);
		tempString = "CameraMoveRightReceiver";
		mRightReceiver.init(corrManager, tempString);
		tempString = "CameraMoveUpReceiver";
		mUpReceiver.init(corrManager, tempString);
		tempString = "CameraMoveDownReceiver";
		mDownReceiver.init(corrManager, tempString);
		tempString = "CameraLookAtReceiver";
		mLookAtReceiver.init(corrManager, tempString);
		update();
	}

	Camera3D::~Camera3D()
	{
		
	}
	void Camera3D::changePosition(glm::vec3 newPosition)
	{
		mPosition = newPosition;
		update();
	}

	void Camera3D::createFrustum()
	{
		mFrustumPlanes.clear();
		float nearFrustumHeight = glm::tan(mFieldOfView/2) * mNearClippingDistance;
		float nearFrustumWidth = nearFrustumHeight * mScreenRatio;
		float farFrustumHeight = glm::tan(mFieldOfView/2) * mFarClippingDistance;
		float farFrustumWidth = farFrustumHeight * mScreenRatio;

		glm::vec3 viewDirection = glm::normalize(mLookAtPosition - mPosition);
		glm::vec3 farClippingCenter = mPosition + viewDirection * mFarClippingDistance;
		glm::vec3 nearClippingCenter = mPosition + viewDirection * mNearClippingDistance;

		glm::vec3 cameraRight = glm::normalize(glm::cross(viewDirection, mCameraRoll));
		glm::vec3 cameraUp = glm::normalize(glm::cross(viewDirection, cameraRight));

		//Near Clipping Frustum Plane
		mFrustumPlanes.push_back(APlane(viewDirection, glm::dot(-viewDirection, nearClippingCenter)));

		//Far Clipping Frustum Plane
		mFrustumPlanes.push_back(APlane(-viewDirection, glm::dot(viewDirection, farClippingCenter)));

		//Right Clipping Frustum Plane
		glm::vec3 planeNormal = -glm::normalize(glm::cross(cameraUp, (farClippingCenter + cameraRight * farFrustumWidth) - mPosition));
		mFrustumPlanes.push_back(APlane(planeNormal, glm::dot(-planeNormal, mPosition)));

		//Left Clipping Frustum Plane
		planeNormal = glm::normalize(glm::cross(cameraUp, (farClippingCenter - cameraRight * farFrustumWidth) - mPosition));
		mFrustumPlanes.push_back(APlane(planeNormal, glm::dot(-planeNormal, mPosition)));

		//Top Clipping Frustum Plane
		planeNormal = -glm::normalize(glm::cross(cameraRight, (farClippingCenter - cameraUp * farFrustumHeight) - mPosition));
		mFrustumPlanes.push_back(APlane(planeNormal, glm::dot(-planeNormal, mPosition)));

		//Bottom Clipping Frustum Plane
		planeNormal = glm::normalize(glm::cross(cameraRight, (farClippingCenter + cameraUp * farFrustumHeight) - mPosition));
		mFrustumPlanes.push_back(APlane(planeNormal, glm::dot(-planeNormal, mPosition)));

		mFrustum = true;

	}

	bool Camera3D::isSphereInView(glm::vec3 centerPoint, float radius)
	{
		if (!mFrustum)
			createFrustum();

		if (mFrustumPlanes[0].getDistance(centerPoint) < -radius)
			return false;

		if (mFrustumPlanes[1].getDistance(centerPoint) < -radius)
			return false;

		if (mFrustumPlanes[2].getDistance(centerPoint) < -radius)
			return false;

		if (mFrustumPlanes[3].getDistance(centerPoint) < -radius)
			return false;

		if (mFrustumPlanes[4].getDistance(centerPoint) < -radius)
			return false;

		if (mFrustumPlanes[5].getDistance(centerPoint) < -radius)
			return false;
		
		return true;
	}

	bool Camera3D::isBoxInView(std::vector<glm::vec3> points)
	{
		bool isThereAGoodPoint = false;
		unsigned int iterator = 0;

		if (!mFrustum)
			createFrustum();

		for (size_t i = 0; i < mFrustumPlanes.size(); i++)
		{
			while (!isThereAGoodPoint && iterator < 8)
			{
				if (mFrustumPlanes[i].getDistance(points[iterator]) > 0)
					isThereAGoodPoint = true;
		
				iterator++;
			}
			iterator = 0;
			if (!isThereAGoodPoint)
			{
				std::cout << "false";
				return false;
			}
			isThereAGoodPoint = false;
		}
		
		return true;
	}

	void Camera3D::update()
	{	
		if (mForwardReceiver.getMessage())
		{
			mPosition += mLookAtPosition * mForward;
			mForwardReceiver.clearMessage();
		}
		if (mBackReceiver.getMessage())
		{
			mPosition += mLookAtPosition * mBack;
			mBackReceiver.clearMessage();
		}
		if (mLeftReceiver.getMessage())
		{
			mPosition += mLeft * glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), mLookAtPosition);
			mLeftReceiver.clearMessage();
		}
		if (mRightReceiver.getMessage())
		{
			mPosition += mRight * glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), mLookAtPosition);
			mRightReceiver.clearMessage();
		}
		if (mUpReceiver.getMessage())
		{
			mPosition += glm::vec3(0.0f, mUp, 0.0f);
			mUpReceiver.clearMessage();
		}
		if (mDownReceiver.getMessage())
		{
			mPosition += glm::vec3(0.0f, mDown, 0.0f);
			mDownReceiver.clearMessage();
		}
		if (mLookAtReceiver.getMessage())
		{
			glm::vec2 mouseCoordsChange = mLookAtReceiver.getMouseMessage();
			mHAngle -= mouseCoordsChange.x * mMouseSensitivity;
			mVAngle -= mouseCoordsChange.y * mMouseSensitivity;
			mLookAtPosition = glm::vec3(cos(mVAngle) * sin(mHAngle), sin(mVAngle), cos(mVAngle) * cos(mHAngle));
			mLookAtReceiver.clearMessage();
		}

		mPerspectiveMatrix = glm::perspective(glm::radians(mFieldOfView), mScreenRatio, mNearClippingDistance, mFarClippingDistance);

		mCameraMatrix = glm::lookAt(mPosition, mPosition + mLookAtPosition, glm::vec3(0.0f, 1.0f, 0.0f));

		mModelMatrix = glm::mat4(1.0f);

		mPerspectiveProj = mPerspectiveMatrix * mCameraMatrix * mModelMatrix;

		
	}
}