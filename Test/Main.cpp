#include "InputHandler.h"
#include "InitFileReadWrite.h"
#include "OSInterface.h"
#include "Triangle.h"
#include "SimpleShader.h"
#include "Square.h"
#include "MultiSprite.h"
#include "imageLoad.h"
#include "Cameras.h"
#include "SpriteFont.h"
#include "ACube.h"
#include "SpatialSceneGraphOct.h"
#include "GameLogo.h"
#include "GraphicsResourceManager.h"
#include "GUI.h"
#include "MainMenu.h"
#include "AAudio.h"
#include "MessagingSystem.h"
#include "ACollision.h"
#include "ErrHandler.h"
#include "AMeshRenderer.h"
#include "Particles.h"
#include "Skybox.h"
#include <random>
#include "InitShaders.h"
#include "Level1.h"


/*temporarily include iostream*/
#include <iostream>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm-0.9.9.7/glm/gtc/quaternion.hpp>
#include <glm-0.9.9.7/glm/gtx/quaternion.hpp>
#include <glm-0.9.9.7/glm/gtx/euler_angles.hpp>
#include <glm-0.9.9.7/glm/gtc/type_ptr.hpp>

int main(int argc, char** argv)
{
	Ackerfe::OSInterface osInterface;
	osInterface.init();
	osInterface.createWindow("Window", 512, 512, 0);

	Ackerfe::GraphicsResourceManager graphics;

	Ackerfe::CorrespondentManager manager;
	manager.init();

	Ackerfe::Correspondent quitCorrespondent;
	std::string corrString = "QuitGame";
	quitCorrespondent.init(&manager, corrString);

	GameLogo gameLogo;
	gameLogo.init("Logo.vert", "Logo.frag", 512, 512, glm::vec2(0.0f, 0.0f), 1.0f, &osInterface, &graphics);
	gameLogo.logoUpdateRenderLoop();

	Ackerfe::GUI gui;
	gui.init("GUI", &manager, &osInterface);

	Ackerfe::InputHandler newInput;
	newInput.init(&manager, &osInterface);

	MainMenu mainMenu;
	mainMenu.init(&graphics, "Logo.vert", "Logo.frag", 512, 512, glm::vec2(0.0f, 0.0f), 1.0f, &osInterface, &gui, &newInput);
	mainMenu.mainMenuLoop();

	Ackerfe::relativeMouseMotionToggle();

	Ackerfe::AAudio audio;
	std::string tempString = "SoundMap1.txt";
	audio.init(tempString, &manager);

	bool doQuit = false;


	GLuint programID = Ackerfe::compileLinkSimpleShaders("TextureVert.vert", "TextureFrag.frag");
	GLuint secondProgramID = Ackerfe::compileLinkSimpleShaders("SimpleVert.vert", "SimpleFrag.frag");

	GLint shaderPerspectiveID = glGetUniformLocation(programID, "Perspective");
	GLint shaderCameraMatrixID = glGetUniformLocation(programID, "CameraMatrix");
	GLint shaderModelMatrixID = glGetUniformLocation(programID, "ModelMatrix");
	GLint shaderLightPositionID = glGetUniformLocation(programID, "LightPosition");
	GLint shaderModelCameraMatrixID = glGetUniformLocation(programID, "ModelCameraMatrix");
	GLint shaderLightColourID = glGetUniformLocation(programID, "LightColour");
	GLint shaderLightIntensityID = glGetUniformLocation(programID, "LightIntensity");

	Ackerfe::InitShaders shaderSet;
	shaderSet.init();

	Ackerfe::Camera2D camera2D(512, 512, glm::vec2(0.0f, 0.0f), 1.0f);
	glm::mat4 ortho = camera2D.getMatrix();

	Ackerfe::Camera3D camera3D(512, 512, glm::vec3(0.0f, 0.0f, 0.0f),
		45.0f, 1.0f, 10000.0f, glm::vec3(0.0f, 1.0f, 0.0f), &manager, 1.57f, 0.0f);

	Ackerfe::Camera3D cameraCheck(512, 512, glm::vec3(0.0f, 0.0f, 0.0f),
		45.0f, 1.0f, 20000.0f, glm::vec3(0.0f, 1.0f, 0.0f), &manager, -1.57f, 0.0f);

	Ackerfe::MultiSprite multiSprite2;
	multiSprite2.init();

	std::vector<Ackerfe::SpatialSceneGraphOct*> sceneGraphOctStack;
	std::vector<Ackerfe::SpatialEntity*> spatialEntityStack;
	float minSpace = -1000.0f;
	float maxSpace = 1000.0f;
	Ackerfe::SpatialSceneGraphOct spatialGraph(minSpace, maxSpace, minSpace, maxSpace, minSpace, maxSpace);
	spatialGraph.createChildren();
	sceneGraphOctStack.push_back(&spatialGraph);

	std::vector<Ackerfe::ACube> cubes;

	GLuint frontSprite = Ackerfe::loadPng("Texture/cyan.png");
	GLuint backSprite = Ackerfe::loadPng("Texture/green.png");
	GLuint leftSprite = Ackerfe::loadPng("Texture/blue.png");
	GLuint rightSprite = Ackerfe::loadPng("Texture/purple.png");
	GLuint topSprite = Ackerfe::loadPng("Texture/orange.png");
	GLuint bottomSprite = Ackerfe::loadPng("Texture/yellow.png");

	for (float i = -1; i <= 1; i += 1)
	{
		for (float j = -1; j < 1; j += 1)
		{
			for (float k = -1; k < 1; k += 1)
			{
				spatialGraph.addEntityToGraph(new Ackerfe::ACube(glm::vec3(i, j, k),
					0.3f, frontSprite, backSprite, leftSprite, rightSprite, topSprite,
					bottomSprite, &multiSprite2));
			}
		}
	}

	for (unsigned int i = 0; i < sceneGraphOctStack.size(); i++)
	{
		if (Ackerfe::aabbCnvx(sceneGraphOctStack[i]->getBox(), cameraCheck.getFrustum()))
		{
			sceneGraphOctStack[i]->addToStack(&spatialEntityStack, &sceneGraphOctStack);
		}
	}

	for (unsigned int i = 0; i < spatialEntityStack.size(); i++)
	{
		if (1/*Ackerfe::aABBCnvx(spatialEntityStack[i]->getBox(), cameraCheck.getFrustum())*/)
		{
			
			spatialEntityStack[i]->renderEntity();
			std::cout << "Box at " << spatialEntityStack[i]->getPosition().x << ", " << spatialEntityStack[i]->getPosition().y << ", " << spatialEntityStack[i]->getPosition().z << std::endl;
		}

	}

	multiSprite2.prepareBatches();

	Level1 level1;
	level1.init(&camera3D, &shaderSet, 512, 512, &osInterface, &gui, &newInput);
	
	while (!quitCorrespondent.getMessage())
	{
		level1.level1Loop();
	}

	return 0;
	
}
