#pragma once
#include <SDL/SDL.h>
#include <GL/glew.h>
#include <string>

namespace Ackerfe
{	
	/* Enumeratore che fa si che possiamo cambiare lo stile della finestra, usato nel metodo createWindow*/
	
	class WindowHandler
	{
		SDL_Window* msdlWindow;
		unsigned int mScreenWidth, mScreenHeight;
		
	public:
		WindowHandler();
		~WindowHandler();

		int createWindow(std::string windowName, unsigned int screenWidth, unsigned int screenHeight, int currentFlags);
		void swapBuffer();
		int getScreenWidth() { return mScreenWidth; }
		int getScreenHeight() { return mScreenHeight; }

	};
}
