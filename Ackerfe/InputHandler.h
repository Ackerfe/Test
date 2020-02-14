#pragma once
#include<unordered_map>
#include "ErrHandler.h"
#include "OSInterface.h"
#include <glm-0.9.9.7/glm/glm.hpp>
#include "MessagingSystem.h"

namespace Ackerfe
{

	struct KeyOspondent
	{
		void update(KeyState * state)
		{
			if (cond.keyConditions(state))
			{
				corr.publish();
			}
		}
		KeyCondition cond;
		Correspondent corr;
	};

	struct MouseOspondent
	{
		void update(MouseState * state)
		{
			if (cond.mouseConditions(state))
			{
				glm::vec2 mouseConditions = glm::vec2(static_cast<float>(state->x), static_cast<float>(state->y));
				corr.publish(mouseConditions);
			}
		}
		MouseCondition cond;
		Correspondent corr;
	};

	struct MotOspondent
	{
		void update(MouseMotion * motion)
		{
			if (relative)
			{
				glm::vec2 relMotion = glm::vec2(static_cast<float>(motion->xRel), static_cast<float>(motion->yRel));
				corr.publish(relMotion);
			}
			else
			{
				glm::vec2 mouseMotion = glm::vec2(static_cast<float>(motion->x), static_cast<float>(motion->y));
				corr.publish(mouseMotion);
			}
		}
		bool relative = false;
		Correspondent corr;
	};
	class InputHandler
	{
	public:
		InputHandler();
		~InputHandler();

		void init(CorrespondentManager *corrManager, OSInterface * osInterface);

		void findAllKeys(std::string &filePath);

		void mapKey(unsigned int keyID, std::string &signature);

		void mapMouse(unsigned int buttonID, std::string &signature);

		/*Logs keystrokes to be used by the game.*/
		void inputQueue();

	private:
		OSInterface * mOSInterface;
		std::vector<std::unique_ptr<KeyOspondent>> mKeys;
		std::vector<std::unique_ptr<MouseOspondent>> mButtons;
		std::vector<std::unique_ptr<MotOspondent>> mMotions;
		CorrespondentManager *mCorrespondentManager;
	};

}