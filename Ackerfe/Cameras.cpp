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
		mSphr.pos = &mPosition;
		mSphr.radius = 5.0f;
		mFrustum.pos = &mPosition;
		createFrustum();

		update();
	}

	Camera3D::~Camera3D()
	{
		
	}
	void Camera3D::changePosition(glm::vec3 newPosition)
	{
		mPosition = newPosition;
		glm::vec3 *temporary = new glm::vec3(newPosition);
		mSphr.pos = temporary;
		
		update();
	}

	void Camera3D::createFrustum()
	{
		mFrustum.planes.clear();
		float nearFrustumHeight = glm::tan(mFieldOfView/2) * mNearClippingDistance;
		float nearFrustumWidth = nearFrustumHeight * mScreenRatio;
		float farFrustumHeight = glm::tan(mFieldOfView/2) * mFarClippingDistance;
		float farFrustumWidth = farFrustumHeight * mScreenRatio;

		glm::vec3 viewDirection = glm::normalize(mLookAtPosition - mPosition);
		glm::vec3 farClippingCenter = mPosition + mLookAtPosition * mFarClippingDistance;
		glm::vec3 nearClippingCenter = mPosition + mLookAtPosition * mNearClippingDistance;

		glm::vec3 cameraRight = glm::normalize(glm::cross(mLookAtPosition, mCameraRoll));
		glm::vec3 cameraUp = glm::normalize(glm::cross(mLookAtPosition, cameraRight));

		//near clipping frustum plane
		mFrustum.planes.push_back(ACollPlane(mLookAtPosition, glm::dot(-mLookAtPosition, nearClippingCenter)));
		/*std::cout << "Near plane normal: " << mFrustum.planes.back().normal.x
			<< ", " << mFrustum.planes.back().normal.y << ". "
			<< mFrustum.planes.back().normal.z << " has offset: "
			<< mFrustum.planes.back().offset << std::endl;*/
			//far clipping frustum plane
		mFrustum.planes.push_back(ACollPlane(-mLookAtPosition, glm::dot(mLookAtPosition, farClippingCenter)));
		/*std::cout << "Far plane normal: " << mFrustum.planes.back().normal.x
			<< ", " << mFrustum.planes.back().normal.y << ". "
			<< mFrustum.planes.back().normal.z << " has offset: "
			<< mFrustum.planes.back().offset << std::endl;*/
			//right clipping frustum plane
		glm::vec3 planeNormal = -glm::normalize(glm::cross(cameraUp, (farClippingCenter + cameraRight * farFrustumWidth) - mPosition));
		mFrustum.planes.push_back(ACollPlane(planeNormal, glm::dot(-planeNormal, mPosition)));
		/*std::cout << "Right plane normal: " << mFrustum.planes.back().normal.x
			<< ", " << mFrustum.planes.back().normal.y << ". "
			<< mFrustum.planes.back().normal.z << " has offset: "
			<< mFrustum.planes.back().offset << std::endl;*/
			//left clipping frustum plane
		planeNormal = glm::normalize(glm::cross(cameraUp, (farClippingCenter - cameraRight * farFrustumWidth) - mPosition));
		mFrustum.planes.push_back(ACollPlane(planeNormal, glm::dot(-planeNormal, mPosition)));
		/*std::cout << "Left plane normal: " << mFrustum.planes.back().normal.x
			<< ", " << mFrustum.planes.back().normal.y << ". "
			<< mFrustum.planes.back().normal.z << " has offset: "
			<< mFrustum.planes.back().offset << std::endl;*/
			//top clipping frustum plane
		planeNormal = -glm::normalize(glm::cross(cameraRight, (farClippingCenter - cameraUp * farFrustumHeight) - mPosition));
		mFrustum.planes.push_back(ACollPlane(planeNormal, glm::dot(-planeNormal, mPosition)));
		/*std::cout << "Top plane normal: " << mFrustum.planes.back().normal.x
			<< ", " << mFrustum.planes.back().normal.y << ". "
			<< mFrustum.planes.back().normal.z << " has offset: "
			<< mFrustum.planes.back().offset << std::endl;*/
			//bottom clipping frustum plane
		planeNormal = glm::normalize(glm::cross(cameraRight, (farClippingCenter + cameraUp * farFrustumHeight) - mPosition));
		mFrustum.planes.push_back(ACollPlane(planeNormal, glm::dot(-planeNormal, mPosition)));
		/*std::cout << "Bottom plane normal: " << mFrustum.planes.back().normal.x
			<< ", " << mFrustum.planes.back().normal.y << ". "
			<< mFrustum.planes.back().normal.z << " has offset: "
			<< mFrustum.planes.back().offset << std::endl;*/
	}

	void Camera3D::update()
	{	
		std::cout << "      " << mSphr.pos->x << "      " << mSphr.pos->y << "      " << mSphr.pos->z;
		if (mLookAtReceiver.getMessage())
		{
			glm::vec2 mouseCoordsChange = mLookAtReceiver.getMouseMessage();
			mHAngle -= mouseCoordsChange.x * mMouseSensitivity;
			mVAngle -= glm::mod(mouseCoordsChange.y * mMouseSensitivity, 360.0f);
			mLookAtPosition = glm::vec3(cos(glm::radians(mVAngle)) * sin(glm::radians(mHAngle)), sin(glm::radians(mVAngle)), cos(glm::radians(mVAngle)) * cos(glm::radians(mHAngle)));
			mLookAtReceiver.clearMessage();
			createFrustum();
		}

		if (mForwardReceiver.getMessage())
		{
			mPosition += mLookAtPosition * mForward;
			mForwardReceiver.clearMessage();
			createFrustum();
		}

		if (mBackReceiver.getMessage())
		{
			mPosition += mLookAtPosition * mBack;
			mBackReceiver.clearMessage();
			createFrustum();
		}

		if (mLeftReceiver.getMessage())
		{
			mPosition += mLeft * glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), mLookAtPosition);
			mLeftReceiver.clearMessage();
			createFrustum();
		}

		if (mRightReceiver.getMessage())
		{
			mPosition += mRight * glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), mLookAtPosition);
			mRightReceiver.clearMessage();
			createFrustum();
		}

		if (mUpReceiver.getMessage())
		{
			mPosition += glm::vec3(0.0f, mUp, 0.0f);
			mUpReceiver.clearMessage();
			createFrustum();
		}

		if (mDownReceiver.getMessage())
		{
			mPosition += glm::vec3(0.0f, mDown, 0.0f);
			mDownReceiver.clearMessage();
			createFrustum();
		}

		mPerspectiveMatrix = glm::perspective(glm::radians(mFieldOfView), mScreenRatio, mNearClippingDistance, mFarClippingDistance);
		mCameraMatrix = glm::lookAt(mPosition, mPosition + mLookAtPosition, glm::vec3(0.0f, 1.0f, 0.0f));
		mModelMatrix = glm::mat4(1.0f);
		mPerspectiveProj = mPerspectiveMatrix * mCameraMatrix * mModelMatrix;
		glm::vec3 *temporary = new glm::vec3(mPosition);
		mSphr.pos = temporary;

		
	}
}