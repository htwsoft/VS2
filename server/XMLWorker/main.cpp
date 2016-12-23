/*
 * main.cpp
 * Programm zum Testen der XMLWorker klasse
 *  Created on: 15.12.2016
 *      Author: Marco
 */

#include ".\source\FileWorker.h"
#include ".\source\XMLWorkerTest.h"
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

/* Testen ob FileReader funktioniert */

void testeFileReader(string fileName)
{
	FileReader * freader;
	
	cout << "testeFileReader: " << fileName << endl;
	freader = new FileReader(fileName);
	while(!freader->isEof())
	{
		cout << freader->readLine() << endl;
	}
	delete freader;	
	cout << endl;
}

/* Testen ob FileWriter funktioniert */
void testeFileWriter(string fileName)
{
	FileWriter * fwriter;
	
	cout << "testeFileWriter: " << fileName << endl;
	fwriter = new FileWriter(fileName);
	fwriter->writeLine("<Test>", true);
	fwriter->writeLine("  <Test1>Value</Test1>", true);
	fwriter->writeLine("  <Test2>Value</Test2>", true);
	fwriter->writeLine("<//Test>", false);
	delete fwriter;	
}

void testeXMLWorker(string fileName)
{
	XMLWorkerTest * xmltest;
	xmltest = new XMLWorkerTest();
	xmltest->starteTest();
	delete xmltest;
}

int main(int argc, char * args[])
{
	cout << endl;
	writeLine("Starte Programm:");
	writeLine("----------------");
	if(argc > 1)
	{
		testeXMLWorker(args[1]);
	}
	else
	{
		writeLine("Zu wenig/viele Parameter!");
	}	
	return 0;
}

