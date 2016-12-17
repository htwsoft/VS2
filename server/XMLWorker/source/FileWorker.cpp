/*
 * FileWorker.cpp
 * Methoden der FileWorker-Klasse
 * Created on: 15.12.2016
 * Author: Marco
 */

#include "FileWorker.h"
#include <cstdlib>
#include <fstream>
#include <iostream>


/*
* Konstruktor der FileWorker-Klasse
*/
FileWorker::FileWorker(string fileName)
{
	//Laden bzw. erzeugend der Datei
	file = fstream(fileName, ios::in | ios::out | ios::binary);
	this->fileName = fileName;
	//Datei-zeiger auf den Anfang der Datei setzen
	this->setzeDateiZeigerAufAnfang();
}

/*
* Destruktor der FileWorker-Klasse
*/
FileWorker::~FileWorker()
{
	/*
	 * pruefen ob die Datei geoeffnet ist, wenn ja datei schliessen
	 * */
	if(this->file.is_open())
	{
		this->file.close();
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
* Methode dient zum schreiben von Messages auf der shell
*/
void FileWorker::writeDebugMessage(string text)
{
	cout << "Debug: " << text << endl;	
}

/*
* Methode dient zum schreiben von Messages auf der shell
*/
void FileWorker::writeDebugMessage(int zahl)
{
	cout << "Debug: " << zahl << endl;	
}

/*
* Methode schreibt in die aktuell geoffnete Datei
* ab der zuletzt gesetzten position
*/
void FileWorker::writeLine(string text)
{
	int aktPos = 0;
	string dateiAbPos = "";	
	//aktueller Lesezeiger merken
	aktPos = this->getAktPos();
	/*
	* dateiAbPos wird benoetigt,
	* da die Datei beim einfuegen des neuen Textes sonst
	* ab der Stelle des Lesezeigers ueberschrieben wird
	*/
	//datei von lesezeiger bis zu ende lesen
	dateiAbPos = this->leseDateiAbPos(aktPos);
	//neuen Text in Datei anhaengen
	this->ueberschreibeDatei(text, dateiAbPos, aktPos);
	/* 
	* Datei wieder auf die letzte position des 
	* lesezeiger setzen 
	*/
	this->setzeDateiZeigerAufPos(aktPos);
}

/*
* funktion ueberschriebt die aktuelle Datei mitb dem uebergebenen
* text
*/
void FileWorker::ueberschreibeDatei(string textNew, string textDanach, int pos)
{
	int laengeText = 0;
	char * buffer = 0;
	if(this->file.is_open())
	{
		/* schreibeZeigerAuf Anfang setzen um Datei quasi 
		* "ueberschreiben" mit neuem Text
		*/
		this->setzeDateiZeigerAufPos(pos);
		/*
		* text muss in einen char * geschrieben werden
		* da file->write keinen string unterstuetzt
		*/
		laengeText = textNew.length();
		buffer = new char[laengeText+1];
		textNew.copy(buffer, laengeText, 0);
		buffer[laengeText+1] = '\0';
		this->file.write(buffer, laengeText);
		free(buffer);
		
		this->file.put('\r');
		this->file.put('\n');
		
		laengeText = textDanach.length();
		buffer = new char[laengeText+1];
		textDanach.copy(buffer, laengeText, 0);
		buffer[laengeText+1] = '\0';
		this->file.write(buffer, laengeText-1);
		free(buffer);		
	}
	this->pruefeAufEof();
	this->setzeDateiZeigerAufAnfang();
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
		cout << buffer << endl;
}

/*
* Funktion liefert und liest eine ganze zeile einer Datei
*/
string FileWorker::readLine()
{
	string line = "";
	char zeichen = '\0';
	/*
	* Prüfen ob die übergebene Datei geöffnet ist
	*/
	if(this->isFileOpen())
	{
		while( !this->file.eof() && zeichen != '\n' )
		{
			//lesen des naechsten Zeichens
			this->file.get(zeichen);
			//Gelesene Zeichen zusammensetzen
			line = line + zeichen;
		}
		this->file.flush();
	}
	return line;
}

/*
* funktion liest den restlichen inhalt einer Datei ab der
* uebergebnen Position. ist noetig um einen Text in mitten
* einer Datei anzuhaengen
*/
string FileWorker::leseDateiBisPos(int pos)
{
	string text = "";
	char * buffer = 0;
	//Pruefen ob Datei geoffnet ist
	if(this->isFileOpen() && pos > 0)
	{
		buffer = new char[pos+1];
		buffer[pos] = '\0';
		//Zeiger an entsprechende Position setzen
		this->setzeDateiZeigerAufAnfang();
		//Daten lesen
		this->file.read(buffer, pos);
		text = text + buffer;
	}
	//Pruefn ob das Ende der Datei erreicht ist
	//Falls ja diesen Status zuruecksetzen,
	//da sonst keine Operationen mehr moeglich
	this->pruefeAufEof();
	return text;
}

/*
* Funktion ist wie leseDateiBisPos, liest
* allerdings den Inhalt ab einer bestimmten Position
*/
string FileWorker::leseDateiAbPos(int pos)
{
	string text = "";
	if(this->isFileOpen())
	{
		this->setzeDateiZeigerAufPos(pos);	
		while(!this->file.eof())
		{
			text = text + this->readLine();
		}		
	}
	this->pruefeAufEof();
	return text;
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