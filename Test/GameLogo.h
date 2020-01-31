#pragma once

#include <math.h>
#include "MultiSprite.h"
#include "SimpleShader.h"
#include "ImageLoad.h"
#include "Cameras.h"
#include "WindowHandler.h"


class GameLogo
{

public:

	void init(std::string vertShader, std::string fragShader, int screenWidth, int screenHeight, glm::vec2 cameraPosition, float cameraZoom, Ackerfe::WindowHandler* window);
	void logoUpdateRenderLoop();
	void render();

private:

	int mScreenWidth;
	int mScreenHeight;
	GLuint mProgramID;
	Ackerfe::Camera2D mCamera;
	Ackerfe::MultiSprite mMultiSprite;
	GLint mPerspectiveUniformID;
	glm::mat4 mOrthoMatrix;
	Ackerfe::WindowHandler* mWindow;
};

