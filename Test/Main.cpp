#include"InputHandler.h"
#include"WindowHandler.h"
#include"InitFileReadWrite.h"
#include<SDL/SDL.h>
#include"Triangle.h"
#include"SimpleShader.h"
#include"Square.h"
#include"MultiSprite.h"
#include"imageLoad.h"
#include"Cameras.h"
#include"SpriteFont.h"
#include"ACube.h"
#include"SpatialSceneGraphOct.h"
#include "GameLogo.h"
#include "GraphicsResourceManager.h"
#include "GUI.h"
#include "MainMenu.h"
#include "AAudio.h"
#include "MessagingSystem.h"

/*temporarily include iostream*/
#include<iostream>

int main(int argc, char** argv)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	Ackerfe::WindowHandler newWindow;
	newWindow.createWindow("Window", 512, 512, 0);

	Ackerfe::GraphicsResourceManager graphics;

	Ackerfe::CorrespondentManager manager;
	manager.init();

	GameLogo gameLogo;
	gameLogo.init("Logo.vert", "Logo.frag", 512, 512, glm::vec2(0.0f, 0.0f), 1.0f, &newWindow, &graphics);
	gameLogo.logoUpdateRenderLoop();

	Ackerfe::GUI gui;
	gui.init("GUI", &manager);

	Ackerfe::InputHandler newInput;
	newInput.init(&manager);

	MainMenu mainMenu;
	mainMenu.init(&graphics, "Logo.vert", "Logo.frag", 512, 512, glm::vec2(0.0f, 0.0f), 1.0f, &newWindow, &gui, &newInput);
	mainMenu.mainMenuLoop();

	SDL_SetRelativeMouseMode(SDL_TRUE);

	Ackerfe::AAudio audio;
	std::string tempString = "SoundMap1.txt";
	audio.init(tempString, &manager);

	bool doQuit = false;

	Ackerfe::Square triangle("Texture/test.png");
	Ackerfe::Triangle square;

	GLuint programID = Ackerfe::compileLinkSimpleShaders("TextureVert.vert", "TextureFrag.frag");
	GLuint secondProgramID = Ackerfe::compileLinkSimpleShaders("SimpleVert.vert", "SimpleFrag.frag");

	GLint shaderPerspectiveID = glGetUniformLocation(programID, "Perspective");
	GLint shaderCameraMatrixID = glGetUniformLocation(programID, "CameraMatrix");
	GLint shaderModelMatrixID = glGetUniformLocation(programID, "ModelMatrix");
	GLint shaderLightPositionID = glGetUniformLocation(programID, "LightPosition");
	GLint shaderModelCameraMatrixID = glGetUniformLocation(programID, "ModelCameraMatrix");
	GLint shaderLightColourID = glGetUniformLocation(programID, "LightColour");
	GLint shaderLightIntensityID = glGetUniformLocation(programID, "LightIntensity");

	Ackerfe::MultiSprite multiSprite3;
	multiSprite3.init();

	Ackerfe::SpriteFont spriteFont("Fonts/ThreSixt_2.ttf", 64);
	char buffer[256];
	sprintf_s(buffer, "Test String");
	spriteFont.draw(multiSprite3, buffer, glm::vec2(0.0f, 0.0f), glm::vec2(0.01f), 0.0f, Ackerfe::ColourRGBA8(255, 255, 255, 255));

	Ackerfe::Camera2D camera2D(512, 512, glm::vec2(0.0f, 0.0f), 1.0f);
	glm::mat4 ortho = camera2D.getMatrix();
	Ackerfe::Camera3D camera3D(512, 512, glm::vec3(53.0f, 53.0f, 53.0f), 40.0f, 2.0f, 30.0f, glm::vec3(0.0f, 1.0f, 0.0f), &manager, 1.0f, 0.0f);

	Ackerfe::MultiSprite multiSprite;
	multiSprite.init();

	multiSprite.addSprite(Ackerfe::loadPng("Texture/test.png"), 0.0f,
		Ackerfe::Vertex(0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, Ackerfe::ColourRGBA8(255, 100, 100, 255)),
		Ackerfe::Vertex(0.0f, 100.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, Ackerfe::ColourRGBA8(255, 100, 100, 255)),
		Ackerfe::Vertex(100.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, Ackerfe::ColourRGBA8(255, 100, 100, 255)),
		Ackerfe::Vertex(100.0f, 100.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, Ackerfe::ColourRGBA8(255, 100, 100, 255)));

	multiSprite.prepareBatches();


	Ackerfe::MultiSprite multiSprite2;
	multiSprite2.init();

	std::vector<Ackerfe::SpatialSceneGraphOct*> sceneGraphOctStack;
	std::vector<Ackerfe::SpatialEntity*> spatialEntityStack;
	float minSpace = -100.0f;
	float maxSpace = 100.0f;
	Ackerfe::SpatialSceneGraphOct spatialGraph(minSpace, maxSpace, minSpace, maxSpace, minSpace, maxSpace);
	spatialGraph.createChildren();
	sceneGraphOctStack.push_back(&spatialGraph);

	std::vector<Ackerfe::ACube> cubes;

	for (float i = 10; i < 50; i += 5)
	{
		for (float j = 10; j < 50; j += 5)
		{
			for (float k = 10; k < 50; k += 5)
			{
				spatialGraph.addEntityToGraph(new Ackerfe::ACube(glm::vec3(i, j, k), 1.0f, "Texture/cyan.png", "Texture/green.png", "Texture/blue.png",
					"Texture/purple.png", "Texture/orange.png", "Texture/yellow.png", &multiSprite2));
			}
		}
	}
	for (unsigned int i = 0; i < sceneGraphOctStack.size(); i++)
	{
		if (camera3D.isBoxInView(sceneGraphOctStack[i]->getPoints()))
		{
			sceneGraphOctStack[i]->addToStack(&spatialEntityStack, &sceneGraphOctStack);
		}
	}

	for (unsigned int i = 0; i < spatialEntityStack.size(); i++)
	{
		if (camera3D.isSphereInView(spatialEntityStack[i]->getPosition(), spatialEntityStack[i]->getCollisionRadius()))
		{
			spatialEntityStack[i]->renderEntity();
		}
	}

	multiSprite2.prepareBatches();
	multiSprite3.prepareBatches();

	while (!doQuit)
	{
		audio.update();
		camera3D.update();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(programID);
		//triangle.textureDraw();
		glUniformMatrix4fv(shaderPerspectiveID, 1, GL_FALSE, &ortho[0][0]);
		//multiSprite3.renderBatches();
		//multiSprite.renderBatches();
		glUniformMatrix4fv(shaderPerspectiveID, 1, GL_FALSE, &camera3D.getPerspectiveMatrix()[0][0]);
		glUniformMatrix4fv(shaderModelMatrixID, 1, GL_FALSE, &camera3D.getModelMatrix()[0][0]);
		glUniformMatrix4fv(shaderCameraMatrixID, 1, GL_FALSE, &camera3D.getCameraMatrix()[0][0]);
		glUniformMatrix4fv(shaderModelCameraMatrixID, 1, GL_FALSE, &camera3D.getModelCameraMatrix()[0][0]);
		glUniform3f(shaderLightPositionID, 53.0f, 53.0f, 53.0f);
		glUniform3f(shaderLightColourID, 1.0f, 1.0f, 1.0f);
		glUniform1f(shaderLightIntensityID, 500.0f);
		//multiSprite3.renderBatches();
		multiSprite2.renderBatches();
		glUseProgram(secondProgramID);
		//square.draw();
		glUseProgram(0);
		newInput.inputQueue();
		newWindow.swapBuffer();
	}

	return 0;
}