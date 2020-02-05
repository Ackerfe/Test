#pragma once
#include "FMOD/fmod.hpp"
#include "ErrHandler.h"
#include <string>
#include <map>

namespace Ackerfe
{
	class AAudio
	{
		FMOD::System* mSystem = nullptr;
		std::map<std::string, FMOD::Sound*>mSoundMap;

	public:
		void init();
		void errorCheck(FMOD_RESULT result, std::string failLine);
		void loadSound(std::string &soundFilePath, bool streaming = false);
		void play(std::string &soundFilePath);
		void unloadSound(std::string &soundFilePath);
	};
}
