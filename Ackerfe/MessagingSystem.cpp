#include "MessagingSystem.h"
#include "InitFileReadWrite.h"
#include "ErrHandler.h"
#include <fstream>
#include <iostream>


namespace Ackerfe
{
	
	CorrespondentManager::CorrespondentManager()
	{
	}

	CorrespondentManager::~CorrespondentManager()
	{
	}

	void CorrespondentManager::init()
	{
		checkConnectionRequest();
	}
	void CorrespondentManager::firstInit()
	{
		std::string filePath = "CorrespondentMasterList.txt";
		std::vector<std::string> tempVector = readFile(filePath);

		for (std::string i : tempVector)
		{
			createCorrespondentSignature(i);
			std::cout << i <<std::endl;
		}

		tempVector.clear();
		filePath = "Ini.txt";
		std::string startLine = "CorrespondentManager";
		std::string endLine = "CorrespondentManagerEnd";

		extractLinesFromFile(&tempVector, startLine, endLine, filePath);
			for (std::string i : tempVector)
			{
				findAllConnections(i);

			}
	}

	void CorrespondentManager::findAllConnections(std::string & filePath)
	{
		std::string tempString;
		std::string currentPublisher;
		std::ifstream fileStream(filePath);
		
		if (fileStream.is_open())
		{
			while (getline(fileStream, tempString))
			{
				if (tempString == "PUBLISHER")
				{
					getline(fileStream, tempString);

					if (isCorrespondentSignature(tempString)) 
						currentPublisher = tempString;
						

					else
						throwError("PUBLISHER", "Program does not recognize publisher " + tempString);
				}
				if (tempString == "SUBSCRIBER")
				{
					getline(fileStream, tempString);

					if (isCorrespondentSignature(tempString))
						mConnectionRequest.emplace(currentPublisher, tempString);
						
					else
						throwError("SUBSCRIBER", "Program does not recognize subscriber " + tempString);
				}
			}

		}
		else
			throwError(filePath, filePath + " is missing or corrupted");
	}

	void CorrespondentManager::checkConnectionRequest()
	{
		
		for (std::multimap<std::string, std::string>::iterator currentRequest = mConnectionRequest.begin(); currentRequest != mConnectionRequest.end(); currentRequest++)
		{
			std::cout << std::endl << currentRequest->first + "->" +currentRequest->second;
			auto publisher = mActiveCorrespondents.find(currentRequest->first);
			if (publisher != mActiveCorrespondents.end())
			{
				publisher = mActiveCorrespondents.find(currentRequest->second);
				if (publisher != mActiveCorrespondents.end())
				{
				
					createSubscription((std::string&)currentRequest->first , currentRequest->second);
				
				}
			}
		}
		mConnectionRequest.clear();
	}

	void CorrespondentManager::listNewCorrespondent(std::string & correspondentSignature, Correspondent* correspondent)
	{
		if (isCorrespondentSignature(correspondentSignature))
		{
			mActiveCorrespondents.insert(std::pair<std::string, Correspondent*>(correspondentSignature, correspondent));
		}
		else
			throwError("CorrespondentError", "Correspondent " + correspondentSignature + " does not appear in CorrespondentMasterList.txt");

	}

	void CorrespondentManager::createSubscription(std::string & subscriber, std::string & publisher)
	{
		Correspondent* correspondent;
		auto doesSubscriberExist = mActiveCorrespondents.find(subscriber);
		if (doesSubscriberExist == mActiveCorrespondents.end())
		{
			mConnectionRequest.emplace(publisher, subscriber);
		
		}

		auto doesPublisherExist = mActiveCorrespondents.find(publisher);
		if (doesPublisherExist == mActiveCorrespondents.end())
		{
			mConnectionRequest.emplace(publisher, subscriber);
			
		}


	
		doesPublisherExist->second->receiveSubscriber(subscriber, doesSubscriberExist->second);
	}

