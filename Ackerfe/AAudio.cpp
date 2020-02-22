#include "AAudio.h"
#include<fstream>

namespace Ackerfe
{
	void errorCheck(FMOD_RESULT result, std::string failLine)
	{
		if (result != FMOD_OK)
		{
			throwError("FMODError", failLine);
		}
	}

	ASound::ASound()
	{

	}

	ASound::~ASound()
	{

	}

	void ASound::init(CorrespondentManager * corrManager, std::string & soundFile, FMOD::System * system)
	{
		soundReciever.init(corrManager, soundFile);
		mSystem = system;
		errorCheck(mSystem->createSound(soundFile.c_str(), FMOD_DEFAULT, NULL, &mSound), "Sound " + soundFile + " could not be initialized");
	}

	void ASound::update()
	{
		if (soundReciever.getMessage())
		{
			errorCheck(mSystem->playSound(mSound, NULL, false, NULL), "Sound could not be played.");
			soundReciever.clearMessage();
		}
	}

	void ASound::destroy()
	{
		errorCheck(mSound->release(), "Failed to release Sound");
	}

	AAudio::AAudio()
	{
	}

	AAudio::~AAudio()
	{
	}

	void AAudio::init(std::string & initialSoundMapFilePath, CorrespondentManager * corrManager)
	{
		errorCheck(FMOD::System_Create(&mSystem), "System Failed to be created.");
		errorCheck(mSystem->init(8, FMOD_INIT_NORMAL, NULL), "FMOD System failed to initialize.");
		mCorrespondentManager = corrManager;
		loadSoundMap(initialSoundMapFilePath);
	}

	void AAudio::loadSoundMap(std::string & soundMapFilePath)
	{
		if (!mSoundMap.empty())
		{
			mSoundMap.clear();
		}

		std::string tempString;
		std::ifstream fileStream(soundMapFilePath);
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
					mSoundMap.back().init(mCorrespondentManager, tempString, mSystem);
				}
			}
		}
		else
		{
			throwError(soundMapFilePath, soundMapFilePath + " sound map file is missing or corrupted.");
		}
	}

	void AAudio::update()
	{
		for (unsigned int i = 0; i < mSoundMap.size(); i++)
		{
			mSoundMap[i].update();
		}
	}

	FMOD_RESULT F_CALLBACK AAudio::EndOfSong(FMOD_CHANNELCONTROL*channelControl, FMOD_CHANNELCONTROL_TYPE controlType,
		FMOD_CHANNELCONTROL_CALLBACK_TYPE callbackType, void*commanData1, void*commanData2)
	{
		if (controlType == FMOD_CHANNELCONTROL_CHANNEL && callbackType == FMOD_CHANNELCONTROL_CALLBACK_END) {
			//se è un singolo channel è non un channel group e se la callback è chiamata quanto è finita la riproduzione del suono

			FMOD::Channel*channel = (FMOD::Channel*)channelControl;

			
		}


		return FMOD_OK;
	}
}