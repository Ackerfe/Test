#include "InputHandler.h"
#include "AckerfeErrorHandler.h"

namespace Ackerfe
{
	InputHandler::InputHandler()
	{
	}

	InputHandler::~InputHandler()
	{
	}

	void InputHandler::pressKey(unsigned int keyID)
	{
		mKeyMap[keyID] = true;
	}

	bool InputHandler::isKeyDown(unsigned int keyID)
	{
		auto it = mKeyMap.find(keyID);
		if (it != mKeyMap.end()) 
			return it->second;
		else {
			return false;
		}
		/*
		else
		{
			throwError("KeyBindings", "Il tasto selezionato non fa parte dei KeyBindings");
			return false;
		}
		*/
	}
	void InputHandler::inputQueue()
	{
		SDL_Event evnt;
		while (SDL_PollEvent(&evnt))
		{
			switch (evnt.type)
			{
				case SDL_QUIT:
				{
					SDL_Quit();
					exit(60);
					break;
				}
				case SDL_KEYDOWN:
				{
					pressKey(evnt.key.keysym.sym);
					break;
				}
				default:
					break;
			}
		}
	}
}