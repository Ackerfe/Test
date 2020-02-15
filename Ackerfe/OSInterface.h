#pragma comment(lib, "glu32.lib")
#pragma once
#include <SDL/SDL.h>
#include <SDL/SDL_timer.h>
#include <vector>
#include <string>
#include <GL/glew.h>
#include "MessagingSystem.h"

namespace Ackerfe
{
	unsigned int millisecondsSinceProgramStart();

	int relativeMouseMotionToggle();

	struct KeyState
	{
		unsigned int key = 0;
		bool down = false;
	};

	struct KeyCondition
	{
		bool keyConditions(KeyState * state) const
		{
			return (state->key == key && state->down == down);
		}
		unsigned int key = 0;
		bool down = false;
	};

	struct MouseState
	{
		unsigned int button = 0;
		bool down = false;
		int x = 0;
		int y = 0;
	};

	struct MouseCondition
	{
		bool mouseConditions(MouseState * state) const
		{
			return (state->button == button && state->down == down);
		}
		unsigned int button = 0;
		bool down = false;
	};

	struct MouseMotion
	{
		int x = 0;
		int y = 0;
		int xRel = 0;
		int yRel = 0;
	};

	struct InputState
	{
		std::vector<KeyState> mKeys;
		std::vector<MouseState> mButtons;
		std::vector<MouseMotion> mMotions;
	};

	enum WindowFlags { INVISIBLE = 0X1, FULLSCREEN = 0x2, BORDERLESS = 0x4 };

	class OSInterface
	{
		SDL_Window* msdlWindow;
		InputState mInputState;
		std::vector<SDL_Event> mEvents;

	public:
		OSInterface();
		~OSInterface();

		void init();
		int createWindow(std::string windowName, unsigned int screenWidth, unsigned int screenHeight, int currentFlags);
		void swapBuffer();

		std::vector<SDL_Event> getEvents();
		InputState getInput();

		void updateInput();


	
	};

}

