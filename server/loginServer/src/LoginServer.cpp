/*
 * LoginServer.cpp
 *
 *  Created on: 29.01.2017
 *      Author: Christian Patzek
 */

#include "./LoginServer.h"


//ToDo port oeffnen und auf Verbindungen lauschen, uIdCount aus DB/XML lesen
LoginServer::LoginServer()
{
	//uIdCount=Abfrage;
};

LoginInformation LoginServer::login(UserData loginData)
{
	this->loginData=loginData;
	confirmUserData();
	return serverInformation;
}

//ToDo DB-Abfrage nach den login-daten
void LoginServer::confirmUserData()
{
	/*if(!select loginData)
	 * {
	 * 		serverInformation.server.setIp("Err");
			serverInformation.server.setPort("10000");
			serverInformation.setAdminRights(false);
	 * }
	 *
	  else
	  {
	  	    serverInformation.server.setIp("Ip aus Datenbank");
			serverInformation.server.setPort("Port aus Datenbank");
			serverInformation.setAdminRights(AdminRights aus Datenbank);
	   }
	   */
}

//ToDo
void LoginServer::incrementUIdCount()
{
	uIdCount++;
	//Speichere in DB/XML
}
//ToDo DB-Datensatz anlegen
bool LoginServer::reg(UserData loginData, string serverName)
{
	if(confirmUserName(loginData.getUserName()))
		return false;
	else
	{
		/*
		 * lege Datensatz in DB an
		 */
		incrementUIdCount();
		return true;
	}
}

//ToDo DB-Abfrage
bool LoginServer::confirmUserName(string userName)
{
	/*if(select userName)
	 *  return false;
	 *else
	 *	return true;
	 *
	 */
}
