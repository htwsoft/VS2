/*
 * Messageboard.h
 *
 *  Created on: 21.12.2016
 *      Author: Christian Patzek
 *      Messageboard ist ein Server/Knoten in der Baumstruktur
 */

#ifndef MESSAGEBOARD_H_
#define MESSAGEBOARD_H_

#endif /* MESSAGEBOARD_H_ */

#define NUM_CHILDREN 2//xml datei? unterschiedliche Boards haben unterschiedliche anzahl von kindern!

#include "../XMLWorker/source/XMLWorker.h"
#include "./Message.h"
#include "./ConnectInformation.h"

class Messageboard
{
	private:
	    string xmlPath;
	    XMLWorker * xml;
		int size;
		int id;
		string name;
		int fatherId;
		string fatherName;
		int ** childIds;
		string ** childNames;
		ConnectInformation * father;
		ConnectInformation ** childs;
		Message* first;
		Message* last;
		Message* highlighted;
		ConnectInformation * connectInformation;
		void initBoard();
	public:
		Messageboard(string);//initboard ueber xml-datei?
		~Messageboard();
		void saveMessages();
		//Client-Server
		string getFatherName();
		string** getChildNames();
		Message getNextMessage();
		Message getPreviousMessage();
		bool setMessage(string,int,string);
		bool createNewMessage(string,int,string);
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
		void saveChildInformation(int,string,ConnectInformation);
		void notifyChildren();
		void saveFatherInformation(int,string,ConnectInformation);
};
