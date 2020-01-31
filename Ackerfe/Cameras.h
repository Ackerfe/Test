#pragma once

#include "glm-0.9.9.7/glm/glm.hpp"
#include "glm-0.9.9.7/glm/gtc/matrix_transform.hpp"
#include <vector>

namespace Ackerfe
{
	class APlane 
	{
		glm::vec3 mNormal;
		float mOriginDistance;

	public:
		APlane() {}
		APlane(glm::vec3 normal, float originDistance): mNormal(normal), mOriginDistance(originDistance) {}
		~APlane() {}

		float getDistance(glm::vec3 position)
		{
			return (glm::dot(mNormal, position) + mOriginDistance);
		}
	};
	class Camera2D
	{
		glm::vec2 mPosition;
		glm::mat4 mOrthoProj;
		glm::mat4 mOrthoMatrix;
		float mScale;
		int mScreenWidth;
		int mScreenHeight;

	public:
		Camera2D(int screenWidth, int screenHeight, glm::vec2 position, float scale);
		~Camera2D();
		glm::mat4 getMatrix() { return mOrthoProj; }
	};

	class Camera3D
	{
		glm::vec3 mPosition;
		glm::mat4 mPerspectiveProj;
		glm::mat4 mPerspectiveMatrix;
		glm::mat4 mCameraMatrix;
		glm::mat4 mModelMatrix;
		float mScale;
		bool mFrustum = false;
		std::vector<APlane> mFrustumPlanes;
		float mScreenRatio;
		float mNearClippingDistance;
		float mFarClippingDistance;
		float mFieldOfView;
		glm::vec3 mCameraRoll;
		glm::vec3 mLookAtPosition;
		void update();
		
	public:
		Camera3D(int screenWidth, int screenHeight, glm::vec3 position, glm::vec3 lookAt, float fieldOfView, float near, float far, glm::vec3 cameraRoll);
		~Camera3D();

		glm::mat4 getPerspectiveMatrix() { return mPerspectiveProj; }
		glm::mat4 getCameraMatrix() { return mCameraMatrix; }
		glm::mat4 getModelMatrix() { return mModelMatrix; }

		glm::vec3 getPosition() { return mPosition; }
		void changePosition(glm::vec3 newPosition);
		void createFrustum();
		bool isSphereInView(glm::vec3 centerPoint, float radius);
		bool isBoxInView(std::vector<glm::vec3> points);
	};
}
