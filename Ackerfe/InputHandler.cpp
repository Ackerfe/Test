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

	void InputHandler::init(CorrespondentManager* corrManager)
	{
		mManager = corrManager;
		std::string tempString = "InputToGUISender";
		mToGUI.init(mManager, tempString);

		tempString = "Ini.txt";
		std::string tempStart = "InputHandler";
		std::string tempEnd = "InputHandlerEnd";
		std::vector<std::string> tempVector;
		extractLinesFromFile(&tempVector, tempStart, tempEnd, tempString);

		for (std::string i : tempVector)
			findAllKeys(i);
	}
	void InputHandler::pressKey(unsigned int keyID)
	{
		auto it = mKeyMap.find(keyID);
		if (it != mKeyMap.end())
			it->second.publish();
	}


	void InputHandler::pressButton(unsigned int keyID, glm::vec2 mousePosition)
	{
		auto it = mKeyMap.find(keyID);
			if (it != mKeyMap.end())
				it->second.publish(mousePosition);
	}

	void InputHandler::findAllKeys(std::string & filePath)
	{
		std::string tempString;
		std::string currentKey;
		std::ifstream fileStream(filePath);
		if (fileStream.is_open())
		{
			while (getline(fileStream, tempString))
			{
				if (tempString == "KEY")
				{
					getline(fileStream, tempString);
					getline(fileStream, tempString);
					currentKey = tempString;
				}
				if (tempString == "KEYCODE")
				{
					getline(fileStream, tempString);
					mapKey(std::stoi(tempString, nullptr, 10), currentKey);
				}
			}
		}
		else
			throwError(filePath, filePath + " could not be opened.");
	}

	void InputHandler::mapKey(unsigned int keyID, std::string & signature)
	{
		Correspondent newCorrespondent;
		mKeyMap.insert(std::pair<unsigned int, Correspondent>(keyID, newCorrespondent));
		mKeyMap[keyID].init(mManager, signature);
	}


	void InputHandler::inputQueue()
	{
	
		SDL_Event evnt;
		while (SDL_PollEvent(&evnt))
		{
			mToGUI.publish(evnt);
		
			switch (evnt.type)
			{
			case SDL_QUIT:
				SDL_Quit();
				exit(60);
				break;
	
			case SDL_KEYDOWN:
				pressKey(evnt.key.keysym.sym);
				break;
	
			case SDL_MOUSEBUTTONDOWN:
				pressButton(evnt.button.button, glm::vec2(evnt.button.x, evnt.button.y));
				break;
		
			}
		}
	}


}