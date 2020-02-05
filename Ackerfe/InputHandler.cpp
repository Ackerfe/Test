#include "InputHandler.h"
#include "ErrHandler.h"
#include <fstream>

namespace Ackerfe
{
	InputHandler::InputHandler()
	{
	}

	InputHandler::~InputHandler()
	{
	}

	void InputHandler::init(GUI* gui)
	{
		mGUI = gui;
	}
	void InputHandler::pressKey(unsigned int keyID)
	{
		auto it = mKeyMap.find(keyID);
		if (it != mKeyMap.end())
			it->second.keyFunction();
	}

	void InputHandler::unpressKey(unsigned int keyID)
	{
		
	}

	void InputHandler::pressButton(unsigned int keyID, glm::vec2 mousePosition)
	{
		auto it = mButtonMap.find(keyID);
			if (it != mButtonMap.end())
				it->second.buttonFunction(mousePosition);
	}

	void InputHandler::unpressButton(unsigned int keyID, glm::vec2 mousePosition)
	{
		
	}

	void InputHandler::inputQueue()
	{
	
		SDL_Event evnt;
		while (SDL_PollEvent(&evnt))
		{
		
			switch (evnt.type)
			{
			case SDL_QUIT:
				SDL_Quit();
				exit(60);
				break;
			
			case SDL_MOUSEMOTION:
				if (mGUI != nullptr)
					mGUI->mouseMotionFunc(evnt);
				break;
			case SDL_KEYDOWN:
				pressKey(evnt.key.keysym.sym);
				if (mGUI != nullptr)
					mGUI->keyDownFunc(evnt);
				break;
			case SDL_KEYUP:
				unpressKey(evnt.key.keysym.sym);
				if (mGUI != nullptr)
					mGUI->keyUpFunc(evnt);
				break;
			case SDL_TEXTINPUT:
				if(mGUI!=nullptr)
					mGUI->decodeInputText(evnt);

				break;
			case SDL_MOUSEBUTTONDOWN:
				pressButton(evnt.button.button, glm::vec2(evnt.button.x, evnt.button.y));
				if (mGUI != nullptr)
					mGUI->mouseButtonDownFunc(evnt);
				break;
			case SDL_MOUSEBUTTONUP:
				unpressButton(evnt.button.button, glm::vec2(evnt.button.x, evnt.button.y));
				if (mGUI != nullptr)
					mGUI->mouseButtonUpFunc(evnt);
				break;
			}
		}
	}

	void InputHandler::mapKeysFromFile(std::string & filePath,
		std::unordered_map<std::string, unsigned int> initStringsToSDLKeyCodes,
		std::unordered_map<std::string, void(*)()> initStringsToFunctions,
		std::unordered_map<std::string, void(*)(glm::vec2)> buttonMapStringsToFunctions)
	{
		std::vector <std::string> keyMapFileStrings = readFile(filePath);
		unsigned int iterator = 0;
		while (keyMapFileStrings[iterator] != "KeyMap")
		{

			if (iterator > keyMapFileStrings.size())
				throwError("keyMapError", "keymap file" + filePath + " contains no labeled 'KeyMap'");
			
			iterator++;

		}

		iterator++;

		while (keyMapFileStrings[iterator] != "KeyMapEnd")
		{


			if (iterator > keyMapFileStrings.size()) 
				throwError("keyMapError", "keymap file" + filePath + " contains no labeled 'KeyMapEnd'");
			

			unsigned int newKey = 0;
			AKey newKeyFunction;

			auto it = initStringsToSDLKeyCodes.find(keyMapFileStrings[iterator]);
			if (it != initStringsToSDLKeyCodes.end())
				newKey = it->second;

			else 
				throwError("keyMapSyntax", "Incorrect Keymap Syntax, no key where it was expected, instead I got: " + keyMapFileStrings[iterator]);

			iterator++;

			auto knit = initStringsToFunctions.find(keyMapFileStrings[iterator]);

			if (knit != initStringsToFunctions.end()) 
				newKeyFunction.keyFunction = knit->second;
				
			else
				throwError("keyMapSyntax", "Incorrect Keymap Syntax, no function where it was expected, instead I got: " + keyMapFileStrings[iterator]);

			mKeyMap[newKey] = newKeyFunction;

			iterator++;
				
		}

		iterator = 0;

		while (keyMapFileStrings[iterator] != "ButtonMap")
		{
			if (iterator > keyMapFileStrings.size())
				throwError("ButtonMapError", "ButtonMap file" + filePath + " contains no labeled 'ButtonMap'");

			iterator++;
		}

		iterator++;

		while (keyMapFileStrings[iterator] != "ButtonMapEnd")
		{


			if (iterator > keyMapFileStrings.size())
				throwError("ButtonMapError", "ButtonMap file" + filePath + " contains no labeled 'ButtonMapEnd'");

			unsigned int newButton = 0;
			AButton newButtonFunction;

			auto it = initStringsToSDLKeyCodes.find(keyMapFileStrings[iterator]);

			if (it != initStringsToSDLKeyCodes.end())
				newButton = it->second;

			else
				throwError("ButtonMapSyntax", "Incorrect ButtonMap Syntax, no Button where it was expected, instead I got: " + keyMapFileStrings[iterator]);

			iterator++;

			auto knit = buttonMapStringsToFunctions.find(keyMapFileStrings[iterator]);

			if (knit != buttonMapStringsToFunctions.end()) 
				newButtonFunction.buttonFunction = knit->second;
	
			else
				throwError("ButtonMapSyntax", "Incorrect ButtonMap Syntax, no function where it was expected, instead I got: " + keyMapFileStrings[iterator]);

			mButtonMap[newButton] = newButtonFunction;
			std::cout << "added " << newButton << " to buttonMap";
			iterator++;

			}
			
		
	}
}