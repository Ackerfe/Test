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


	Ackerfe::MultiSprite multiSprite3;
	multiSprite3.init();
	Ackerfe::SpriteFont spriteFont("Fonts/ThreSixt_2.ttf", 64);
	
	char buffer[256];
	sprintf_s(buffer, "Test String");
	spriteFont.draw(multiSprite3, buffer, glm::vec2(0.0f, 0.1f), glm::vec2(1.0f), 0.0f, Ackerfe::ColourRGBA8(255, 100, 100, 255));

	Ackerfe::Camera2D camera2D(1000, 1000, glm::vec2(0.0f,0.0f), 1.0f);
	glm::mat4 ortho = camera2D.getMatrix();

	Ackerfe::Camera3D camera3D(1000, 1000, glm::vec3(4.0f,4.0f,3.0f), glm::vec3(0.5f,0.5f,-2.5f), 45.0f, 0.1f, 1500.0f);
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

	//front
	multiSprite2.addSprite(Ackerfe::loadPng("Texture/yellow (2).png"), 0.0f,
		Ackerfe::Vertex(0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, Ackerfe::ColourRGBA8(255, 255, 255, 255)),
		Ackerfe::Vertex(0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, Ackerfe::ColourRGBA8(255, 255, 255, 255)),
		Ackerfe::Vertex(1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, Ackerfe::ColourRGBA8(255, 255, 255, 255)),
		Ackerfe::Vertex(1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, Ackerfe::ColourRGBA8(255, 255, 255, 255)));

	//right
	multiSprite2.addSprite(Ackerfe::loadPng("Texture/orange (2).png"), 0.0f,
		Ackerfe::Vertex(1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, Ackerfe::ColourRGBA8(255, 255, 255, 255)),
		Ackerfe::Vertex(1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, Ackerfe::ColourRGBA8(255, 255, 255, 255)),
		Ackerfe::Vertex(1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, Ackerfe::ColourRGBA8(255, 255, 255, 255)),
		Ackerfe::Vertex(1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, Ackerfe::ColourRGBA8(255, 255, 255, 255)));

	//bottom
	multiSprite2.addSprite(Ackerfe::loadPng("Texture/blue (2).png"), 0.0f,
		Ackerfe::Vertex(0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,-1.0f, 0.0f, Ackerfe::ColourRGBA8(255, 255, 255, 255)),
		Ackerfe::Vertex(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, Ackerfe::ColourRGBA8(255, 255, 255, 255)),
		Ackerfe::Vertex(1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, -1.0f, 0.0f, Ackerfe::ColourRGBA8(255, 255, 255, 255)),
		Ackerfe::Vertex(1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, -1.0f, 0.0f, Ackerfe::ColourRGBA8(255, 255, 255, 255)));

	//left
	multiSprite2.addSprite(Ackerfe::loadPng("Texture/cyan (2).png"), 0.0f,
		Ackerfe::Vertex(0.0f, 0.0f, 1.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f, Ackerfe::ColourRGBA8(255, 255, 255, 255)),
		Ackerfe::Vertex(0.0f, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, Ackerfe::ColourRGBA8(255, 255, 255, 255)),
		Ackerfe::Vertex(0.0f, 0.0f, 0.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f, Ackerfe::ColourRGBA8(255, 255, 255, 255)),
		Ackerfe::Vertex(0.0f, 1.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f, Ackerfe::ColourRGBA8(255, 255, 255, 255)));

	//back
	multiSprite2.addSprite(Ackerfe::loadPng("Texture/purple (2).png"), 0.0f,
		Ackerfe::Vertex(0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, -1.0f, Ackerfe::ColourRGBA8(255, 255, 255, 255)),
		Ackerfe::Vertex(0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, Ackerfe::ColourRGBA8(255, 255, 255, 255)),
		Ackerfe::Vertex(1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f, Ackerfe::ColourRGBA8(255, 255, 255, 255)),
		Ackerfe::Vertex(1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f, Ackerfe::ColourRGBA8(255, 255, 255, 255)));

	//top
	multiSprite2.addSprite(Ackerfe::loadPng("Texture/green (2).png"), 0.0f,
		Ackerfe::Vertex(0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, Ackerfe::ColourRGBA8(255, 255, 255, 255)),
		Ackerfe::Vertex(0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, Ackerfe::ColourRGBA8(255, 255, 255, 255)),
		Ackerfe::Vertex(1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, Ackerfe::ColourRGBA8(255, 255, 255, 255)),
		Ackerfe::Vertex(1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, Ackerfe::ColourRGBA8(255, 255, 255, 255)));


	//second Cube

	//front
	multiSprite2.addSprite(Ackerfe::loadPng("Texture/yellow (2).png"), 0.0f,
		Ackerfe::Vertex(0.0f, 0.0f, -2.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, Ackerfe::ColourRGBA8(255, 255, 255, 255)),
		Ackerfe::Vertex(0.0f, 1.0f, -2.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, Ackerfe::ColourRGBA8(255, 255, 255, 255)),
		Ackerfe::Vertex(1.0f, 0.0f, -2.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, Ackerfe::ColourRGBA8(255, 255, 255, 255)),
		Ackerfe::Vertex(1.0f, 1.0f, -2.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, Ackerfe::ColourRGBA8(255, 255, 255, 255)));

	//right
	multiSprite2.addSprite(Ackerfe::loadPng("Texture/orange (2).png"), 0.0f,
		Ackerfe::Vertex(1.0f, 0.0f, -2.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, Ackerfe::ColourRGBA8(255, 255, 255, 255)),
		Ackerfe::Vertex(1.0f, 1.0f, -2.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, Ackerfe::ColourRGBA8(255, 255, 255, 255)),
		Ackerfe::Vertex(1.0f, 0.0f, -3.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, Ackerfe::ColourRGBA8(255, 255, 255, 255)),
		Ackerfe::Vertex(1.0f, 1.0f, -3.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, Ackerfe::ColourRGBA8(255, 255, 255, 255)));

	//bottom
	multiSprite2.addSprite(Ackerfe::loadPng("Texture/blue (2).png"), 0.0f,
		Ackerfe::Vertex(0.0f, 0.0f, -3.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f, Ackerfe::ColourRGBA8(255, 255, 255, 255)),
		Ackerfe::Vertex(0.0f, 0.0f, -2.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, Ackerfe::ColourRGBA8(255, 255, 255, 255)),
		Ackerfe::Vertex(1.0f, 0.0f, -3.0f, 1.0f, 1.0f, 0.0f, -1.0f, 0.0f, Ackerfe::ColourRGBA8(255, 255, 255, 255)),
		Ackerfe::Vertex(1.0f, 0.0f, -2.0f, 1.0f, 0.0f, 0.0f, -1.0f, 0.0f, Ackerfe::ColourRGBA8(255, 255, 255, 255)));

	//left
	multiSprite2.addSprite(Ackerfe::loadPng("Texture/cyan (2).png"), 0.0f,
		Ackerfe::Vertex(0.0f, 0.0f, -3.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f, Ackerfe::ColourRGBA8(255, 255, 255, 255)),
		Ackerfe::Vertex(0.0f, 1.0f, -3.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, Ackerfe::ColourRGBA8(255, 255, 255, 255)),
		Ackerfe::Vertex(0.0f, 0.0f, -2.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f, Ackerfe::ColourRGBA8(255, 255, 255, 255)),
		Ackerfe::Vertex(0.0f, 1.0f, -2.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f, Ackerfe::ColourRGBA8(255, 255, 255, 255)));

	//back
	multiSprite2.addSprite(Ackerfe::loadPng("Texture/purple (2).png"), 0.0f,
		Ackerfe::Vertex(0.0f, 0.0f, -3.0f, 0.0f, 1.0f, 0.0f, 0.0f, -1.0f, Ackerfe::ColourRGBA8(255, 255, 255, 255)),
		Ackerfe::Vertex(0.0f, 1.0f, -3.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, Ackerfe::ColourRGBA8(255, 255, 255, 255)),
		Ackerfe::Vertex(1.0f, 0.0f, -3.0f, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f, Ackerfe::ColourRGBA8(255, 255, 255, 255)),
		Ackerfe::Vertex(1.0f, 1.0f, -3.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f, Ackerfe::ColourRGBA8(255, 255, 255, 255)));

	//top
	multiSprite2.addSprite(Ackerfe::loadPng("Texture/green (2).png"), 0.0f,
		Ackerfe::Vertex(0.0f, 1.0f, -2.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, Ackerfe::ColourRGBA8(255, 255, 255, 255)),
		Ackerfe::Vertex(0.0f, 1.0f, -3.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, Ackerfe::ColourRGBA8(255, 255, 255, 255)),
		Ackerfe::Vertex(1.0f, 1.0f, -2.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, Ackerfe::ColourRGBA8(255, 255, 255, 255)),
		Ackerfe::Vertex(1.0f, 1.0f, -3.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, Ackerfe::ColourRGBA8(255, 255, 255, 255)));


	multiSprite2.prepareBatches();
	multiSprite3.prepareBatches();
	
	while (!doQuit) 
	{
		
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(programID);
		//square.textureDraw();
		//glUniformMatrix4fv(location, 1, GL_FALSE, &camera2DMatrix[0][0]);
		//multiSprite3.renderBatches();
		//multiSprite.renderBatches();
	
		glUniformMatrix4fv(shaderPerspectiveID, 1, GL_FALSE, &perspective[0][0]);
		glUniformMatrix4fv(shaderModelMatrixID, 1, GL_FALSE, &modelMatrix[0][0]);
		glUniformMatrix4fv(shaderCameraMatrixID, 1, GL_FALSE, &cameraMatrix[0][0]);
		glUniformMatrix4fv(shaderModelCameraMatrixID, 1, GL_FALSE, &modelCameraMatrix[0][0]);

		glUniform3f(shaderLightPositionID, 2.0f, 1.5, -1.5f);
		glUniform3f(shaderLightColourID, 1.0f, 1.0f, 1.0f);
		glUniform1f(shaderLightIntensityID, 1.2f);

		multiSprite2.renderBatches();
		//multiSprite3.renderBatches();
		//glUseProgram(secondProgramID);
		glUseProgram(0);
		
		newInput.inputQueue();
		
		if (newInput.isKeyDown(SDLK_ESCAPE))
			doQuit = true;
		
		newWindow.swapBuffer();
		
			
	};
	return 0;
}