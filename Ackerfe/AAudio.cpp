#include "AAudio.h"

namespace Ackerfe
{
	void errorCheck(FMOD_RESULT result, std::string failLine)
	{
		if (result != FMOD_OK) {
			throwError("FMODerror", failLine);
		}
	}

	void AAudio::init(std::string &initialSoundMapFilePath, CorrespondentManager* corrManager)
	{
		
		errorCheck(FMOD::System_Create(&mSystem), "System failed to be created");
		errorCheck(mSystem->init(8, FMOD_INIT_NORMAL, NULL), "FMOD System failed to initialize");
		mManager = corrManager;
		loadSoundMap(initialSoundMapFilePath);
		
	}

	
	void AAudio::loadSoundMap(std::string & initialSoundMapFilePath)
	{
		if (!mSoundMap.empty())
			mSoundMap.clear();

		std::string tempString;
		std::ifstream fileStream(initialSoundMapFilePath);
		if (fileStream.is_open())
		{
			while (getline(fileStream, tempString))
			{
				if (tempString == "SOUND")
				{
					getline(fileStream, tempString);
					getline(fileStream, tempString);
					getline(fileStream, tempString);
					getline(fileStream, tempString);
					ASound newSound;
					mSoundMap.push_back(newSound);
					mSoundMap.back().init(mManager, tempString, mSystem);
				}
			}
		}
		else
			throwError("SoundMapFile", "SoundMapFile " + initialSoundMapFilePath + " could not be opened");
	}

	void AAudio::update()
	{
		for (unsigned int i = 0; i < mSoundMap.size(); i++)
		{
			mSoundMap[i].update();
		}
	}
	

	
	
	ASound::ASound()
	{
	}


	void ASound::init(CorrespondentManager * corrManager, std::string & soundFile, FMOD::System * system)
	{ 
		soundReceiver.init(corrManager, soundFile);
		mSystem = system;
		errorCheck(mSystem->createSound(soundFile.c_str(), FMOD_DEFAULT, NULL, &mSound), "Sound " + soundFile + " could not be initialized");
	}

	void ASound::update()
	{
		if (soundReceiver.getMessage())
		{
			errorCheck(mSystem->playSound(mSound, NULL, false, NULL), "Sound could not be played");
			soundReceiver.clearMessage();
		}
	}

	void ASound::destroy()
	{
		errorCheck(mSound->release(), "Sound could not be released");
	}

}