/*
 * LoginServer.h
 *
 *  Created on: 29.01.2017
 *      Author: Christian Patzek
 */

#ifndef LOGINSERVER_H_
#define LOGINSERVER_H_

#include <iostream>
#include <String>
#include "./LoginInformation.h"
#include "./UserData.h"

using namespace std;

class LoginServer
{
	private:
		int uIdCount;
		UserData loginData;
		LoginInformation serverInformation;

		void incrementUidCount();//XML-Datei fuer uIdCount? oder mittels DB?
		bool confirmUserData();//ueberprueft mittels DB ob die aktuellen loginData mit einem datensatz uebereinstimmen
		bool confirmUserName(string);//ueberprueft ob schon ein Benutzer mit dem selben Benutzernamen existiert
	public:
		LoginServer();//starte server/oeffne port, lausche fuer anfragen
		LoginInformation login(UserData);//Client erhaelt IP/Port+Rechte des Home-Messageboards an dem er gemeldet ist
		bool reg(UserData, string); //registrieren mit Benutzername+Password mit Angabe des Home-Messageboards
									//register am root(sprich chefboard, ist nicht moeglich!)
};

#endif /* LOGINSERVER_H_ */



