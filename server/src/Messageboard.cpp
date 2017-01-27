/*
 * Messageboard.cpp
 *
 *  Created on: 21.12.2016
 *      Author: Christian Patzek und Marco Palumbo
 */

#include "./Messageboard.h"
#include "../XMLWorker/source/XMLWorker.h"
#include <cstring>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <sstream>

//TO-DO wahrscheinlich nicht komplett, das Verfahren hier loescht nur alle Nachrichten auf dem Board
Messageboard::~Messageboard()
{
	saveBoard();
	this->clearMessages();
	this->clearBoardInformations();
}

//TO-DO Informationen aus XML laden um Board zu initialisieren, anschlie�end orb starten(port �ffnen und listen)
Messageboard::Messageboard(string xmlPath)
{
	this->xmlPath = xmlPath;
	this->xml = new XMLWorker();
	this->size = 0;
	this->boardInformation = NULL;
	this->mIdCounter = 0;
	this->first = NULL;
	this->last = NULL;
	this->highlighted = NULL;
	this->initBoardXML();
	//this->highlighted = this->first;
	//hier orb starten, sprich port �ffnen und lauschen (wird in eine neue Klasse ausgelagert da Code sonst zu gro�)
}

/* Konstruktor falls ein neues Board erstellt werden soll */
Messageboard::Messageboard(int id, string name)
{
	this->xmlPath = "./MessageBoard.xml";
	this->xml = new XMLWorker();
	this->size = 0;
	this->boardInformation = new BoardInformation(name, id, NULL);
	this->mIdCounter = 0;
	this->first = NULL;
	this->last = NULL;
	this->highlighted = NULL;
	
}

//Speichern eines neuen Childs
void Messageboard::saveChildrenInformation(int id, string name, ConnectInformation * connectInformation)
{
	BoardInformation * child = 0;
	child = new BoardInformation(name, id, connectInformation);
	childs.push_back(child);
	saveBoard();
}

/* das komplette board(also alle Informationen und Messages) in einer XML datei speichern */
void Messageboard::saveBoard()
{
	XMLNode * rootNode = 0;
	XMLNode * messagesNode = 0;
	XMLNode * connectInformationNode = 0;
	//Durch Create RootNode wird die zuvor gespeicherte XML gel�scht
	this->xml->createRootNode("messageboard");
	rootNode = this->xml->getRootNode();
	//Speichern der eigenen Informationen des Boards
	this->saveBoardInformations(rootNode);
	//Node "messages" zum speicher der Nachrichten
	messagesNode = rootNode->addChild("messages", "", false);
	this->saveMessages(messagesNode);
	connectInformationNode = rootNode->addChild("connectInformations", "", false);
	this->saveConnectInformations(connectInformationNode);
	//Speichern des Messageboards
	this->xml->saveXML(this->xmlPath);
}

/* speichern der ConnectInformations von Child und Father */
void Messageboard::saveConnectInformations(XMLNode * fatherNode)
{
	XMLNode * fatherConnectNode = 0;
	XMLNode * childConnectNode = 0;	
	//Speichern der ConnectInformations des FatherBoards
	fatherConnectNode = fatherNode->addChild("father", "", false);
	this->saveFatherConnectInformation(fatherConnectNode);
	//Speichern der ChildConnect Informations in der XML
	childConnectNode = fatherNode->addChild("childs", "", false);
	this->saveChildConnectInformations(childConnectNode);
}

/* speichern der ConnectInformatiosn des Childs */
void Messageboard::saveChildConnectInformations(XMLNode * fatherNode)
{
	XMLNode * childNode = 0;
	BoardInformation * child = 0;
	string name = "";
	string ip = "";
	string port = "";
	string id = "";
	if(this->childs.size() > 0)
	{
		//alle Childs suchen und in der XML speichern
		for(iterChilds=this->childs.begin(); iterChilds<this->childs.end(); iterChilds++)
		{
			child = *iterChilds;
			childNode = fatherNode->addChild("child", "", false);

			id = this->intToStr(child->getId());
			name = child->getName();
			ip = child->getConnectInformation()->getIp();
			port = this->intToStr(child->getConnectInformation()->getPort());
			
			//Hinzufuegen der richtigen Nodes fuer ein child
			childNode->addChild("name", name, false);
			childNode->addChild("ip", ip, false);
			childNode->addChild("port", port, false);
			childNode->addAttribut("id", id);
		}
	}		
}

