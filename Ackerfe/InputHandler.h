#pragma once
#include <unordered_map>
#include <glm-0.9.9.7/glm/glm.hpp>
#include <SDL/SDL.h>
#include <string>
#include "ErrHandler.h"
#include "MessagingSystem.h"

namespace Ackerfe
{
	class InputHandler
	{
		std::unordered_map<unsigned int, Correspondent> mKeyMap;
		CorrespondentManager* mManager;
		Correspondent mToGUI;
		Correspondent mMouseSender;

	public:
		InputHandler();
		~InputHandler();

		void init(CorrespondentManager* corrManager);

		void pressKey(unsigned int keyID);

		void pressButton(unsigned int keyID, glm::vec2 mousePosition);
		
		void findAllKeys(std::string &filePath);

		void mapKey(unsigned int keyID, std::string &signature);

		void inputQueue();


	};
}
