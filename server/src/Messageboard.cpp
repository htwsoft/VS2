/*
 * Messageboard.cpp
 *
 *  Created on: 21.12.2016
 *      Author: Christian Patzek
 */

#include "./Messageboard.h"
#include <cstdlib>
#include <string>

//TO-DO Informationen aus XML laden um Board zu initialisieren, anschließend orb starten(port öffnen und listen)
Messageboard::Messageboard(string xmlPath)
{
	this->xmlPath = xmlPath;
	this->xml = NULL;
	/* first = XML
	 * last = XML
	 * size = XML
	 * id = XML
	 * name = XML
	 * fatherId = XML
	 * fatherName = XML
	 * childIds** = XML
	 * childNames** = XML
	 * childs** = XML ConnectInformations aller kinder
	 * father = XML ConnectInformation vater
	 * ConnectInformation = XML
	 */
	 
	highlighted=first;
	//hier orb starten, sprich port öffnen und lauschen
}

//TO-DO wahrscheinlich nicht komplett, das Verfahren hier loescht nur alle Nachrichten auf dem Board
Messageboard::~Messageboard()
{
	if(first == 0)
	{
		throw "Liste ist leer";
	}

	Message* tmp;

	for(int i = 0; i < size; i++)
	{
		tmp = first;
	    first = first->getNext();
	    delete tmp;
	}
	size -= size;
	highlighted = 0;
	saveMessages();
}
//TO-DO das komplette board(also alle Informationen und Messages) in einer XML datei speichern
void Messageboard::saveMessages()
{}

string Messageboard::getFatherName()
{
	return fatherName;
}

string** Messageboard::getChildNames()
{
	return childNames;
}

Message Messageboard::getNextMessage()
{
	if(highlighted->getNext() != NULL)
	{
		highlighted = highlighted->getNext();

	}
	return * highlighted;
}

Message Messageboard::getPreviousMessage()
{
	if(highlighted->getPrevious() != NULL)
	{
		highlighted = highlighted->getPrevious();
	}
	return *highlighted;
}

bool Messageboard::setMessage(string message, int uid, string uName)
{
	if(confirmAdminRights(uid))
	{
		highlighted->setUid(uid);highlighted->setMessage(message);
		return true;
	}
	else if(confirmMessageRights(uid))
	{
		highlighted->setUid(uid);highlighted->setMessage(message);
		return true;
	}
	return false;
}

bool Messageboard::createNewMessage(string message, int uid, string uName)
{
	Message* neu = NULL;

	if(first == 0)
	{
		neu = new Message(message, uid, 0, 0, uName);
		first = neu;
		last = neu;
	}
	else
	{
		neu = new Message(message, uid, neu, 0, uName);
		neu->getNext()->setPrevious(neu);
		first = neu;
		highlighted = neu;
	}
	++size;
	saveMessages();
	return true;
}

//TO-DO XML-Abfrage
bool Messageboard::confirmAdminRights(int uid)
{
	bool assert = true;//XML-Abfrage, prüfe uid. sprich abfrage auf admin. Ueberpruefung mit der Datenbank vom Login-Server
	return assert;
}
//TO-DO
bool Messageboard::confirmMessageRights(int uid)
{
	bool assert = true;//XML-Abfrage, prüfe uid. sprich ob eigentümer der nachricht
	return assert;
}

bool Messageboard::deleteMessage(int uid)
{
	if(confirmAdminRights(uid))
	{
		erase();
		saveMessages();
		return true;
	}
	else if(confirmMessageRights(uid))
	{
		erase();
		saveMessages();
		return true;
	}
	return false;
}

