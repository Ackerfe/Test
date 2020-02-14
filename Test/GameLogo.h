#pragma once

#include <math.h>
#include "GraphicsResourceManager.h"
#include "SimpleShader.h"
#include "ImageLoad.h"
#include "Cameras.h"
#include "WindowHandler.h"
#include "OSInterface.h"


class GameLogo
{

public:

	void init(std::string vertShader, std::string fragShader, int screenWidth, int screenHeight, glm::vec2 cameraPosition, float cameraZoom, Ackerfe::OSInterface* window, Ackerfe::GraphicsResourceManager* graphics);
	void logoUpdateRenderLoop();
	void render();

private:

	int mScreenWidth;
	int mScreenHeight;
	GLuint mProgramID;
	Ackerfe::Camera2D mCamera;
	Ackerfe::GraphicsResourceManager* mGraphics;
	GLint mPerspectiveUniformID;
	glm::mat4 mOrthoMatrix;
	Ackerfe::OSInterface* mWindow;
};

