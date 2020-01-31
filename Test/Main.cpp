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


/*temporary*/
#include <iostream>
#include "Cameras.h"

int main(int argc, char** argv)
{
	
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	float red = 0.0f;
	float green = 0.0f;
	float blue = 0.0f;
	Ackerfe::WindowHandler newWindow;
	newWindow.createWindow("Window", 1000, 1000, 0);

	Ackerfe::InputHandler newInput;


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
	//Ackerfe::SpriteFont spriteFont("Fonts/ThreSixt_2.ttf", 64);
	
	//char buffer[256];
	//sprintf_s(buffer, "Test String");
	//spriteFont.draw(multiSprite3, buffer, glm::vec2(0.0f, 0.1f), glm::vec2(1.0f), 0.0f, Ackerfe::ColourRGBA8(255, 100, 100, 255));

	Ackerfe::Camera2D camera2D(1000, 1000, glm::vec2(0.0f,0.0f), 1.0f);
	glm::mat4 ortho = camera2D.getMatrix();

	Ackerfe::Camera3D camera3D(512, 512, glm::vec3(10.0f,10.0f,50.0f), glm::vec3(23.0f, 23.0f, 23.0f), 45.0f, 2.0f, 30.0f, glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 perspective = camera3D.getPerspectiveMatrix();
	glm::mat4 modelMatrix = camera3D.getModelMatrix();
	glm::mat4 cameraMatrix = camera3D.getCameraMatrix();
	glm::mat4 modelCameraMatrix = modelMatrix * cameraMatrix;
	 

	Ackerfe::MultiSprite multiSprite;
	multiSprite.init();
	
	Ackerfe::Vertex test = Ackerfe::Vertex(0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, Ackerfe::ColourRGBA8(255, 100, 100, 255));
	Ackerfe::Vertex test2 = Ackerfe::Vertex(0.0f, 100.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, Ackerfe::ColourRGBA8(255, 100, 100, 255));
	Ackerfe::Vertex test3 = Ackerfe::Vertex(100.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, Ackerfe::ColourRGBA8(255, 100, 100, 255));
	Ackerfe::Vertex test4 = Ackerfe::Vertex(100.0f, 100.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, Ackerfe::ColourRGBA8(255, 100, 100, 255));
	GLuint textureID = Ackerfe::loadPng("Texture/test.png");
	GLuint textureID2 = Ackerfe::loadBmp("Texture/TWO.bmp");

	multiSprite.addSprite(textureID, 0.0f, test, test2, test3, test4);

	
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


	for (float i=10.0f; i<50.0f; i+=5.0f)
	{
		for (float j=10.0f; j<50.0f; j+=5.0f)
		{
			for (float k = 10.0f; k < 50.0f; k += 5.0f) 
				spatialGraph.addEntityToGraph(new Ackerfe::ACube(glm::vec3(i, j, k), 1.0f, "Texture/purple.png", "Texture/green.png", "Texture/blue.png", "Texture/orange.png", "Texture/cyan.png", "Texture/yellow.png", &multiSprite2));

			
		}
	}
	
	for (unsigned int i = 0; i < sceneGraphOctStack.size(); i++)
	{
		if (camera3D.isBoxInView(sceneGraphOctStack[i]->getPoints()));
			sceneGraphOctStack[i]->addToStack(&spatialEntityStack, &sceneGraphOctStack);
	}

	for (unsigned int i = 0; i < spatialEntityStack.size(); i++)
	{
		if (camera3D.isSphereInView(spatialEntityStack[i]->getPosition(), spatialEntityStack[i]->getCollisionRadius()))
			spatialEntityStack[i]->renderEntity();

	}
	
	

	


	multiSprite2.prepareBatches();
	
	
	while (!doQuit) 
	{
		
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(programID);
		//square.textureDraw();
		//glUniformMatrix4fv(shaderPerspectiveID, 1, GL_FALSE, &ortho[0][0]);
		//multiSprite3.renderBatches();
		//multiSprite.renderBatches();
	
		glUniformMatrix4fv(shaderPerspectiveID, 1, GL_FALSE, &perspective[0][0]);
		glUniformMatrix4fv(shaderModelMatrixID, 1, GL_FALSE, &modelMatrix[0][0]);
		glUniformMatrix4fv(shaderCameraMatrixID, 1, GL_FALSE, &cameraMatrix[0][0]);
		glUniformMatrix4fv(shaderModelCameraMatrixID, 1, GL_FALSE, &modelCameraMatrix[0][0]);

		glUniform3f(shaderLightPositionID, 45.0f, 45.5, 45.5f);
		glUniform3f(shaderLightColourID, 0.5f, 1.0f, 0.5f);
		glUniform1f(shaderLightIntensityID, 450.5f);
		

		multiSprite2.renderBatches();
		
		//multiSprite3.renderBatches();
		//glUseProgram(secondProgramID);
		glUseProgram(0);
		
		newInput.inputQueue();
		
		if (newInput.isKeyDown(SDLK_ESCAPE))
			doQuit = true;

		if (newInput.isKeyDown(SDLK_w))
		{
			camera3D.changePosition(camera3D.getPosition() + glm::vec3(0.0f, 0.10f, 0.0f));
			newInput.unpressKey(SDLK_w);
			perspective = camera3D.getPerspectiveMatrix();
			modelMatrix = camera3D.getModelMatrix();
			cameraMatrix = camera3D.getCameraMatrix();
			modelCameraMatrix = modelMatrix * cameraMatrix;
		}
		if (newInput.isKeyDown(SDLK_d))
		{
			camera3D.changePosition(camera3D.getPosition() + glm::vec3(0.10f, 0.0f, 0.0f));
			newInput.unpressKey(SDLK_d);
			perspective = camera3D.getPerspectiveMatrix();
			modelMatrix = camera3D.getModelMatrix();
			cameraMatrix = camera3D.getCameraMatrix();
			modelCameraMatrix = modelMatrix * cameraMatrix;
		}
		if (newInput.isKeyDown(SDLK_a))
		{
			camera3D.changePosition(camera3D.getPosition() + glm::vec3(-0.10f, 0.0f, 0.0f));
			newInput.unpressKey(SDLK_a);
			perspective = camera3D.getPerspectiveMatrix();
			modelMatrix = camera3D.getModelMatrix();
			cameraMatrix = camera3D.getCameraMatrix();
			modelCameraMatrix = modelMatrix * cameraMatrix;
		}
		if (newInput.isKeyDown(SDLK_s))
		{
			camera3D.changePosition(camera3D.getPosition() + glm::vec3(0.0f, -0.10f, 0.0f));
			newInput.unpressKey(SDLK_s);
			perspective = camera3D.getPerspectiveMatrix();
			modelMatrix = camera3D.getModelMatrix();
			cameraMatrix = camera3D.getCameraMatrix();
			modelCameraMatrix = modelMatrix * cameraMatrix;
		}
		if (newInput.isKeyDown(SDLK_k))
		{
			camera3D.changePosition(camera3D.getPosition() + glm::vec3(0.0f, 0.0f, -0.10f));
			newInput.unpressKey(SDLK_k);
			perspective = camera3D.getPerspectiveMatrix();
			modelMatrix = camera3D.getModelMatrix();
			cameraMatrix = camera3D.getCameraMatrix();
			modelCameraMatrix = modelMatrix * cameraMatrix;
		}
		if (newInput.isKeyDown(SDLK_i))
		{
			camera3D.changePosition(camera3D.getPosition() + glm::vec3(0.0f, 0.0f, 0.10f));
			newInput.unpressKey(SDLK_i);
			perspective = camera3D.getPerspectiveMatrix();
			modelMatrix = camera3D.getModelMatrix();
			cameraMatrix = camera3D.getCameraMatrix();
			modelCameraMatrix = modelMatrix * cameraMatrix;
		}
		newWindow.swapBuffer();
		
			
	}
	return 0;
}