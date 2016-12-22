/*
 * Message.cpp
 *
 *  Created on: 21.12.2016
 *      Author: Noctis
 */

#include <Message.h>

Message::Message(string Message, int uid, Message* previous =0, Message* next =0, string uName)
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
