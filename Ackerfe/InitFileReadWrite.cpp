#include "InitFileReadWrite.h"
#include <fstream>
#include "AckerfeErrorHandler.h"
namespace Ackerfe
{

	std::vector<std::string> Ackerfe::readInitFile()
	{
		std::vector<std::string> returnVector;
		std::ifstream initFile("Ini.txt");
		if (initFile.is_open())
		{
			int initFileLine = 0;
			while (getline(initFile, returnVector[initFileLine]))
				initFileLine++;

		}
		else
			Ackerfe::throwFileError("Inizializzazione", "Il file di inizializzazione manca o � corrotto");

		return returnVector;
	}

	std::string Ackerfe::readInitFileLine(unsigned int lineNumber)
	{
		std::string returnString = "";
		std::ifstream initFile("Ini.txt");
		if (initFile.is_open())
			for (unsigned int i = 0; i < lineNumber; i++)
				getline(initFile, returnString);
			
		else
			Ackerfe::throwFileError("Inizializzazione","Il file di inizializzazione manca o � corrotto");

		return returnString;
	}

	void Ackerfe::writeInitFile(std::vector<std::string> initContents)
	{
		std::ofstream initFile("Ini.txt");
		if (initFile.is_open())
			for (unsigned int i = 0; i < initContents.size(); i++)
				initFile << initContents[i] << std::endl;
		
		else
			Ackerfe::throwFileError("Inizializzazione", "Non � stato possibile creare il file di inizializzazione");
		
	}

	void Ackerfe::writeInitFileLine(unsigned int lineNumber, std::string replacementString)
	{
		std::string tempString;
		std::vector<std::string> tempFile;
		std::ifstream initFile("Ini.txt");
		unsigned int iterator = 1;

		if (initFile.is_open()) 
			while (getline(initFile, tempString))
			{
				if (iterator == lineNumber)
					tempFile.push_back(replacementString);

				else
					tempFile.push_back(tempString);

				iterator++;
			}

		else
			Ackerfe::throwFileError("Inizializzazione", "Il file di inizializzazione manca o � corrotto");

		writeInitFile(tempFile);
	}

}