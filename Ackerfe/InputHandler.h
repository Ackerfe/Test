#pragma once
#include <unordered_map>
#include <glm-0.9.9.7/glm/glm.hpp>
#include <string>
#include "GUI.h"
namespace Ackerfe
{
	struct AckerfeInput
	{
		bool keyDown = false;
	};
	struct AKey : public AckerfeInput
	{
		void(*keyFunction)();
	};
	struct AButton
	{
		void(*buttonFunction)(glm::vec2);
	};
	class InputHandler
	{
		std::unordered_map<unsigned int, AKey> mKeyMap;
		std::unordered_map<unsigned int, AButton> mButtonMap;
		GUI* mGUI = nullptr;

	public:
		InputHandler();
		~InputHandler();

		void init(GUI* gui);

		void inputQueue();

		void pressKey(unsigned int keyID);
		void unpressKey(unsigned int keyID);

		void pressButton(unsigned int keyID, glm::vec2 mousePosition);
		void unpressButton(unsigned int keyID, glm::vec2 mousePosition);

		void mapKeysFromFile(std::string &filePath,
			std::unordered_map<std::string, unsigned int> initStringsToSDLKeyCodes,
			std::unordered_map<std::string, void(*)()> initStringsToFunctions,
			std::unordered_map<std::string, void(*)(glm::vec2)> buttonMapStringsToFunctions);


	};
}
