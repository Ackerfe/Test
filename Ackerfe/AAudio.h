#pragma once
#include "FMOD/fmod.hpp"
#include "ErrHandler.h"
#include <string>
#include <map>
#include "MessagingSystem.h"

namespace Ackerfe
{
	class ASound
	{
		Correspondent soundReceiver;
		FMOD::Sound* mSound = nullptr;
		FMOD::System* mSystem = nullptr;

	public:
		ASound();

		void init(CorrespondentManager* corrManager, std::string &soundFile, FMOD::System* system);
		void update();
		void destroy();


	};

	
	class AAudio
	{
		FMOD::System* mSystem = nullptr;
		CorrespondentManager* mManager;
		std::vector<ASound> mSoundMap;

	public:
		void init(std::string &initialSoundMapFilePath, CorrespondentManager* corrManager);
		void loadSoundMap(std::string &soundMapFilePath);
		void update();
	};
}