/* Speichern der ConnectInformations des Fathers in der XML */
void Messageboard::saveFatherConnectInformation(XMLNode * fatherNode)
{
	string id = "";
	string name = "";
	string ip = "";
	string port = "";
	if(this->father != NULL)
	{
		id = this->intToStr(this->father->getId());
		name = this->father->getName();
		ip = this->father->getConnectInformation()->getIp();
		port = this->intToStr(this->father->getConnectInformation()->getPort());
		//Hinzufuegen der richtigen Nodes fuer den vater
		fatherNode->addChild("name", name, false);
		fatherNode->addChild("ip", ip, false);
		fatherNode->addChild("port", port, false);
		fatherNode->addAttribut("id", id);
	}
}

/* speichern der Messages in der XML */
void Messageboard::saveMessages(XMLNode * fatherNode)
{
	Message * worker = NULL;
	XMLNode * messageNode = NULL;
	string message = "";
	string messageId = "";
	string userId = "";
	//Ab hier werden die nachrichten gespeichert
	worker = this->first;
	while(worker != NULL)
	{
		//lesen der Message-Daten
		message = worker->getMessage();
		messageId = worker->getId();
		userId = this->intToStr(worker->getUid());
		//erstellen der <message> node
		messageNode = fatherNode->addChild("message", "", false);
		messageNode->addChild("text", message, false);
		messageNode->addChild("uid", userId, false);
		messageNode->addAttribut("id", messageId);
		//Naechste Nachricht
		worker = worker->getNext();
	}
}


/* Speichern der eigenen Informationen des Messageboards in der XML */
void Messageboard::saveBoardInformations(XMLNode * fatherNode)
{
	string messageIdCounter = ""; //nachrichten zaehler zur generierun neuer MessageIDs
	string messageCount = ""; //Anzahl nachrichten
	string boardId = ""; //Id des Messageboards
	
	messageIdCounter = this->intToStr(this->mIdCounter);
	messageCount = this->intToStr(this->size);
	boardId = this->intToStr(this->boardInformation->getId());
	fatherNode->addChild("name", this->boardInformation->getName(), false);
	fatherNode->addChild("mcounter", messageCount, false);
	fatherNode->addChild("idcounter", messageIdCounter, false);	
	fatherNode->addAttribut("id", boardId);
}

/* loeschen der gespeichertn ConnectInformations */
void Messageboard::clearBoardInformations()
{
	//loeschen der father ConnectInfo
	delete this->father;
	//loeschen der childConnectInfos
	if(this->childs.size() > 0)
	{
		//alle Childs suchen und im Speicher freigeben
		for(iterChilds=this->childs.begin(); iterChilds<this->childs.end(); iterChilds++)
		{
			delete *iterChilds;
		}
		childs.clear();	
	}	
}

/* Loeschen der gespeicherten Nachrichten */
void Messageboard::clearMessages()
{
	if(first != 0)
	{
		Message * tmp;
		for(int i = 0; i < this->size; i++)
		{
			tmp = first;
			first = first->getNext();
			delete tmp;
		}
		size = 0;
		highlighted = 0;
	}
}


/* auswerten der XML und speichern im Messageboard */
void Messageboard::initBoardXML()
{
	//laden der XML
	this->xml->loadXML(this->xmlPath);
	this->initMessages();
	this->initMessageIdCounter();
	this->initBoardInformations();
	this->initConnectInfos();
}

/* Erstellt die Id fuer eine neue Message */
string Messageboard::createNewMessageId()
{
	string newMessageID = "";
	this->mIdCounter++;
	newMessageID = intToStr(this->boardInformation->getId()) + "-" + intToStr(this->mIdCounter);
	return newMessageID;
}

/* funktion wandelt einen Integerwert in einen String */
string Messageboard::intToStr(int number)
{
	ostringstream converter;
	converter << number;
	return converter.str();
}

