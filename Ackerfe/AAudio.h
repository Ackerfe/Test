#pragma once
#include <FMOD/fmod.hpp>
#include <FMOD/fmod_studio.hpp>
#include "ErrHandler.h"
#include <string>
#include <map>
#include <vector>
#include "MessagingSystem.h"

namespace Ackerfe
{
	class ASound
	{
	public:
		ASound();
		~ASound();

		void init(CorrespondentManager *corrManager, std::string &soundFile, FMOD::System *system);
		void update();
		void destroy();
	private:
		Correspondent soundReciever;
		FMOD::Sound *mSound = nullptr;
		FMOD::System *mSystem = nullptr;
	};

	class AAudio
	{
	public:
		AAudio();
		~AAudio();

		void init(std::string &initialSoundMapFilePath, CorrespondentManager *corrManager);
		void loadSoundMap(std::string& soundMapFilePath);
		void update();
		FMOD_RESULT F_CALLBACK EndOfSong(FMOD_CHANNELCONTROL*channelControl, FMOD_CHANNELCONTROL_TYPE controlType,
			FMOD_CHANNELCONTROL_CALLBACK_TYPE callbackType, void*commanData1, void*commanData2);
		

	private:
		FMOD::System* mSystem = nullptr;
		std::vector<ASound> mSoundMap;
		CorrespondentManager *mCorrespondentManager;
	};

}