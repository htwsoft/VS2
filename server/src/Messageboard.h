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
		int id;
		int mIdCounter; //Zaehler um richtige ID fuer eine Message zu generieren
		string name; //name des Boards
		BoardInformation * father;
		vector<BoardInformation *> childs;
		vector<BoardInformation *>::iterator iterChilds;
		Message * first;
		Message * last;
		Message * highlighted;
		BoardInformation * boardInformation;
		ConnectInformation * connectInformation;
		void initBoard();
		void initMessages();
		void initMessage(XMLNode *);
		void initMessageIdCounter();
		void initBoardName();
		void initConnectInfos();
		void initFatherNodeConnectInfos(XMLNode * node);
		void initChildConnectInfos(XMLNode * node);
		void initChild(XMLNode * node);
		void clearMessages();
		void clearBoardInformations();
		string intToStr(int number);
		string createNewMessageId();
	public:
		Messageboard(string);//initboard ueber xml-datei?
		~Messageboard();
		void saveMessages();
		//Client-Server
		string getFatherName();
		string * getChildNames();
		Message * getNextMessage();
		Message * getPreviousMessage();
		Message * getHighlightedMessage();
		bool setMessage(string,int,string);
		bool createNewMessage(string, string, int, string);
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
