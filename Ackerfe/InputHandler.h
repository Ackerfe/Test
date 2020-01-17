#pragma once
#include <unordered_map>
namespace Ackerfe
{
	class InputHandler
	{
		std::unordered_map<unsigned int, bool> mKeyMap;


	public:
		InputHandler();
		~InputHandler();

		/*Viene chiamata quando il giocatore preme un tasto in modo che possa essere messa a confronto con la mKeyMap*/
		void pressKey(unsigned int keyID);
		/*Controlla se il tasto è premuto al momento*/
		bool isKeyDown(unsigned int keyID);
		/*Ricorda i tasti premuti in modo che possano essere utilizzati dal programma in ordine*/
		void inputQueue();

	};
}
