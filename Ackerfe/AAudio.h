#pragma once
#include "FMOD/fmod.hpp"
#include "ErrHandler.h"
#include <string>

namespace Ackerfe
{
	class AAudio
	{
		FMOD::System* mSystem = nullptr;

	public:
		void init();
		void errorCheck(FMOD_RESULT result, std::string failLine);
		FMOD::Sound* loadSound(std::string &soundFilePath);
		void play(FMOD::Sound* sound);
		void loadAndPlaySound(std::string &soundFilePath);
	};
}
