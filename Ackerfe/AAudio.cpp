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

	void AAudio::loadSound(std::string & soundFilePath, bool streaming /*= false*/)
	{
		auto doesSoundExist = mSoundMap.find(soundFilePath);
		if (doesSoundExist != mSoundMap.end())
			return;

		FMOD_MODE mode = FMOD_DEFAULT;

		if (streaming)
			mode |= FMOD_CREATESTREAM;

		FMOD::Sound* newSound;
		mSystem->createSound(soundFilePath.c_str(), mode, NULL, &newSound);
		mSoundMap[soundFilePath] = newSound;
		
	}
	
	void AAudio::unloadSound(std::string & soundFilePath)
	{
		auto doesSoundExist = mSoundMap.find(soundFilePath);
		if (doesSoundExist != mSoundMap.end())
			return;

		errorCheck(doesSoundExist->second->release(), "Failed to release sound" + soundFilePath);
		mSoundMap.erase(doesSoundExist);
		std::cout << "exited succesfully";

	}
	
	void AAudio::play(std::string &soundFilePath)
	{
		auto doesSoundExist = mSoundMap.find(soundFilePath);
		if (doesSoundExist != mSoundMap.end())
			loadSound(soundFilePath);
		mSystem->playSound(doesSoundExist->second, NULL, false, NULL);
	}
	
	
}