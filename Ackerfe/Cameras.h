#pragma once
#include "glm-0.9.9.7/glm/glm.hpp"
#include "glm-0.9.9.7/glm/gtc/matrix_transform.hpp"
#include <vector>
#include "MessagingSystem.h"
#include "ACollision.h"

namespace Ackerfe
{
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
		ACollCnvx mFrustum;

		glm::vec3 mPosition;

		glm::mat4 mPerspectiveProj;
		glm::mat4 mPerspectiveMatrix;

		glm::mat4 mCameraMatrix;
		glm::mat4 mModelMatrix;
		glm::vec3 mCameraRoll;
		glm::vec3 mLookAtPosition;
	
		float mScale;
		float mScreenRatio;
		float mNearClippingDistance;
		float mFarClippingDistance;
		float mFieldOfView;

		float mForward = 2.6f;
		float mBack = -2.6f;
		float mLeft = 2.6f;
		float mRight = -2.6f;
		float mUp = 2.6f;
		float mDown = -2.6f;

		float mVAngle = 0.0f;
		float mHAngle = 0.0f;
		
		float mMouseSensitivity = 0.05f;

		Correspondent mForwardReceiver;
		Correspondent mBackReceiver;
		Correspondent mLeftReceiver;
		Correspondent mRightReceiver;
		Correspondent mUpReceiver;
		Correspondent mDownReceiver;
		Correspondent mLookAtReceiver;

		CorrespondentManager* mManager;

		ACollSphr mSphr;
		
	public:
		Camera3D(int screenWidth, int screenHeight, glm::vec3 position, float fieldOfView, float near, float far, glm::vec3 cameraRoll, CorrespondentManager* corrManager, float hAngle, float vAngle);
		~Camera3D();

		glm::mat4 getPerspectiveMatrix() { return mPerspectiveProj; }
		glm::mat4 getCameraMatrix() { return mCameraMatrix; }
		glm::mat4 getModelMatrix() { return mModelMatrix; }
		glm::mat4 getProjectionMatrix() { return mPerspectiveMatrix; }
		glm::mat4 getModelCameraMatrix() { return mModelMatrix * mCameraMatrix; }

		glm::vec3 getPosition() { return mPosition; }
		void changePosition(glm::vec3 newPosition);
		void createFrustum();
		void update();

		ACollCnvx* getFrustum() { return &mFrustum; }
		ACollSphr* getSphr() { return &mSphr; }
		
	};
}
