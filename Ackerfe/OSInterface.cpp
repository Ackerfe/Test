#include "OSInterface.h"


namespace Ackerfe
{
	OSInterface::OSInterface()
	{
	}

	OSInterface::~OSInterface()
	{
		SDL_Quit();
	}

	void OSInterface::init()
	{
		SDL_Init(SDL_INIT_EVERYTHING);
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	}

	int OSInterface::createWindow(std::string windowName, unsigned int screenWidth, unsigned int screenHeight, int currentFlags)
	{
		Uint32 flags = SDL_WINDOW_OPENGL;
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

		msdlWindow = SDL_CreateWindow(windowName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, flags);
		SDL_GLContext glContext = SDL_GL_CreateContext(msdlWindow);
		glewInit();
		glClearDepth(1.0);
		glClearColor(0.5f, 0.5f, 0.5f, 1.0f);

		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		return 0;
	}

	void OSInterface::swapBuffer()
	{
		SDL_GL_SwapWindow(msdlWindow);
	}

	std::vector<SDL_Event> OSInterface::getEvents()
	{
		updateInput();
		std::vector<SDL_Event> returnVector;
		returnVector = mEvents;
		mEvents.clear();
		return returnVector;
	}

	InputState OSInterface::getInput()
	{
		updateInput();
		InputState returnState;
		returnState = mInputState;
		mInputState.mButtons.clear();
		mInputState.mKeys.clear();
		mInputState.mMotions.clear();
		return returnState;
	}

	void OSInterface::updateInput()
	{
		SDL_Event evnt;
		while (SDL_PollEvent(&evnt))
		{
			mEvents.push_back(evnt);
			MouseState mouseState;
			KeyState keyState;
			MouseMotion mouseMotion;

			switch (evnt.type)
			{
			case SDL_KEYDOWN:
				if (evnt.key.windowID == SDL_GetWindowID(msdlWindow))
				{
					keyState.key = evnt.key.keysym.sym;
					keyState.down = true;
					mInputState.mKeys.push_back(keyState);	
				}
				break;
			case SDL_KEYUP:
				if (evnt.key.windowID == SDL_GetWindowID(msdlWindow))
				{
					keyState.key = evnt.key.keysym.sym;
					keyState.down = false;
					mInputState.mKeys.push_back(keyState);
				}
				break;
			case SDL_MOUSEBUTTONDOWN:
				if (evnt.button.windowID == SDL_GetWindowID(msdlWindow))
				{
					mouseState.button = evnt.button.button;
					mouseState.down = true;
					mouseState.x = evnt.button.x;
					mouseState.y = evnt.button.y;
					mInputState.mButtons.push_back(mouseState);
				}
				break;
			case SDL_MOUSEBUTTONUP:
				if (evnt.button.windowID == SDL_GetWindowID(msdlWindow))
				{
					mouseState.button = evnt.button.button;
					mouseState.down = false;
					mouseState.x = evnt.button.x;
					mouseState.y = evnt.button.y;
					mInputState.mButtons.push_back(mouseState);
				}
				break;
			case SDL_MOUSEMOTION:
				if (evnt.motion.windowID == SDL_GetWindowID(msdlWindow))
				{
					mouseMotion.x = evnt.motion.x;
					mouseMotion.y = evnt.motion.y;
					mouseMotion.xRel = evnt.motion.xrel;
					mouseMotion.yRel = evnt.motion.yrel;
					mInputState.mMotions.push_back(mouseMotion);
				}
				break;
			default:
				break;
			}
		}
	}

	unsigned int millisecondsSinceProgramStart()
	{
		return static_cast <unsigned int>(SDL_GetTicks());
	}

	int relativeMouseMotionToggle()
	{
		if (SDL_GetRelativeMouseMode() == SDL_TRUE)
			return SDL_SetRelativeMouseMode(SDL_FALSE);
		
		return SDL_SetRelativeMouseMode(SDL_TRUE);
	}
}