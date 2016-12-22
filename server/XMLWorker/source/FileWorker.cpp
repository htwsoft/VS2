/*
 * FileWorker.cpp
 * Methoden der FileWorker-Klasse
 * Created on: 15.12.2016
 * Author: Marco
 */

#include ".\FileWorker.h"
#include <cstdlib>
#include <fstream>
#include <iostream>

/*********************************************
* Methoden der FileWriter-Klasse             *
*********************************************/
FileWriter::FileWriter(string fileName):FileWorker(fileName)
{
	//Datei zum beschrieben oeffnen. Datei wird wird beim oeffnen
	//geloescht
	this->file = fstream(fileName, ios::out | ios::binary | ios::trunc );
	if(this->file.is_open())
	{

		//Datei-zeiger auf den Anfang der Datei setzen
		this->setzeDateiZeigerAufAnfang();
	}
	else
	{
		throw FEHLER_DATEI_NICHT_OFFEN;
	}
}

/*
* Methode schreibt in die aktuell geoffnete Datei
* ab der zuletzt gesetzten position
*/
void FileWriter::writeLine(string text, bool withNewLine)
{
	int laengeText = 0;
	char * buffer = 0;
	char zeichen = 0;
	/*
	* text muss in einen char * geschrieben werden
	* da file->write keinen string unterstuetzt
	*/
	laengeText = text.length();
	buffer = new char[laengeText+1];
	text.copy(buffer, laengeText, 0);
	buffer[laengeText+1] = '\0';
	//this->file.write(buffer, laengeText);
	for(int i=0; i<laengeText; i++)
	{
		/* eigene konvention fuer "/" 
		   wenn "/" in text stuerzt das Programm ab 
		   z.B. </test> zu: <//test>
		*/
		if(buffer[i] == '/' && buffer[i+1] == '/')
		{
			this->file.put(47);
			i = i+2;
		}
		zeichen = buffer[i];
		this->file.put(zeichen);
	}
	free(buffer);
	if(withNewLine)
	{
		this->file.put('\n');
	}
}

/*********************************************
* Methoden der FileReader-Klasse             *
*********************************************/

FileReader::FileReader(string fileName):FileWorker(fileName)
{
	//Laden bzw. erzeugend der Datei
	this->file = fstream(fileName, ios::in | ios::binary);
	if(this->file.is_open())
	{

		//Datei-zeiger auf den Anfang der Datei setzen
		this->setzeDateiZeigerAufAnfang();
	}
	else
	{
		throw FEHLER_DATEI_NICHT_OFFEN;
	}
}

/*
* Funktion liefert und liest eine ganze zeile einer Datei
*/
string FileReader::readLine()
{
	string line = "";
	/*
	* Prüfen ob die übergebene Datei geöffnet ist
	*/
	if(this->isFileOpen())
	{
		if(!this->file.eof())
		{
			getline(this->file, line);
		}
		this->file.flush();
	}
	return line;
}

/*********************************************
* Methoden der FileWorker-Klasse             *
*********************************************/

/*
* Konstruktor der FileWorker-Klasse
*/
FileWorker::FileWorker(string fileName)
{
	this->fileName = fileName;

}

/*
* Destruktor der FileWorker-Klasse
*/
FileWorker::~FileWorker()
{
	/*
	 * pruefen ob die Datei geoeffnet ist und erzeugt wurde , wenn ja datei schliessen
	 * */
	if(!this->file)
	{	
		if(this->file.is_open())
		{
			this->file.close();
		}
	}
}

/*
* funktion liefert die Aktuelle Zeiger-Position zurück
*/
int FileWorker::getAktPos()
{
	return this->file.tellg();	
}

/*
* Methode setzt den Datei-Zeiger auf den Anfang der Datei
*/
void FileWorker::setzeDateiZeigerAufAnfang()
{
	if(this->file.is_open())
	{
		this->setzeDateiZeigerAufPos(0);
	}		
}

/*
* Funkiton setzt den DateiZeiger auf die uebergebe Position in der Datei
*/
void FileWorker::setzeDateiZeigerAufPos(int pos)
{
	if(this->file.is_open())
	{
		this->file.seekg(pos, ios_base::beg);
	}
}

/*
* funktion kopiert ein String in ein char array
*/
void  FileWorker::copyStringToChar(string text, char * buffer)
{
		//funktioniert nicht. muss gucken warum
		//aus irgendeinem grund will er den buffer
		//nicht mitgeben
		int laengeText = 0;
		laengeText = text.length() + 1;
		buffer = (char*) malloc(laengeText * sizeof(char));
		text.copy(buffer, laengeText-1, 0);
		buffer[laengeText] = '\0';		
}

/*
* Pruefn ob das Ende der Datei erreicht ist
*/
void FileWorker::pruefeAufEof()
{
	/*
	* clear der Flags der Datei noetig,
	* da nach eof die Datei "geladen" werden muss
	*/	
	if(this->file.eof())
	{
		this->file.clear();
	}	
}

/*
* liefert den Namen der uebergebnen Datei zurueck
*/
string FileWorker::getFileName()
{
	return this->fileName;
}

/*
* Liefert true zurueck falls die Datei geoeffnet werden konnte
*/
bool FileWorker::isFileOpen()
{
	return this->file.is_open();
}

/*
* Liefert true zurueck falls das Dateiende erreicht wurde
*/
bool FileWorker::isEof()
{
	return this->file.eof();
}

/*
* Liefert das IsGood-Flag der fstream-Klasse
* ist true falls die letzte Operation erfolgreich war
*/
bool FileWorker::isGood()
{
	return this->file.good();
}