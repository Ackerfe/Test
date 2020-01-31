#include "GameLogo.h"

void GameLogo::init(std::string vertShader, std::string fragShader, int screenWidth, int screenHeight, glm::vec2 cameraPosition, float cameraZoom, Ackerfe::WindowHandler* window)
{
	mProgramID = Ackerfe::compileLinkSimpleShaders(vertShader, fragShader);
	mPerspectiveUniformID = glGetUniformLocation(mProgramID, "Perspective");
	mCamera.init(screenWidth, screenHeight, cameraPosition, cameraZoom);
	mOrthoMatrix = mCamera.getMatrix();
	mScreenWidth = screenWidth;
	mScreenHeight = screenHeight;
	mWindow = window;
	mMultiSprite.init();
}

void GameLogo::logoUpdateRenderLoop()
{
	glDisable(GL_DEPTH_TEST);

	GLuint BackGroundTextureID = Ackerfe::loadPng("Texture/LogoState/LogoBackground.png");

	float quarterScreenHeight = mScreenHeight / 4.0f;
	float threeQuartersScreenHeight = mScreenHeight - quarterScreenHeight;

	mMultiSprite.addSprite(BackGroundTextureID, 0.0f,
		Ackerfe::Vertex(0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, Ackerfe::ColourRGBA8(255, 255, 255, 255)),
		Ackerfe::Vertex(0.0f, mScreenHeight, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, Ackerfe::ColourRGBA8(255, 255, 255, 255)),
		Ackerfe::Vertex(mScreenWidth, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, Ackerfe::ColourRGBA8(255, 255, 255, 255)),
		Ackerfe::Vertex(mScreenWidth, mScreenHeight, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, Ackerfe::ColourRGBA8(255, 255, 255, 255)));

	mMultiSprite.addSprite(BackGroundTextureID, 0.0f,
		Ackerfe::Vertex(0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, Ackerfe::ColourRGBA8(0, 0, 0, 255)),
		Ackerfe::Vertex(0.0f, quarterScreenHeight, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, Ackerfe::ColourRGBA8(0, 0, 0, 255)),
		Ackerfe::Vertex(mScreenWidth, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, Ackerfe::ColourRGBA8(0, 0, 0, 255)),
		Ackerfe::Vertex(mScreenWidth, quarterScreenHeight, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, Ackerfe::ColourRGBA8(0, 0, 0, 255)));

	mMultiSprite.addSprite(BackGroundTextureID, 0.0f,
		Ackerfe::Vertex(0.0f, threeQuartersScreenHeight, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, Ackerfe::ColourRGBA8(0, 0, 0, 255)),
		Ackerfe::Vertex(0.0f, mScreenHeight, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, Ackerfe::ColourRGBA8(0, 0, 0, 255)),
		Ackerfe::Vertex(mScreenWidth, threeQuartersScreenHeight, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, Ackerfe::ColourRGBA8(0, 0, 0, 255)),
		Ackerfe::Vertex(mScreenWidth, mScreenHeight, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, Ackerfe::ColourRGBA8(0, 0, 0, 255)));

	mMultiSprite.addSprite(Ackerfe::loadPng("Texture/test.png"), 0.0f,
		Ackerfe::Vertex(quarterScreenHeight, quarterScreenHeight, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, Ackerfe::ColourRGBA8(255, 255, 255, 255)),
		Ackerfe::Vertex(quarterScreenHeight, threeQuartersScreenHeight, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, Ackerfe::ColourRGBA8(255, 255, 255, 255)),
		Ackerfe::Vertex(threeQuartersScreenHeight, quarterScreenHeight, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, Ackerfe::ColourRGBA8(255, 255, 255, 255)),
		Ackerfe::Vertex(threeQuartersScreenHeight, threeQuartersScreenHeight, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, Ackerfe::ColourRGBA8(255, 255, 255, 255)));

	mMultiSprite.prepareBatches();

	int startTime = SDL_GetTicks();
	int currentTime = startTime;
	int logoLength = 5000;
	int logoTime = currentTime - startTime;

	while (logoTime < logoLength)
	{
		if (logoTime < 4000)
		{
			mMultiSprite.setSpriteAlpha(3, pow((logoTime/251), 2.0f));
			mMultiSprite.prepareBatches();
			render();
		}

		else
		{
			mMultiSprite.setSpriteAlpha(3, 255);
			mMultiSprite.prepareBatches();
			render();
		}
		currentTime = SDL_GetTicks();
		logoTime = currentTime - startTime;
	}

	glEnable(GL_DEPTH_TEST);
}

void GameLogo::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(mProgramID);

	glUniformMatrix4fv(mPerspectiveUniformID, 1, GL_FALSE, &mOrthoMatrix[0][0]);


	mMultiSprite.renderBatches();

	glUseProgram(0);

	mWindow->swapBuffer();
}
