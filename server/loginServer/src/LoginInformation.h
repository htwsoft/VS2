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
		bool adminRights;
		ConnectInformation server;
	public:
		LoginInformation(bool adminRights,ConnectInformation server){this->adminRights=adminRights;this->server=server;}
		bool getAdminRights()const{return adminRights;}
		void setAdminRights(bool adminRights){this->adminRights=adminRights;}
};

#endif /* LOGININFORMATION_H_ */
