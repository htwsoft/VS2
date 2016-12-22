/*
 * ConnectInformation.h
 *
 *  Created on: 21.12.2016
 *      Author: Christian Patzek
 *      Verbindungsinformation eines Knotens in der Baumstruktur
 */

#ifndef CONNECTINFORMATION_H_
#define CONNECTINFORMATION_H_


#endif /* CONNECTINFORMATION_H_ */

class ConnectInformation
{
	private:
		string ip;
		int port;
	public:
		ConnectInformation(string ip,int port){this->ip=ip;this->port=port;}
		string getIp() const{return ip;}
		int getPort() const{return port;}
		void setIp(string ip){this->ip=ip;}
		void setPort(int port){this->port=port;}
};




