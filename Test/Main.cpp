#include <InputHandler.h>
#include <WindowHandler.h>
#include <SDL/SDL.h>
/*temporary*/
#include <iostream>

int main(int argc, char** argv)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	Ackerfe::WindowHandler newWindow;
	newWindow.createWindow("Window", 500, 500, 0);

	Ackerfe::InputHandler newInput;


	bool doQuit = false;

	while (!doQuit) 
	{
		newInput.inputQueue();
		if (newInput.isKeyDown(SDLK_w))
		{
			doQuit = true;
		}
		else
			newWindow.swapBuffer();
	}
	return 0;
}