#include <InputHandler.h>
#include <WindowHandler.h>
#include <SDL/SDL.h>
#include "Triangle.h"
#include "SimpleShader.h"
#include "Square.h"
#include "ErrHandler.h"
#include "MultiSprite.h"
#include "ImageLoad.h"
#include "Vertex.h"

/*temporary*/
#include <iostream>

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

	Ackerfe::MultiSprite multiSprite;
	multiSprite.init();
	
	Vertex test = Vertex(0.0f, 0.0f, 0.0f, 1.0f);
	Vertex test2 = Vertex(0.0f, 1.0f, 0.0f, 0.0f);
	Vertex test3 = Vertex(1.0f, 0.0f, 1.0f, 1.0f);
	Vertex test4 = Vertex(1.0f, 1.0f, 1.0f, 0.0f);
	GLuint textureID = Ackerfe::loadPng("Texture/test.png");
	GLuint textureID2 = Ackerfe::loadBmp("Texture/TWO.bmp");

	multiSprite.addSprite(textureID, 0.0f, test, test2, test3, test4);

	
	multiSprite.prepareBatches();
	
	while (!doQuit) 
	{
		
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(programID);
		//square.textureDraw();
		multiSprite.renderBatches();
		//glUseProgram(secondProgramID);
		glUseProgram(0);
		
		newInput.inputQueue();
		
		if (newInput.isKeyDown(SDLK_ESCAPE))
			doQuit = true;
		
		newWindow.swapBuffer();
		
			
	};
	return 0;
}