#include "WindowHandler.h"

namespace Ackerfe
{
	WindowHandler::WindowHandler()
	{
	}

	WindowHandler::~WindowHandler()
	{
	}

	int WindowHandler::createWindow(std::string windowName, unsigned int screenWidth, unsigned int screenHeight, int currentFlags)
	{
		Uint32 flags = SDL_WINDOW_OPENGL;
		mScreenWidth = screenWidth;
		mScreenHeight = screenHeight;

		if (currentFlags & INVISIBLE)
		{
			flags |= SDL_WINDOW_HIDDEN;
		}
		if (currentFlags & FULLSCREEN) 
		{
			flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
		}
		if (currentFlags & BORDERLESS) 
		{
			flags |= SDL_WINDOW_BORDERLESS;
		}

		msdlWindow = SDL_CreateWindow(windowName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, getScreenWidth(), getScreenHeight(), flags);
		SDL_GLContext glContext = SDL_GL_CreateContext(msdlWindow);
		glewInit();
		glClearDepth(1.0);
		glClearColor(0.5f, 0.0f, 0.5f, 1.0f);

		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		
		
		
		return 0;
	}

	void WindowHandler::swapBuffer()
	{
		SDL_GL_SwapWindow(msdlWindow);
	}
}