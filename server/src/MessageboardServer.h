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
        bool sendMessageToSoapBoard(const char * message, string messageID, int userId);
        bool deleteMessageOnSoapBoard(const char * messageID);
        bool modifyMessageOnSoapBoard(const char * message, const char * messageID);
        bool isConnectedToSoapBoard();
        bool confirmAccessRights(string messsageId, VS2::UserData& uData);
        bool checkIsAdmin(VS2::UserData& uData);
        bool checkGlobalMessageRights(string messageId);
        bool checkMessageOwner(VS2::UserData& uData);
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
        CORBA::Boolean setMessage(const char* message, const char* messageID, const VS2::UserData& uData);
        CORBA::Boolean deleteMessage(const char * messageID, const VS2::UserData& uData);
        CORBA::Boolean createNewMessage(const char* message, const VS2::UserData& uData);
        MessageData * getNextMessage();
        MessageData * getPreviousMessage();
		ConnectInformationData * connectToFather(const VS2::UserData& uData); //Liefert die ConnectInformationen für den Vater
		ConnectInformationData * connectToChild(const char * childName); //Liefert die ConnectInformationen für ein Child
        //ServerServer Functions
        CORBA::Boolean publishOnChilds(const char * message, const char * messageID, const VS2::UserData& uData, CORBA::Boolean schalter);
        CORBA::Boolean publishOnFather(const char * message, const char * messageID, const VS2::UserData& uData);
        CORBA::Boolean saveMessage(const char * message, const char * messageID, const VS2::UserData& uData);        
        void notifyFather(const VS2::UserData& uData);
        void saveFatherInformation(CORBA::Long id, const char* name, const VS2::ConnectInformationData& ciData, const VS2::UserData& uData);
        void notifyChildren(const VS2::UserData& uData);
        void saveChildInformation(CORBA::Long id, const char* name, const VS2::ConnectInformationData& ciData, const VS2::UserData& uData);
        CORBA::Boolean modifyMessageSoap(const char* message, const char* messageID, ::CORBA::Long serverNr, const ::VS2::UserData& uData);
        CORBA::Boolean deleteMessageSoap(const char * messageID, const VS2::UserData& uData);
        CORBA::Boolean createMessageSoap(const char* message, const char * messageID, CORBA::Long serverNr, const VS2::UserData& uData);        
};


#endif
