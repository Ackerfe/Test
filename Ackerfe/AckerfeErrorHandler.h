#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <SDL/SDL.h>
#include "InitFileReadWrite.h"

namespace Ackerfe 
{
	/*Restituisce la data e l'ora in formato: day-month-year hour-minute-second in modo da poter datare i file log degli errori*/
	std::string dateTime();
	
	/*Usa la funzione dateTime per stampare l'errore in un file che ha come nome la data in modo da avere i log di errore in ordine cronologico*/
	void throwFileError(std::string errorWord, std::string errorString);
	
	/*Stampa l'errore in console e chiede se si può ignorare l'errore e andare avanti(Usato solo in modalità debug)*/
	void throwConsoleError(std::string errorString);
	/*La funzione che viene usata in ogni altra parte dell'engine, decide se printare in console o in file leggendo la modalità impostata (debug o release) dal file ini
	  usa una errorString per definire l'errore e una errorWord che indica il tipo di errore*/
	void throwError(std::string errorWord, std::string errorString);
}

