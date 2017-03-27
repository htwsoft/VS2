/*
 * LoginServer.h
 *
 *  Created on: 29.01.2017
 *      Author: Christian Patzek
 *      compile: g++ test.c -l sqlite3
 */

#ifndef LOGINSERVER_H_
#define LOGINSERVER_H_

#include <iostream>
#include "./sqlite3.h"
#include <stdlib.h>
#include <string>
#include <assert.h>
#include <signal.h>
#include <unistd.h>
#include "./LoginInformation.h"
#include "./UserData.h"

using namespace std;

class LoginServer
{
	private:
		int uIdCount;
		UserData loginData;
		LoginInformation serverInformation;
		string boardName;

		static const char* DATABASE;
		static const char* UIDCOUNT_TABLE;
		static const int CONFIRM_USER_DATA;
		static const int INCREMENT_UID;
		static const int REG;
		static const int NEW_DATA;
		static const int USERNAME;
		static const int GET_UID;

		bool openDataBase(int callback, string serverName="");
		bool createNewData(string serverName);
		void incrementUIdCount();
		bool confirmUserData();//ueberprueft mittels DB ob die aktuellen loginData mit einem datensatz uebereinstimmen
		bool confirmUserName(string);//ueberprueft ob schon ein Benutzer mit dem selben Benutzernamen existiert
	public:
		LoginServer();//hole uidcount aus DB, starte server/oeffne port, lausche fuer anfragen
		LoginInformation login(UserData);//Client erhaelt IP/Port+Rechte des Home-Messageboards an dem er gemeldet ist
		bool reg(UserData, string); 
		void setUIdCount(int uIdCount){this->uIdCount=uIdCount;}
		int getUIdCount()const{return uIdCount;}
		UserData getLoginData()const{return loginData;}
		LoginInformation getServerInformation()const{return serverInformation;}
		string getBoardName()const{return boardName;}							
};

#endif /* LOGINSERVER_H_ */