	void CorrespondentManager::cancelSubscription(std::string & subscriber, std::string & publisher)
	{
		auto doesPublisherExist = mActiveCorrespondents.find(publisher);
		if (doesPublisherExist != mActiveCorrespondents.end())
			doesPublisherExist->second->removeSubscriber(subscriber);

		for (auto connectionIterator = mConnectionRequest.begin(); connectionIterator != mConnectionRequest.end(); connectionIterator++)
			if (connectionIterator->first == publisher && connectionIterator->second == subscriber)
					mConnectionRequest.erase(connectionIterator);


	}

	

	void CorrespondentManager::delistCorrespondent(std::string & correspondentSignature)
	{
		auto activeCorrespondent = mActiveCorrespondents.find(correspondentSignature);
		if (activeCorrespondent != mActiveCorrespondents.end())
		{
			mActiveCorrespondents.erase(activeCorrespondent);
		}

	}

	void CorrespondentManager::createCorrespondentSignature(std::string & signature)
	{
		mAllPossibleCorrespondentSignatures.push_back(signature);
	}

	void CorrespondentManager::removeCorrespondentSignature(std::string & signature)
	{
		unsigned int iterator = 0;
		while (iterator < mAllPossibleCorrespondentSignatures.size())
		{
			if (mAllPossibleCorrespondentSignatures[iterator] == signature)
				mAllPossibleCorrespondentSignatures.erase(mAllPossibleCorrespondentSignatures.begin() + iterator);
		}
	}

	bool CorrespondentManager::isCorrespondentSignature(std::string & signature)
	{
		unsigned int iterator = 0;
		while (iterator < mAllPossibleCorrespondentSignatures.size())
		{
			if (mAllPossibleCorrespondentSignatures[iterator] == signature)
				return true;

			iterator++;
		}
		return false;
	}

	Correspondent::Correspondent()
	{
	}

	Correspondent::~Correspondent()
	{
	}

	void Correspondent::init(CorrespondentManager * manager, std::string &signature)
	{
		mManager = manager;
		mSignature = signature;
		manager->listNewCorrespondent(signature, this);
	}

	void Correspondent::destroy()
	{
		mManager->delistCorrespondent(mSignature);
	}

	void Correspondent::passToSubscribers(std::shared_ptr<Message> messagePtr)
	{
		for (auto iterator = mSubscribers.begin(); iterator != mSubscribers.end(); iterator++)
			iterator->second->receiveMessage(messagePtr);
	
	}

	void Correspondent::receiveSubscriber(std::string & subscriberSignature, Correspondent * subscriber)
	{
		mSubscribers.insert(std::pair<std::string, Correspondent*>(subscriberSignature, subscriber));
	}

	void Correspondent::removeSubscriber(std::string & subscriberSignature)
	{
		auto findSubscriber = mSubscribers.find(subscriberSignature);
		if (findSubscriber != mSubscribers.end())
			mSubscribers.erase(subscriberSignature);
		
	}

	void Correspondent::publish()
	{
		std::shared_ptr<Message> newMessage(new Message);
		passToSubscribers(newMessage);
		
	}

	void Correspondent::publish(glm::vec2 mouseCoords)
	{
		std::shared_ptr<MouseMessage> newMessage(new MouseMessage);
		newMessage->mouseCoords = mouseCoords;
		passToSubscribers(newMessage);
		
	}

	void Correspondent::publish(SDL_Event & evnt)
	{
		std::shared_ptr<EventMessage> newMessage(new EventMessage);
		newMessage->evnt = evnt;
		passToSubscribers(newMessage);

	}

	void Correspondent::receiveMessage(std::shared_ptr<Message> message)
	{
		mMessage = message;

	}

	bool Correspondent::getMessage()
	{
		if (mMessage != nullptr)
			return true;
		return false;
	}

	glm::vec2 Correspondent::getMouseMessage()
	{
		return mMessage->getMouseMessage();
	}

	SDL_Event Correspondent::getEventMessage()
	{
		return mMessage->getEventMessage();
	}

	void Correspondent::clearMessage()
	{
		mMessage = nullptr;
	}

}