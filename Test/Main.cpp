#include <InputHandler.h>
#include <WindowHandler.h>
#include <SDL/SDL.h>

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
	newWindow.createWindow("Window", 500, 500, 0);

	Ackerfe::InputHandler newInput;


	bool doQuit = false;

	while (!doQuit) 
	{
		glClearColor(red, green, blue, 1.0f);
		
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		newInput.inputQueue();
		if (newInput.isKeyDown(SDLK_w))
		{
			doQuit = true;
		}
		else {
			newWindow.swapBuffer();
		}
		if (red >= 1.0f)
			red = 0.0f;
		else
			red += 0.0001f;
		if (green >= 1.0f)
			green = 0.0f;
		else
			green += 0.0002f;
		if (blue >= 1.0f)
			blue = 0.0f;
		else
			blue += 0.0003f;

		
	};
	return 0;
}