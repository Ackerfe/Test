#include <InputHandler.h>
#include <WindowHandler.h>
#include <SDL/SDL.h>
#include "Triangle.h"
#include "SimpleShader.h"
#include "Square.h"
#include "AckerfeErrorHandler.h"

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

	Ackerfe::Square square("Texture/TWO.bmp");
	Ackerfe::Triangle triangle;

	GLuint programID = Ackerfe::compileLinkSimpleShaders("TextureVert.vert", "TextureFrag.frag");
	GLuint secondProgramID = Ackerfe::compileLinkSimpleShaders("SimpleVert.vert", "SimpleFrag.frag");

	while (!doQuit) 
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(programID);
		square.textureDraw();
		glUseProgram(secondProgramID);
		triangle.draw();
		glUseProgram(0);
		newInput.inputQueue();
		
		if (newInput.isKeyDown(SDLK_w))
		{
			doQuit = true;
		}
		else {
			newWindow.swapBuffer();
		}
		

		
	};
	return 0;
}