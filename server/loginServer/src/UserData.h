/*
 * UserData.h
 *
 *  Created on: 29.01.2017
 *      Author: Christian Patzek
 */

#ifndef USERDATA_H_
#define USERDATA_H_

#include <string>

using namespace std;

class UserData
{
	private:
		string userName;
		string password;
	public:
		UserData(string userName,string password){this->userName=userName;this->password=password;}
		string getUserName()const{return userName;}
		void setUserName(string userName){this->userName=userName;}
		string getPassword()const{return password;}
};

#endif /* USERDATA_H_ */
