#pragma once
#include "GraphicsResourceManager.h"
#include "GUI.h"
#include "WindowHandler.h"
#include "Cameras.h"
#include "InputHandler.h"
#include "AAudio.h"

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
	Ackerfe::InputHandler* mInput = nullptr;
	

public:
	
	void init(Ackerfe::GraphicsResourceManager* GRM, std::string vertShader, std::string fragShader,
		int screenWidth, int screenHeight, 
		glm::vec2 cameraPosition, float cameraZoom, 
		Ackerfe::WindowHandler* window, Ackerfe::GUI* gui, Ackerfe::InputHandler* input);
	void mainMenuLoop();
	void render();
	bool exitGame(const CEGUI::EventArgs &e);
	bool beginGame(const CEGUI::EventArgs &e);
};

