/*
 * LoginInformation.h
 *
 *  Created on: 30.01.2017
 *      Author: Noctis
 */

#ifndef LOGININFORMATION_H_
#define LOGININFORMATION_H_

#include "./ConnectInformation.h"

class LoginInformation
{
	private:
		int uId;
		bool adminRights;
		ConnectInformation server;
	public:
		LoginInformation();
		LoginInformation(bool adminRights,ConnectInformation server){this->adminRights=adminRights;this->server=server;}
		bool getAdminRights()const{return adminRights;}
		ConnectInformation getServer()const{return server;}
		void setAdminRights(bool adminRights){this->adminRights=adminRights;}
		void setUId(int uId){this->uId=uId;}
		int getUId()const{return uId;}
};

#endif /* LOGININFORMATION_H_ */
