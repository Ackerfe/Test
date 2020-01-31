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
	
	Camera3D::Camera3D(int screenWidth, int screenHeight, glm::vec3 position, glm::vec3 lookAt, float fieldOfView, float near, float far, glm::vec3 cameraRoll)
		:  mPosition(position), mLookAtPosition(lookAt), mScreenRatio(screenWidth / screenHeight), mFieldOfView(fieldOfView), mNearClippingDistance(near), mFarClippingDistance(far),  mCameraRoll(cameraRoll)
	{
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
		mPerspectiveMatrix = glm::perspective(glm::radians(mFieldOfView), mScreenRatio, mNearClippingDistance, mFarClippingDistance);

		mCameraMatrix = glm::lookAt(mPosition, mLookAtPosition, glm::vec3(0.0f, 1.0f, 0.0f));

		mModelMatrix = glm::mat4(1.0f);

		mPerspectiveProj = mPerspectiveMatrix * mCameraMatrix * mModelMatrix;

		
	}
}