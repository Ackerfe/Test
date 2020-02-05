#include "AAudio.h"

namespace Ackerfe
{
	void AAudio::init()
	{
		errorCheck(FMOD::System_Create(&mSystem), "System failed to be created");
		errorCheck(mSystem->init(8, FMOD_INIT_NORMAL, NULL), "FMOD System failed to initialize");
	}
	void AAudio::errorCheck(FMOD_RESULT result, std::string failLine)
	{
		if (result != FMOD_OK)
			throwError("FMODerror", failLine);
	}
	FMOD::Sound * AAudio::loadSound(std::string & soundFilePath)
	{
		FMOD::Sound* newSound;
		mSystem->createStream(soundFilePath.c_str(), FMOD_DEFAULT, NULL, &newSound);
		return newSound;
	}
	void AAudio::play(FMOD::Sound * sound)
	{
		mSystem->playSound(sound, NULL, false, NULL);
	}
	void AAudio::loadAndPlaySound(std::string & soundFilePath)
	{
		play(loadSound(soundFilePath));
	}
}