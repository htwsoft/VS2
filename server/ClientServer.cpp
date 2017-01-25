#include "./ClientServer.h"
#include "./VS2_kleinSK.cc"
#include "./src/Message.h"

/* Kosntruktor der ClientServer-Klasse */
ClientServer::ClientServer()
{
    this->messageBoard = new Messageboard("./messageboard.xml");
}

/* Destruktor der ClientServer-Klasse*/
ClientServer::~ClientServer()
{
    delete this->messageBoard;
}

/* Neue Nachricht erstellen */
CORBA::Boolean ClientServer::createNewMessage(const char* message, ::CORBA::Long uid, const char* uName)
{
    bool created = false;
    string strMessage(message); //char * in String umwandeln
    string strUName(uName); //char * in String umwandeln
    created = this->messageBoard->createNewMessage(strMessage, uid, strUName);
    return created;
}

/* aktuelle Nachricht loeschen */
CORBA::Boolean ClientServer::deleteMessage(::CORBA::Long uid)
{
    bool deleted = false;
    deleted = this->messageBoard->deleteMessage(uid);
    return deleted;
}

/* aktuelle Nachricht aendern */
CORBA::Boolean ClientServer::setMessage(const char* message, ::CORBA::Long uid, const char* uName)
{
    Message * msg = NULL;
    string strMessage(message); //char * in String umwandeln
    string strUName(uName); //char * in String umwandeln
    msg = this->messageBoard->getPreviousMessage();
    msg->setMessage(strMessage);
    msg->setUid(uid);
    msg->setUName(strUName);
    return true;
}

/* Vorherige Nachricht an Client senden */
MessageData * ClientServer::getPreviousMessage()
{
    Message * msg = NULL;
    MessageData * mData = 0;    
    msg = this->messageBoard->getPreviousMessage();
    if(msg != NULL)    
    {
        mData->uid = msg->getUid();
        mData->id = msg->getId().c_str();
        mData->uName = msg->getUName().c_str();
    }
    return mData;
}

/* Naechste Nachricht an Client senden */
MessageData* ClientServer::getNextMessage()
{
    Message * msg = NULL;
    MessageData * mData = 0;    
    msg = this->messageBoard->getNextMessage();
    if(msg != NULL)    
    {
        mData->uid = msg->getUid();
        mData->id = msg->getId().c_str();
        mData->uName = msg->getUName().c_str();
    }
    return mData;
}