/* Liest die ConnectInfos aus der XML */
void Messageboard::initConnectInfos()
{
	XMLNode * rootNode = 0;
	XMLNode * workNode = 0;
	XMLNode * connectInfoNode = 0;
	rootNode = this->xml->getRootNode();
	if(rootNode != NULL)
	{
		this->xml->setWorkNode(rootNode);
		//Suchen der Node mit den ConnectInfos 
		connectInfoNode = this->xml->getChildNodeWithName("connectInformations");
		if(connectInfoNode != NULL)
		{
			this->xml->setWorkNode(connectInfoNode);
			//ConnectInfos der FatherNode ermitteln
			workNode = this->xml->getChildNodeWithName("father");
			this->initFatherNodeConnectInfos(workNode);
			this->xml->setWorkNode(connectInfoNode);
			//FatherNode fuer Child ConnectInfos finden
			workNode = this->xml->getChildNodeWithName("childs");
			this->initChildConnectInfos(workNode);
		}
	}
}

/* Lesen der ConnectInfos der Childs aus der XML */
void Messageboard::initChildConnectInfos(XMLNode * node)
{
	XMLNode * workNode = 0;
	int childCount = 0;
	if(node != NULL)
	{
		//Ermitteln wie viele Child-ConnectInfos in der XML sind
		childCount = node->getChildCount();
		if(childCount > 0)
		{
			//Abarbeiten der einzelnen Eintraege
			for( int i=0; i < childCount; i++)
			{
				workNode = node->getChild(i);
				this->initChild(workNode);
			}
		}
	}
}

/* Liest die Daten eines Childboards aus der XML */
void Messageboard::initChild(XMLNode * node)
{
	XMLNode * workNode = 0;
	string ip = "";
	int port = 0;
	string name = "";
	int id = 0;
	string strPort = "";
	string strId = "";
	string nodeName = "";
	int paramCount = 0;
	ConnectInformation * connectInformation = NULL;
	paramCount = node->getChildCount();
	for(int i=0; i < paramCount; i++)
	{
		workNode = node->getChild(i);
		nodeName = workNode->getName();
		if(nodeName.compare("name") == 0)
		{
			name = workNode->getValue();		
		}
		else
		if(nodeName.compare("id") == 0)
		{
			strId = workNode->getValue();
			id = atoi(strId.c_str());		
		}
		else
		if(nodeName.compare("ip") == 0)
		{
			ip = workNode->getValue();		
		}
		else
		if(nodeName.compare("port") == 0)
		{
			strPort = workNode->getValue();
			port = atoi(strPort.c_str());		
		}
	}
	//Prufen ob id wert angegeben ist
	if(node->getAttributCount() > 0)
	{
		//Auslesend er Message ID
		strId = node->getAttribut(0)->getValue();
		id = atoi(strId.c_str());	
	}
	connectInformation = new ConnectInformation(ip, port);
	this->childs.push_back(new BoardInformation(name, id, connectInformation));
}

/* Lesen der Father-ConnectInfos aus der XML */
void Messageboard::initFatherNodeConnectInfos(XMLNode * node)
{
	XMLNode * workNode = 0;
	string ip = "";
	int port = 0;
	string strPort = "";
	int id = 0;
	string strId = "";
	string name = "";
	ConnectInformation * connectInformation = NULL;
	
	this->xml->setWorkNode(node);
	workNode = this->xml->getChildNodeWithName("ip");
	if(workNode != NULL)
	{
		ip = workNode->getValue();
	}
	workNode = this->xml->getChildNodeWithName("port");
	if(workNode != NULL)
	{
		strPort = workNode->getValue();
		port = atoi(strPort.c_str());
	}
	workNode = this->xml->getChildNodeWithName("name");
	if(workNode != NULL)
	{
		name = workNode->getValue();
	}
	//Prufen ob id wert angegeben ist
	if(node->getAttributCount() > 0)
	{
		//Auslesend er Message ID
		strId = node->getAttribut(0)->getValue();
		id = atoi(strId.c_str());	
	}
	//Pruefen ob Port und IP gefunden wurden
	if(port > 0 && ip.compare("") != 0)
	{
		connectInformation = new ConnectInformation(ip, port);
		this->father = new BoardInformation(name, id, connectInformation);
	}
}

/* Liest den MessageboardNamen aus der XML */
void Messageboard::initBoardInformations()
{
	XMLNode * rootNode = 0;
	XMLNode * workNode = 0;
	XMLAttribut * idAttr = 0;
	string name = "";
	string strId = "";
	int id = 0;
	rootNode = this->xml->getRootNode();
	if(rootNode != NULL)
	{
		this->xml->setWorkNode(rootNode);
		//Suchen der Node fuer den Board Namen
		workNode = this->xml->getChildNodeWithName("name");
		if(workNode != NULL)
		{
			name = workNode->getValue();
		}
					
		
		//suchen der board id
		if(rootNode->getAttributCount() > 0)
		{
			idAttr = rootNode->getAttribut(0);
			strId = idAttr->getValue();
			id = atoi(strId.c_str());
		}
	}
	this->boardInformation = new BoardInformation(name, id, NULL);
}

