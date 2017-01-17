/*
 * Message.cpp
 *
 *  Created on: 21.12.2016
 *      Author: Noctis
 */

#include "./Message.h"

Message::Message(string message, string mid, int uid, Message * previous, Message * next, string uName)
{
	this->message=message;
	this->uid=uid;
	this->uName=uName;
	this->id = mid;
	this->previous=previous;
	this->next=next;
}

Message::~Message()
{
	if(this->previous != NULL)
	{
		this->previous->next = this->next;
	}
	
	if(this->next != NULL)
	{
		this->next->previous = this->previous;
	}
		
}
