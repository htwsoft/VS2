/*
 * ClientServer.h
 *
 *      Author: Marco Palumbo
 */

#ifndef MESSAGEBOARDSERVER_H_
#define MESSAGEBOARDSERVER_H_

#include "./VS2.hh"
#include "./Messageboard.h"

using namespace VS2;

class MessageboardServer: public POA_VS2::MessageboardServerInterface,
    public PortableServer::RefCountServantBase
{
    private:
        Messageboard * messageBoard;
        Message * searchMessage(string messageID);
        MessageData * getMessageData(Message * msg);
        //Vektor speichert alle erstellten MessageData
        //werden alle beim Destruktor freigegeben
		vector<MessageData *> junkData;
		vector<MessageData *>::iterator iterjunkData;
        ConnectInformationData * getConnectInformationData(ConnectInformation * connectInformation);
        void clearJunkData();
    public:
        MessageboardServer();
        ~MessageboardServer();
        //ClientServer Functions
        char* getFatherName();
        MessageData * setHighlightedMessage(const char* messageID);
        array_of_String * getChildNames();
        array_of_MessageData * getMessages();
        MessageData* getHighlightedMessage();
        MessageData* getMessageWithId(const char * messageID);
        CORBA::Boolean setMessage(const char* message, const char* messageID, CORBA::Long uid, const char* uName);
        CORBA::Boolean deleteMessage(CORBA::Long uid, const char * messageID);
        CORBA::Boolean createNewMessage(const char* message, CORBA::Long uid, const char* uName);
        MessageData * getNextMessage();
        MessageData * getPreviousMessage();
		ConnectInformationData * connectToFather(); //Liefert die ConnectInformationen für den Vater
		ConnectInformationData * connectToChild(const char* childName); //Liefert die ConnectInformationen für ein Child
        CORBA::Boolean iterateChilds(const char* message, const char* messageID, ::CORBA::Long uid, const char* uName, ::CORBA::Boolean schalter){return false;};
        CORBA::Boolean publishOnFather(const char* message, const char* messageID, ::CORBA::Long uid, const char* uName){return false;};
        //ServerServer Functions
        CORBA::Boolean publishChild(const char* message, ::CORBA::Long uid, const char* uName, ::CORBA::Boolean schalter){return false;};
        CORBA::Boolean publishFather(const char* message, ::CORBA::Long uid, const char* uName){return false;};
        void notifyFather(){};
        void saveFatherInformation(::CORBA::Long id, const char* name, const ::VS2::ConnectInformationData& ciData);
        void notifyChildren(){};
        void saveChildInformation(::CORBA::Long id, const char* name, const ::VS2::ConnectInformationData& ciData);        
};


#endif