/* Funktion liest den Message ID Counter aus der XML,
 * damit Nachrichten des Boards eine eindeutige ID 
 * bekommen
 */
void Messageboard::initMessageIdCounter()
{
	XMLNode * workNode;
	XMLNode * rootNode;
	string idCounter;
	rootNode = this->xml->getRootNode();
	if(rootNode != NULL)
	{
		this->xml->setWorkNode(rootNode);
		//Suchen der Node fuer den Message-ID-Counter
		workNode = this->xml->getChildNodeWithName("idcounter");
		if(workNode != NULL)
		{
			idCounter = workNode->getValue();
			this->mIdCounter = atoi(idCounter.c_str());
		}
	}
}

void Messageboard::initMessages()
{
	XMLNode * messageFatherNode = 0; // Node "messages"
	XMLNode * messageNode = 0; //Node "message"
	int messageCount = 0;
	//Pruefen ob inhalt in der XML-Klasse vorhanden ist
	if(this->xml->getRootNode() != NULL)
	{
		//suchen der rootnode fuer messages
		messageFatherNode = this->xml->getChildNodeWithName("messages");
		if(messageFatherNode != NULL)
		{
			//Neuste Nachricht steht in der XML ganz vorne
			messageCount = messageFatherNode->getChildCount();
			for(int i = messageCount-1; i >= 0; i--)
			{
				//Laden der einzelnen Meessages eines Messageboards
				messageNode = messageFatherNode->getChild(i);
				this->initMessage(messageNode);
			}
		}		
	}
}
/* Liest den Inhalt einer Message aus der XML */
void Messageboard::initMessage(XMLNode * node)
{
	string message = ""; //Message-Text
	string mid = ""; //MessageID
	string nodeName = "";
	string value = "";
	int uid = 0; //User-ID der Message
	int anzChildNodes = 0; //Anzahl der Nodes Innerhalb einer Message	
	XMLNode * workNode = 0;
	//Abarbeiten der einzelnen Nodes innerhalb einer Message
	anzChildNodes = node->getChildCount();
	for(int i=0;  i < anzChildNodes; i++)
	{
		workNode = node->getChild(i);
		nodeName = workNode->getName();
		//Pruefen ob Node = User-ID der Message
		if(nodeName.compare("uid") == 0)
		{
			value = workNode->getValue();
			//Integer in String umwandeln
			uid = atoi(value.c_str());
		}
		else
		//Pruefen ob Node = Text der Message
		if(nodeName.compare("text") == 0)
		{
			message = workNode->getValue();
		}	
	}
	//Prufen ob message-id wert angegeben ist
	if(node->getAttributCount() > 0)
	{
		//Auslesend er Message ID
		mid = node->getAttribut(0)->getValue();
	}
	
	//Hier muss noch der Username ermittelt werden
	this->createNewMessage(message, mid, uid, "", false);	
}

string Messageboard::getFatherName()
{
	return father->getName();
}

string * Messageboard::getChildNames()
{
	return NULL;
}

Message * Messageboard::getHighlightedMessage()
{
	Message * message = 0;
	if(this->highlighted != NULL)
	{
		message = this->highlighted;

	}
	return message;
}

/* Liefert die naechte Nachricht des Messageboards */
Message * Messageboard::getNextMessage()
{
    //Pruefen ob eine Nachricht existiert
    if(this->first != NULL)
    {
        //Pruefen ob bereits eine Nahricht angezeigt wurde
        if(this->highlighted == NULL)
        {
            //es wurde noch keine Nachricht gezeigt
            this->highlighted = this->first;
        }
        else
	    if(highlighted->getNext() != NULL)
	    {
		    highlighted = highlighted->getNext();

	    }
    }
	return highlighted;
}

