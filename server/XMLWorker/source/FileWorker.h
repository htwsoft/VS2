/*
 * FILEWORKER.h
 *
 *  Created on: 15.12.2016
 *  Author: Marco
 *  Klasse zum lesen einer Datei
 */

 /*
 * TO-DO doch unterteilung in XML-Reader und Writer
 */
 
#ifndef FILEWORKER_H_
#define FILEWORKER_H_

#include <iostream>
#include <fstream>
#include <string>
#include <sstream> 

using namespace std;


class FileWorker
{
	protected:
		const char * FEHLER_DATEI_NICHT_OFFEN  = "Datei konnte nicht geoeffnet werden!\n";
		fstream file;
		string fileName;
		void copyStringToChar(string text, char * buffer);
		void pruefeAufEof();
	public:
		FileWorker(string fileName);
		~FileWorker();
		int getAktPos();
		void setzeDateiZeigerAufAnfang();
		void setzeDateiZeigerAufPos(int pos);		
		bool isFileOpen();
		bool isEof();
		bool isGood();
		string getFileName();
};

/*
* Klasse FileWriter zum beschreiben einer Datei
*/
class FileWriter: public FileWorker
{
	public:
		FileWriter(string fileName);
		~FileWriter(){};
		void writeLine(string text, bool withNewLine);
};

/*
* Klasse FileReader zum Lesen einer Datei
*/
class FileReader: public FileWorker
{
	public:
		FileReader(string fileName);
		~FileReader(){};
		string readLine();
};
#endif /* FILEWORKER_H_ */
