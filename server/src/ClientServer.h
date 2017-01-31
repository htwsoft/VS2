/*
 * ClientServer.h
 *
 *      Author: Marco Palumbo
 */

#ifndef CLIENTSERVER_H_
#define CLIENTSERVER_H_

#include "./VS2_klein.hh"
#include "./Messageboard.h"

class ClientServer: public POA_ClientMessageboardInterface, public PortableServer::RefCountServantBase
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
        ClientServer();
        ~ClientServer();
        //ClientServer Functions
        virtual char* getFatherName();
        virtual MessageData* setHighlightedMessage(const char* messageID);
        virtual array_of_String * getChildNames();
        virtual array_of_MessageData * getMessages();
        virtual MessageData* getHighlightedMessage();
        virtual MessageData* getMessageWithId(const char * messageID);
        virtual CORBA::Boolean setMessage(const char* message, const char* messageID, CORBA::Long uid, const char* uName);
        virtual CORBA::Boolean deleteMessage(CORBA::Long uid, const char * messageID);
        virtual CORBA::Boolean createNewMessage(const char* message, CORBA::Long uid, const char* uName);
        virtual MessageData * getNextMessage();
        virtual MessageData * getPreviousMessage();
		virtual ConnectInformationData * connectToFather(); //Liefert die ConnectInformationen für den Vater
		virtual ConnectInformationData * connectToChild(const char* childName); //Liefert die ConnectInformationen für ein Child
        //ServerServer Functions
};


#endif
