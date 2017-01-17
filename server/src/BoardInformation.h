#ifndef BOARDINFORMATION_H_
#define BOARDINFORMATION_H_

#include "./ConnectInformation.h"
#include <string>

class BoardInformation
{
	private:
		int id;
		string name;
		ConnectInformation * connectInformation;
	public:
		BoardInformation(string name, int id, ConnectInformation * connectInformation)
		{
			this->name = name; 
			this->id = id; 
			this->connectInformation = connectInformation;
		};
		~BoardInformation(){delete this->connectInformation;};
		string getName(){return this->name;};
		int getId(){return this->id;};
		ConnectInformation * getConnectInformation(){return this->connectInformation;};
		void setName(string name){this->name = name;};
		void setId(int id){this->id = id;}
		void setConnectInformation(ConnectInformation * connectInformation){this->connectInformation = connectInformation;};
};

#endif 