void Messageboard::erase()
{
	if(highlighted==NULL)
	{
		//TO-DO
		throw "leer";
	}
	else if(first == last)
	{
		first = 0;
		last = 0;
		Message* tmp = highlighted;
		highlighted = first;
		delete tmp;
	}
	else if((highlighted->getNext() == last)&&(highlighted->getPrevious() == NULL))
	{
		first = last;
		highlighted->getNext()->setPrevious(0);
		Message* tmp = highlighted;
		highlighted = first;
		delete tmp;
	}
	else if((highlighted->getPrevious() == first)&&(highlighted->getNext()==NULL))
	{
		last = first;
		highlighted->getPrevious()->setNext(0);
		Message* tmp = highlighted;
		highlighted = first;
		delete tmp;
	}
	else if(highlighted->getPrevious()==NULL)
	{
		first = first->getNext();
		first->setPrevious(0);
		Message* tmp = highlighted;
		highlighted = first;
		delete tmp;
	}
	else if(highlighted->getNext()==NULL)
	{
		last = last->getPrevious();
		last->setNext(0);
		Message* tmp = highlighted;
		highlighted = last;
		delete tmp;
	}
	else
	{
		Message* tmp = highlighted;
		highlighted->getNext()->setPrevious( highlighted->getPrevious() );
		highlighted->getPrevious()->setNext( highlighted->getNext() );
		highlighted = highlighted->getPrevious();
		delete tmp;
	}
}

ConnectInformation * Messageboard::connectToFather()
{
	return father;
}

ConnectInformation * Messageboard::connectToChild(string childName)
{
	for(int i = 0; i < NUM_CHILDREN; i++)
	{
		if(childName.compare(childNames[i]) == 0) //childNames[i]==childName
		{
			return childs[i];
		}
	}
	throw "no such child";
}
//TO-DO Verbindungen zu anderen Servern, weiß noch nicht genau wie das funktioniert in CORBA :D
bool Messageboard::iterateChilds(string message, int uid, string uName, bool schalter)
{
	bool assert;
	for(int i = 0; i < NUM_CHILDREN; i++)
	{
		//Verbindung aufbauen zu childs[i]nacheinander(ConnectInformation)
		assert = publishChild(message, uid, uName, schalter);
		//Verbindung abbauen zum aktuellen childs[i]
		if(!assert)
			return false;
	}
	return assert;
}
//TO-DO
bool Messageboard::publishOnFather(string message, int uid, string uName)
{
	//Verbindung aufbauen zu father
	return publishFather(message, uid, uName);
}
//TO-DO
bool Messageboard::publishChild(string message, int uid, string uName, bool schalter)
{
	if(confirmAdminRights(uid) && NUM_CHILDREN > 1)//Ueberpruefung mit der Datenbank vom Login-Server und ob Knoten ueberhaupt kinder hat
	{
		createNewMessage(message, uid, uName);
		if(schalter)
		{
			iterateChilds(message, uid, uName, schalter);
		}
		return true;
	}
	else
		return false;
}

bool Messageboard::publishFather(string message, int uid, string uName)
{
	if(confirmAdminRights(uid))
	{
		createNewMessage(message, uid, uName);
		return true;
	}
	else
		return false;
}
//TO-DO
void Messageboard::notifyFather()
{
	//Verbindung aufbauen zu ConnectInformation father und dort dann sagen er soll dich als kind speichern
	saveChildrenInformation(id,name,connectInformation);//aufruf dieser Funktion auf vaterseite!
	//Verbindung abbauen
}
//TO-DO
void Messageboard::saveChildrenInformation(int id, string name, ConnectInformation connectInformation)
{
	childIds[NUM_CHILDREN] = id;
	childNames[NUM_CHILDREN] = name;
	childs[NUM_CHILDREN] = connectInformation;
	NUM_CHILDREN++;
	saveMessages();
}
//TO-DO
void Messageboard::notifyChildren()
{
	for(int i = 0; i < NUM_CHILDREN; i++)
	{
		//Verbindung aufbauen zu childs[i]
		saveFatherInformation(id, name, connectInformation);//Funktion auf seite der kinder aufrufen!
		//Verbindung abbauen
	}
}
//TO-DO
void Messageboard::saveFatherInformation(int id, string name, ConnectInformation connectInformation)
{
	fatherId = id;
	fatherName = name;
	father = connectInformation;
	saveMessages();
}

