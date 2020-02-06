#include <InputHandler.h>
#include <WindowHandler.h>
#include <SDL/SDL.h>
#include "Triangle.h"
#include "SimpleShader.h"
#include "Square.h"
#include "ErrHandler.h"
#include "MultiSprite.h"
#include "ImageLoad.h"
#include "SpriteFont.h"
#include "Acube.h"
#include "SpatialSceneGraphOct.h"
#include "GameLogo.h"
#include "GraphicsResourceManager.h"
#include "GUI.h"
#include "MainMenu.h"
#include "AAudio.h"
#include "MessagingSystem.h"


/*temporary*/
#include <iostream>
#include "Cameras.h"



void simpleFunction()
{
	std::cout << "Key Pressed" << std::endl;
}

void simpleButtonFunction(glm::vec2 mousecoords)
{
	std::cout << "Button Pressed" << std::endl;	
}


int main(int argc, char** argv)
{
	
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	float red = 0.0f;
	float green = 0.0f;
	float blue = 0.0f;
	Ackerfe::WindowHandler newWindow;
	newWindow.createWindow("Window", 512, 512, 0);

	Ackerfe::GraphicsResourceManager graphics;

	Ackerfe::CorrespondentManager manager;
	manager.firstInit();
	

	GameLogo gameLogo;
	gameLogo.init("Logo.vert", "Logo.frag", 512, 512, glm::vec2 (0.0f,0.0f), 1.0f, &newWindow, &graphics);
	gameLogo.logoUpdateRenderLoop();

	std::string guiResource = "GUI";
	Ackerfe::GUI gui;
	gui.init(guiResource, &manager);

	Ackerfe::InputHandler newInput;
	newInput.init(&manager);

	/*Ackerfe::Correspondent wKey;
	std::string tempString = "wKey";
	wKey.init(&manager, tempString);
	Ackerfe::Correspondent sKey;
	tempString = "sKey";
	sKey.init(&manager, tempString);
	Ackerfe::Correspondent aKey;
	tempString = "aKey";
	aKey.init(&manager, tempString);
	Ackerfe::Correspondent dKey;
	tempString = "dKey";
	dKey.init(&manager, tempString);
	Ackerfe::Correspondent leftShiftKey;
	tempString = "leftShiftKey";
	leftShiftKey.init(&manager, tempString);
	Ackerfe::Correspondent spacebarKey;
	tempString = "spacebarKey";
	spacebarKey.init(&manager, tempString);
	Ackerfe::Correspondent leftMouse;
	tempString = "leftMouse";
	leftMouse.init(&manager, tempString);*/
	manager.init();

	MainMenu mainMenu;
	mainMenu.init(&graphics, "Logo.vert", "Logo.frag", 512, 512, glm::vec2(0.0f, 0.0f), 1.0f, &newWindow, &gui, &newInput);
	mainMenu.mainMenuLoop();

	Ackerfe::AAudio audio;
	std::string tempString = "SoundMap1.txt";
	audio.init(tempString, &manager);
	audio.update();

	bool doQuit = false;

	Ackerfe::Square square("Texture/test.png");
	Ackerfe::Triangle triangle;

	GLuint programID = Ackerfe::compileLinkSimpleShaders("TextureVert.vert", "TextureFrag.frag");
	GLuint secondProgramID = Ackerfe::compileLinkSimpleShaders("SimpleVert.vert", "SimpleFrag.frag");

	GLint shaderPerspectiveID = glGetUniformLocation(programID, "Perspective");
	GLint shaderCameraMatrixID = glGetUniformLocation(programID, "CameraMatrix");
	GLint shaderModelMatrixID = glGetUniformLocation(programID, "ModelMatrix");
	GLint shaderLightPositionID = glGetUniformLocation(programID, "LightPosition");
	GLint shaderModelCameraMatrixID = glGetUniformLocation(programID, "ModelCameraMatrix");
	GLint shaderLightColourID = glGetUniformLocation(programID, "LightColour");
	GLint shaderLightIntensityID = glGetUniformLocation(programID, "LightIntensity");


	//Ackerfe::MultiSprite multiSprite3;
	//multiSprite3.init();
	
	Ackerfe::Camera2D camera2D(512, 512, glm::vec2(0.0f,0.0f), 1.0f);
	

	Ackerfe::Camera3D camera3D(512, 512, glm::vec3(53.0f,53.0f,53.0f), 45.0f, 2.0f, 30.0f, glm::vec3(0.0f, 1.0f, 0.0f), &manager, 1.0f, 0.0f);

	 

	/*Ackerfe::MultiSprite multiSprite;
	multiSprite.init();
	
	Ackerfe::Vertex test = Ackerfe::Vertex(0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, Ackerfe::ColourRGBA8(255, 100, 100, 255));
	Ackerfe::Vertex test2 = Ackerfe::Vertex(0.0f, 100.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, Ackerfe::ColourRGBA8(255, 100, 100, 255));
	Ackerfe::Vertex test3 = Ackerfe::Vertex(100.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, Ackerfe::ColourRGBA8(255, 100, 100, 255));
	Ackerfe::Vertex test4 = Ackerfe::Vertex(100.0f, 100.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, Ackerfe::ColourRGBA8(255, 100, 100, 255));
	GLuint textureID = Ackerfe::loadPng("Texture/test.png");
	GLuint textureID2 = Ackerfe::loadBmp("Texture/TWO.bmp");

	multiSprite.addSprite(textureID, 0.0f,
	Ackerfe::Vertex(0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, Ackerfe::ColourRGBA8(255, 100, 100, 255)),
	Ackerfe::Vertex(0.0f, 100.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, Ackerfe::ColourRGBA8(255, 100, 100, 255)),
	Ackerfe::Vertex(100.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, Ackerfe::ColourRGBA8(255, 100, 100, 255)),
	Ackerfe::Vertex(100.0f, 100.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, Ackerfe::ColourRGBA8(255, 100, 100, 255)));

	
	multiSprite.prepareBatches();*/

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


	for (float i=-50.0f; i<50.0f; i+=5.0f)
	{
		for (float j=-50.0f; j<50.0f; j+=5.0f)
		{
			for (float k = -50.0f; k < 50.0f; k += 5.0f) 
				spatialGraph.addEntityToGraph(new Ackerfe::ACube(glm::vec3(i, j, k), 1.0f, "Texture/purple.png", "Texture/green.png", "Texture/blue.png", "Texture/orange.png", "Texture/cyan.png", "Texture/yellow.png", &multiSprite2));

			
		}
	}
	
	for (unsigned int i = 0; i < sceneGraphOctStack.size(); i++)
	{
		if (camera3D.isBoxInView(sceneGraphOctStack[i]->getPoints()))
			sceneGraphOctStack[i]->addToStack(&spatialEntityStack, &sceneGraphOctStack);
	}

	for (unsigned int i = 0; i < spatialEntityStack.size(); i++)
	{
		if (camera3D.isSphereInView(spatialEntityStack[i]->getPosition(), spatialEntityStack[i]->getCollisionRadius())) {
			spatialEntityStack[i]->renderEntity();
		}

	}
	
	

	


	multiSprite2.prepareBatches();
	
	
	while (!doQuit) 
	{
		//audio.update();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(programID);
		//square.textureDraw();
		//glUniformMatrix4fv(shaderPerspectiveID, 1, GL_FALSE, &ortho[0][0]);
		//multiSprite3.renderBatches();
		//multiSprite.renderBatches();
	
		glUniformMatrix4fv(shaderPerspectiveID, 1, GL_FALSE, &camera3D.getPerspectiveMatrix()[0][0]);
		glUniformMatrix4fv(shaderModelMatrixID, 1, GL_FALSE, &camera3D.getModelMatrix()[0][0]);
		glUniformMatrix4fv(shaderCameraMatrixID, 1, GL_FALSE, &camera3D.getCameraMatrix()[0][0]);
		glUniformMatrix4fv(shaderModelCameraMatrixID, 1, GL_FALSE, &camera3D.getModelCameraMatrix()[0][0]);

		glUniform3f(shaderLightPositionID, 45.0f, 45.5, 45.5f);
		glUniform3f(shaderLightColourID, 0.5f, 1.0f, 0.5f);
		glUniform1f(shaderLightIntensityID, 450.5f);
		

		multiSprite2.renderBatches();
	
		//multiSprite3.renderBatches();
		//glUseProgram(secondProgramID);
		glUseProgram(0);
		
		newInput.inputQueue();
		newWindow.swapBuffer();
		
			
	}
	return 0;
}

