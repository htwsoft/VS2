/*
 * FILEWORKER.h
 *
 *  Created on: 15.12.2016
 *  Author: Marco
 *  Klasse zum lesen einer Datei
 */

#ifndef FILEWORKER_H_
#define FILEWORKER_H_

#include <iostream>
#include <fstream>
#include <String>
#include <sstream> 

using namespace std;


class FileWorker
{
	private:
		fstream file;
		string fileName;
		void copyStringToChar(string text, char * buffer);
		string leseDateiAbPos(int pos);
		string leseDateiBisPos(int pos);
		void ueberschreibeDatei(string textNew, string textDanach, int pos);
		void writeDebugMessage(string text);
		void writeDebugMessage(int text);
		void pruefeAufEof();
	public:
		FileWorker(string fileName);
		~FileWorker();
		int getAktPos();
		bool isFileOpen();
		bool isEof();
		bool isGood();
		void writeLine(string text);
		void setzeDateiZeigerAufAnfang();
		void setzeDateiZeigerAufPos(int pos);
		string readLine();
		string getFileName();
};


#endif /* FILEWORKER_H_ */
