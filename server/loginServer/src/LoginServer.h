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
#include <sqlite.h>
#include <String>
#include <stdlib.h>
#include <string>
#include <assert.h>
#include <signal.h>
#include <unistd.h>
#include "./LoginInformation.h"
#include "./UserData.h"

using namespace std;
using namespace VS2;

class LoginServer
{
	private:
		int uIdCount;
		UserData loginData;
		LoginInformation serverInformation;

		static const int COLUMN_UID;
		static const int COLUMN_USER_NAME;
		static const int COLUMN_PASSWORD;
		static const int COLUMN_ADMIN_RIGHTS;
		static const int COLUMN_IP;
		static const int COLUMN_PORT;
		static const int COLUMN_HOMEBOARD;
		static const string DATABSE;
		static const string UIDCOUNT_TABLE;
		static const int CONFIRM_USER_DATA;
		static const int INCREMENT_UID;
		static const int REG;
		static const int NEW_DATA;
		static const int USERNAME;
		static const int GET_UID;

		bool openDataBase(static const int callback, string serverName="");
		bool createNewData(string serverName);
		static int getUIdCallback();
		static int userNameCallback(void *data, int argc, char **argv, char **azColName);
		static int newDataCallback(void *data, int argc, char **argv, char **azColName);
		static int regCallback(void *data, int argc, char **argv, char **azColName);
		static int uIdCallback(void *data, int argc, char **argv, char **azColName);
		static int loginCallback(void *data, int argc, char **argv, char **azColName);
		void incrementUidCount();
		bool confirmUserData();//ueberprueft mittels DB ob die aktuellen loginData mit einem datensatz uebereinstimmen
		bool confirmUserName(string);//ueberprueft ob schon ein Benutzer mit dem selben Benutzernamen existiert
	public:
		LoginServer();//hole uidcount aus DB, starte server/oeffne port, lausche fuer anfragen
		LoginInformation login(UserData);//Client erhaelt IP/Port+Rechte des Home-Messageboards an dem er gemeldet ist
		bool reg(UserData, string); //registrieren mit Benutzername+Password mit Angabe des Home-Messageboards
									//register am root(sprich chefboard, ist nicht moeglich!)
};

#endif /* LOGINSERVER_H_ */



