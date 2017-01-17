/*
 * Messageboard.h
 *
 *  Created on: 21.12.2016
 *      Author: Christian Patzek und Marco Palumbo
 *      Messageboard ist ein Server/Knoten in der Baumstruktur
 */

#ifndef MESSAGEBOARD_H_
#define MESSAGEBOARD_H_

#endif /* MESSAGEBOARD_H_ */

#define NUM_CHILDREN 2//xml datei? unterschiedliche Boards haben unterschiedliche anzahl von kindern!

#include "../XMLWorker/source/XMLWorker.h"
#include "./Message.h"
#include "./ConnectInformation.h"
#include "./BoardInformation.h"

class Messageboard
{
	private:
	    string xmlPath;
	    XMLWorker * xml;
		int size;
		int mIdCounter; //Zaehler um richtige ID fuer eine Message zu generieren
		BoardInformation * father;
		vector<BoardInformation *> childs;
		vector<BoardInformation *>::iterator iterChilds;
		Message * first;
		Message * last;
		Message * highlighted;
		BoardInformation * boardInformation; //BoardInformatioenen 
		void initBoard();
		void initMessages();
		void initMessage(XMLNode *);
		void initMessageIdCounter();
		void initBoardInformations();
		void initConnectInfos();
		void initFatherNodeConnectInfos(XMLNode * node);
		void initChildConnectInfos(XMLNode * node);
		void initChild(XMLNode * node);
		void clearMessages();
		void clearBoardInformations();
		string intToStr(int number);
		string createNewMessageId();
		void saveMessages(XMLNode * fatherNode);
		void saveBoardInformations(XMLNode * fatherNode);
		void saveConnectInformations(XMLNode * fatherNode){};
	public:
		Messageboard(string);//initboard ueber xml-datei?
		//Messageboard(int, string); Konstruktor zum anlegen eines neuen Boards
		~Messageboard();
		void saveBoard();
		//Client-Server
		string getFatherName();
		string * getChildNames();
		Message * getNextMessage();
		Message * getPreviousMessage();
		Message * getHighlightedMessage();
		bool setMessage(string,int,string);
		bool createNewMessage(string, string, int, string, bool withSave);
		bool confirmAdminRights(int);
		bool confirmMessageRights(int);
		bool deleteMessage(int);
		void erase();
		ConnectInformation * connectToFather();
		ConnectInformation * connectToChild(string);
		bool iterateChilds(string, int, string, bool);
		bool publishOnFather(string, int, string);
		//Server-Server
		bool publishChild(string, int, string, bool);
		bool publishFather(string,int,string);
		void notifyFather();
		void saveChildrenInformation(int, string, ConnectInformation *);
		void notifyChildren();
		void saveFatherInformation(int, string, ConnectInformation *);
};
