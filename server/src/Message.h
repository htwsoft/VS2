/*
 * Message.h
 *
 *  Created on: 21.12.2016
 *      Author: Christian Patzek
 *      Struktur von Messages die auf Messageboards verwaltet werden
 */

#ifndef MESSAGE_H_
#define MESSAGE_H_


#endif /* MESSAGE_H_ */

#include <iostream>
#include <string>
#include <sstream>

using namespace std;

class Message
{
	private:
		string message;
		int id;
		int uid;
		string uName;
		Message* previous;
		Message* next;
	public:
		Message(string, int, string, Message* =0, Message* =0);//speichere id in xml datei direkt???
		~Message();
		void setMessage(const string message){this->message=message;}
		void setId(const int id){this->id=id;}
		void setUid(const int uid){this->uid=uid;/*setUName(uName=XML)*/}
		void setUName(const string uName){this->uName=uName;}
		string getMessage()const{return this->message;}
		int getId()const{return this->id;}
		int getUid()const{return this->uid;}
		string toString(){return message;}
};
