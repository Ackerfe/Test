#pragma once
#include <string>
#include <vector>

namespace Ackerfe
{
	/*Legge il file ini e fa sì che possa essere usato dal programma*/
	std::vector<std::string> readInitFile();
	/*Seleziona una sola riga dal file ini e la rende usabile dal programma*/
	std::string readInitFileLine(unsigned int lineNumber);
	/*Scrive o sostituisce il file ini con il vettore di righe initContents*/
	void writeInitFile(std::vector<std::string> initContents);
	/*Sostituisce la riga lineNumber del file ini con la stringa replacementString*/
	void writeInitFileLine(unsigned int lineNumber, std::string replacementString);

}

