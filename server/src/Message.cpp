/*
 * Message.cpp
 *
 *  Created on: 21.12.2016
 *      Author: Noctis
 */

#include "./Message.h"

Message::Message(string message, int uid, Message * previous, Message * next, string uName)
{
	this->message=message;
	this->uid=uid;
	this->uName=uName;
	//id = XML++;
	//id in XML speichern;
	this->previous=previous;
	this->next=next;
}

Message::~Message()
{
	
}