/* Liefert die vor Nachricht der letzten Message */
Message * Messageboard::getPreviousMessage()
{
    //Pruefen ob eine Nachricht existiert
    if(this->first != NULL)
    {
        //Pruefen ob bereits eine Nahricht angezeigt wurde
        if(this->highlighted == NULL)
        {
            //es wurde noch keine Nachricht gezeigt
            this->highlighted = this->first;
        }
        else
	    if(highlighted->getPrevious() != NULL)
	    {
		    highlighted = highlighted->getPrevious();

	    }
    }
	return highlighted;
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

/* speichert eine neue message und erzeugt eine neue MessageId */
bool Messageboard::createNewMessage(string message, int uid, string uName)
{
	string messageId = "";
	messageId = this->createNewMessageId();
	return this->createNewMessage(message, messageId, uid, uName, true);
}

/* erstellt eine neu Message mit der uebergeben MessageId */
bool Messageboard::createNewMessage(string message, string mid, int uid, string uName, bool withSave)
{
	Message * neu = NULL;
	if(first == NULL)
	{
		neu = new Message(message, mid, uid, 0, 0, uName);
		this->first = neu;
		this->last = neu;
	}
	else
	{
		//Pruefen ob die Message waehren des Init erstell wird
		neu = new Message(message, mid, uid, 0, this->first, uName);
		this->first->setPrevious(neu);
		this->first = neu;
		highlighted = neu;		
	}
	
	if(withSave)
	{
		this->saveBoard();
	}
	this->size++;
	return true;
}

//TO-DO XML-Abfrage
bool Messageboard::confirmAdminRights(int uid)
{
	bool assert = true; //XML-Abfrage, pr�fe uid. sprich abfrage auf admin. Ueberpruefung mit der Datenbank vom Login-Server
	return assert;
}

//TO-DO
bool Messageboard::confirmMessageRights(int uid)
{
	bool assert = false ;//XML-Abfrage, pr�fe uid. sprich ob eigent�mer der nachricht
	assert = highlighted->getUid() == uid;
	return assert;
}

bool Messageboard::deleteMessage(int uid)
{
	if(confirmAdminRights(uid))
	{
		erase();
		saveBoard();
		return true;
	}
	else if(confirmMessageRights(uid))
	{
		erase();
		saveBoard();
		return true;
	}
	return false;
}

void Messageboard::erase()
{
	Message * tmp = highlighted; 
	if(highlighted==NULL)
	{
		//TO-DO
		throw "Liste ist leer!\n";
	}
	else if(first == last)
	{
		first = 0;
		last = 0;
		highlighted = first;
	}
	else if((highlighted->getNext() == last)&&(highlighted->getPrevious() == NULL))
	{
		first = last;
		highlighted = first;
	}
	else if((highlighted->getPrevious() == first)&&(highlighted->getNext()==NULL))
	{
		last = first;
		highlighted = first;
	}
	else if(highlighted->getPrevious()==NULL)
	{
		first = first->getNext();
		highlighted = first;
	}
	else if(highlighted->getNext()==NULL)
	{
		last = last->getPrevious();
		highlighted = last;
	}
	else
	{
		highlighted = highlighted->getPrevious();
	}
	
	if(tmp != NULL)
	{
		delete tmp;
	}
}

//<--------------------------------------------- Ab hier auslagern in MessageBoard-Server-Klasse?
ConnectInformation * Messageboard::connectToFather()
{
	return father->getConnectInformation();
}

ConnectInformation * Messageboard::connectToChild(string childName)
{
	for(int i = 0; i < NUM_CHILDREN; i++)
	{
		if(childName.compare(this->childs[i]->getName()) == 0)
		{
			return childs[i]->getConnectInformation();
		}
	}
	throw "Keine Childs vorhanden!\n";
}

//TO-DO Verbindungen zu anderen Servern, wei� noch nicht genau wie das funktioniert in CORBA :D
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
	//saveChildrenInformation(id,name,connectInformation);//aufruf dieser Funktion auf vaterseite!
	//Verbindung abbauen
}

//TO-DO
void Messageboard::notifyChildren()
{
	for(int i = 0; i < NUM_CHILDREN; i++)
	{
		//Verbindung aufbauen zu childs[i]
		//saveFatherInformation(id, name, connectInformation);//Funktion auf seite der kinder aufrufen!
		//Verbindung abbauen
	}
}
//TO-DO
void Messageboard::saveFatherInformation(int id, string name, ConnectInformation * connectInformation)
{
	if(this->father != NULL)
	{
		delete this->father;
	}
	father = new BoardInformation(name, id, connectInformation);
	saveBoard();
}
