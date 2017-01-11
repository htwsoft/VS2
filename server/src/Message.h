/*
 * Message.h
 *
 *  Created on: 21.12.2016
 *      Author: Christian Patzek und Marco Palumbo
 *      Struktur von Messages die auf Messageboards verwaltet werden
 */

#ifndef MESSAGE_H_
#define MESSAGE_H_


#endif /* MESSAGE_H_ */

#include <iostream>
#include <String>
#include <sstream>

using namespace std;

class Message
{
	private:
		string message;
		string id;
		int uid;
		string uName;
		Message * next;
		Message * previous;
	public:
		Message(string, string, int, Message * = 0, Message * = 0, string = "");//speichere id in xml datei direkt???
		~Message();
		void setMessage(const string message){this->message=message;}
		void setId(const string id){this->id=id;}
		void setUid(const int uid){this->uid=uid;/*setUName(uName=XML)*/}
		void setUName(const string uName){this->uName=uName;}
		string getMessage()const{return this->message;}
		string getId()const{return this->id;}
		int getUid()const{return this->uid;}
		string toString(){return message;}
		Message * getNext(){return this->next;}; //Funktion damit MessageBoard Next Abrufen kann
		Message * getPrevious(){return this->previous;}; //Funktion damit MessageBoard previous Abrufen kann
		void setNext(Message * next){this->next = next;}; //Funktion damit MessageBoard Next zuweisen kann
		void setPrevious(Message * previous){this->previous = previous;}; //Funktion damit MessageBoard zuweisen Abrufen kann		
};
