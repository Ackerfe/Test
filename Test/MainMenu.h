#pragma once
#include "GraphicsResourceManager.h"
#include "GUI.h"
#include "WindowHandler.h"
#include "Cameras.h"
class MainMenu
{
	Ackerfe::GraphicsResourceManager* mGRM;
	Ackerfe::GUI* mGUI;
	bool mStartGame = false;

	int mScreenWidth;
	int mScreenHeight;
	GLuint mProgramID;
	Ackerfe::Camera2D mCamera;
	GLint mPerspectiveUniformID;
	glm::mat4 mOrthoMatrix;
	Ackerfe::WindowHandler* mWindow;

public:
	void init(Ackerfe::GraphicsResourceManager* GRM, std::string vertShader, std::string fragShader,
		int screenWidth, int screenHeight, 
		glm::vec2 cameraPosition, float cameraZoom, 
		Ackerfe::WindowHandler* window, Ackerfe::GUI* gui);
	void mainMenuLoop();
	void render();
	bool exitGame(const CEGUI::EventArgs &e);
	bool beginGame(const CEGUI::EventArgs &e);
};

