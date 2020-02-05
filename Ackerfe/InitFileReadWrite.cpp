#include "InitFileReadWrite.h"
#include <fstream>
#include "ErrHandler.h"
namespace Ackerfe
{

	std::vector<std::string> Ackerfe::readInitFile()
	{
		std::vector<std::string> returnVector;
		std::string tempString;
		std::ifstream initFile("Ini.txt");
		if (initFile.is_open())
		{
			int initFileLine = 0;
			while (getline(initFile, tempString))
			{
				returnVector.push_back(tempString);
				initFileLine++;
			}

		}
		else
			Ackerfe::throwFileError("Inizializzazione", "Il file di inizializzazione manca o è corrotto");

		return returnVector;
	}

	std::vector<std::string> readFile(std::string & filePath)
	{
		std::vector<std::string> returnVector;
		std::string tempString;
		std::ifstream initFile(filePath);
		if (initFile.is_open())
		{
			int initFileLine = 0;
			while (getline(initFile, tempString))
			{
				returnVector.push_back(tempString);
				initFileLine++;
			}

		}
		else
			Ackerfe::throwFileError("Inizializzazione", "Il file di inizializzazione manca o è corrotto");

		return returnVector;
		return std::vector<std::string>();
	}

	std::string Ackerfe::readInitFileLine(unsigned int lineNumber)
	{
		std::string returnString = "";
		std::ifstream initFile("Ini.txt");
		if (initFile.is_open())
			for (unsigned int i = 0; i < lineNumber; i++)
				getline(initFile, returnString);
			
		else
			Ackerfe::throwFileError("Inizializzazione","Il file di inizializzazione manca o è corrotto");

		return returnString;
	}

	void Ackerfe::writeInitFile(std::vector<std::string> initContents)
	{
		std::ofstream initFile("Ini.txt");
		if (initFile.is_open())
			for (unsigned int i = 0; i < initContents.size(); i++)
				initFile << initContents[i] << std::endl;
		
		else
			Ackerfe::throwFileError("Inizializzazione", "Non è stato possibile creare il file di inizializzazione");
		
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
			Ackerfe::throwFileError("Inizializzazione", "Il file di inizializzazione manca o è corrotto");

		writeInitFile(tempFile);
	}

	void extractLinesFromFile(std::vector<std::string>* addTo, std::string & startMinusOne, std::string & endPlusOne, std::string & filePath)
	{
		unsigned int initSize = addTo->size();
		std::string tempString;
		std::fstream fileStream(filePath);
		if (fileStream.is_open())
		{
			while (getline(fileStream, tempString))
			{
				if (tempString == startMinusOne)
				{
					while (getline(fileStream, tempString))
					{
						if (tempString == endPlusOne)
							break;
						else
							addTo->push_back(tempString);

					}
				}
			}
		}
		else
			throwError(filePath, filePath + "is missing or corrupt");
		if (initSize == addTo->size())
			throwError("ReadFileError", "did not find anything between the lines " + startMinusOne + " and " + endPlusOne + "in file " + filePath);
	}

}