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
		void initBoardXML();
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
		void saveConnectInformations(XMLNode * fatherNode);
		void saveChildConnectInformations(XMLNode * fatherNode);
		void saveFatherConnectInformation(XMLNode * fatherNode);
		bool createNewMessage(string, string, int, string, bool = true);
	public:
		Messageboard(string);//Konstruktor mit einer Board-XML-Datei
		Messageboard(int, string); //Konstruktor zum anlegen eines neuen Boards
		~Messageboard();
		void saveBoard();
		//Client-Server
		string getFatherName();
		string * getChildNames();
		Message * getNextMessage();
		Message * getPreviousMessage();
		Message * getHighlightedMessage();
        Message * getFirstMessage();
        Message * getLastMessage();
        void setLastMessageToHighlighted();
        void setFirstMessageToHighlighted();
        void setHighlightedMessage(Message * message);
		bool setMessage(string,int,string);
		bool createNewMessage(string, int, string);
		bool confirmAdminRights(int);
		bool confirmMessageRights(int);
		bool deleteMessage(int);
		void erase();
        int getChildCount();
		ConnectInformation * connectToFather(); //auslagern in Messageboard server?
		ConnectInformation * connectToChild(string); //auslagern in Messageboard server?
		bool iterateChilds(string, int, string, bool); //auslagern in Messageboard server?
		bool publishOnFather(string, int, string); //auslagern in Messageboard server?
		//Server-Server
		void saveFatherInformation(int, string, ConnectInformation *);
		void saveChildrenInformation(int, string, ConnectInformation *);
		bool publishChild(string, int, string, bool); //auslagern in Messageboard server?
		bool publishFather(string,int,string); //auslagern in Messageboard server?
		void notifyFather(); //auslagern in Messageboard server?
		void notifyChildren(); //auslagern in Messageboard server?
};
