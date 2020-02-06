#pragma once

#include <map>
#include <memory>
#include <string>
#include <vector>
#include "glm-0.9.9.7/glm/glm.hpp"
#include "SDL/SDL_events.h"



namespace Ackerfe
{
	struct Message
	{
		virtual glm::vec2 getMouseMessage() { return glm::vec2(0.0f); }
		virtual SDL_Event getEventMessage() { return SDL_Event(); }
	};

	struct MouseMessage : Message
	{
		glm::vec2 getMouseMessage() { return mouseCoords; }
		glm::vec2 mouseCoords;
	};
	
	struct EventMessage :Message
	{
		SDL_Event getEventMessage() { return evnt; }
		SDL_Event evnt;
	};

	class Correspondent;

	class CorrespondentManager
	{
		std::map<std::string, Correspondent*> mActiveCorrespondents;
		std::multimap<std::string, std::string> mConnectionRequest;
		std::vector<std::string> mAllPossibleCorrespondentSignatures;
		
	public:

		CorrespondentManager();
		~CorrespondentManager();

		void firstInit();
		void init();
		void findAllConnections(std::string &filePath);

		void checkConnectionRequest();

		void createSubscription(std::string &subscriber, std::string &publisher);
		void cancelSubscription(std::string &subscriber, std::string &publisher);

		void listNewCorrespondent(std::string &correspondentSignature, Correspondent* correspondent);
		void delistCorrespondent(std::string &correspondentSignature);

		void createCorrespondentSignature(std::string &signature);
		void removeCorrespondentSignature(std::string &signature);
		bool isCorrespondentSignature(std::string &signature);

	};

	class Correspondent
	{
		CorrespondentManager* mManager;
		std::map<std::string, Correspondent*> mSubscribers;
		std::shared_ptr<Message> mMessage;
		std::string mSignature;


	public:

		Correspondent();
		~Correspondent();

		void init(CorrespondentManager* manager, std::string &signature);
		void destroy();

		void passToSubscribers(std::shared_ptr<Message> messagePtr);

		void receiveSubscriber(std::string &subscriberSignature, Correspondent* subscriber = nullptr);
		void removeSubscriber(std::string &subscriberSignature);

		void publish();
		void publish(glm::vec2 mouseCoords);
		void publish(SDL_Event &evnt);

		void receiveMessage(std::shared_ptr<Message> message);

		bool getMessage();
		glm::vec2 getMouseMessage();
		SDL_Event getEventMessage();

		void clearMessage();


	};

	

}
