/*
 * main.cpp
 * Programm zum Testen der XMLWorker klasse
 *  Created on: 15.12.2016
 *      Author: Marco
 */

#include ".\source\FileWorker.h"
#include <iostream>
#include <string>
#include <cstdlib>


using namespace std;


string intToString(int zahl)
{
	ostringstream stream;
	stream << zahl;
	return stream.str();
}

void writeLine(string text)
{
	cout << text << endl;
}

void readFile(string fileName)
{
	FileWorker * freader;
	bool test = false;
	
	freader = new FileWorker(fileName);
	if(freader->isFileOpen())
	{
		while(!freader->isEof())
		{
			cout << freader->readLine() << endl;
			if(!test)
			{
				freader->writeLine("<Test>01234</Test>");
				test = true;
			}
		}
		cout << "Ende!" << endl;
	}
	else
	{
		cout << "Datei konnte nicht geoeffnet werden!" << endl;
	}
	free(freader);	
}

void readParameter(int argc, char * args[])
{
	string text;
	writeLine("Parameter: " + intToString(argc-1) );
	writeLine("----------------");
	for(int i=1; i<argc; i++)
	{
		text = intToString(i) + ": " + static_cast<string>(args[i]);
		writeLine(text);
	}
	writeLine("----------------");
}

int main(int argc, char * args[])
{
	cout << endl;
	writeLine("Starte Programm:");
	writeLine("----------------");
	if(argc > 1)
	{
		//readParameter(argc, args);
		readFile(args[1]);	
	}
	else
	{
		writeLine("Zu wenig/viele Parameter!");
	}	
	writeLine("----------------");
	writeLine("Programm Ende!");
	return 0;
}

