#pragma once

#include "glm-0.9.9.7/glm/glm.hpp"
#include "glm-0.9.9.7/glm/gtc/matrix_transform.hpp"

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
		int mScreenWidth;
		int mScreenHeight;
		
	public:
		Camera3D(int screenWidth, int screenHeight, glm::vec3 position, glm::vec3 lookAt, float fieldOfView, float near, float far);
		~Camera3D();
		glm::mat4 getPerspectiveMatrix() { return mPerspectiveProj; }
		glm::mat4 getCameraMatrix() { return mCameraMatrix; }
		glm::mat4 getModelMatrix() { return mModelMatrix; }

	};
}
