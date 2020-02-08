#pragma once
#include "glm-0.9.9.7/glm/glm.hpp"
#include "glm-0.9.9.7/glm/gtc/matrix_transform.hpp"
#include <vector>
#include "MessagingSystem.h"

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
		Camera2D() {}
		Camera2D(int screenWidth, int screenHeight, glm::vec2 position, float scale);
		~Camera2D();
		glm::mat4 getMatrix() { return mOrthoProj; }

		void init(int screenWidth, int screenHeight, glm::vec2 position, float scale);
	};

	class Camera3D
	{
		

		glm::vec3 mPosition;

		glm::mat4 mPerspectiveProj;
		glm::mat4 mPerspectiveMatrix;

		glm::mat4 mCameraMatrix;
		glm::mat4 mModelMatrix;
		glm::vec3 mCameraRoll;
		glm::vec3 mLookAtPosition;

		std::vector<APlane> mFrustumPlanes;

		bool mFrustum = false;
	
		float mScale;
		float mScreenRatio;
		float mNearClippingDistance;
		float mFarClippingDistance;
		float mFieldOfView;

		float mForward = 0.2f;
		float mBack = -0.2f;
		float mLeft = 0.2f;
		float mRight = -0.2f;
		float mUp = 0.2f;
		float mDown = -0.2f;

		float mVAngle = 0.0f;
		float mHAngle = 0.0f;
		
		float mMouseSensitivity = 0.001f;

		Correspondent mForwardReceiver;
		Correspondent mBackReceiver;
		Correspondent mLeftReceiver;
		Correspondent mRightReceiver;
		Correspondent mUpReceiver;
		Correspondent mDownReceiver;
		Correspondent mLookAtReceiver;

		CorrespondentManager* mManager;
		
	public:
		Camera3D(int screenWidth, int screenHeight, glm::vec3 position, float fieldOfView, float near, float far, glm::vec3 cameraRoll, CorrespondentManager* corrManager, float hAngle, float vAngle);
		~Camera3D();

		glm::mat4 getPerspectiveMatrix() { return mPerspectiveProj; }
		glm::mat4 getCameraMatrix() { return mCameraMatrix; }
		glm::mat4 getModelMatrix() { return mModelMatrix; }
		glm::mat4 getModelCameraMatrix() { return mModelMatrix * mCameraMatrix; }

		glm::vec3 getPosition() { return mPosition; }
		void changePosition(glm::vec3 newPosition);
		void createFrustum();
		void update();
		bool isSphereInView(glm::vec3 centerPoint, float radius);
		bool isBoxInView(std::vector<glm::vec3> points);
	};
}
