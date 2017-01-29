#include "./ClientServer.h"
#include "./VS2_kleinSK.cc"
#include "./Message.h"
#include <cstring>
#include <vector>

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
    cout << "Procedure createNewMessage() called" << endl;
    string strMessage(message); //char * in String umwandeln
    string strUName(uName); //char * in String umwandeln
    created = this->messageBoard->createNewMessage(strMessage, uid, strUName);
    return created;
}

/* aktuelle Nachricht loeschen */
CORBA::Boolean ClientServer::deleteMessage(::CORBA::Long uid)
{
    bool deleted = false;
    cout << "Procedure deleteMessage() called" << endl; 
    deleted = this->messageBoard->deleteMessage(uid);
    return deleted;
}

/* Liefert alle Messages in einem Array */
array_of_MessageData* ClientServer::getMessages()
{
    CORBA::ULong zaehler = 0;
    Message * worker = NULL;
    MessageData * workerData = NULL;
    std::vector<Message *> vMessage;    
    std::vector<Message *>::iterator iterMessage;
    array_of_MessageData * arrayMessageData = NULL;
    cout << "Procedure getMessages() called" << endl;
    //Laden aller Nachrichten in vectorArray
    //Highlighted auf erste Nachricht des Boards setzen    
    worker = this->messageBoard->getFirstMessage();
    while(worker != NULL)
    {
        vMessage.push_back(worker);
        worker = this->messageBoard->getNextMessage();
    }
    //Vector in arrayMessageData speichern
    if(vMessage.size() > 0)
    {
        //neues Array erstellen
        arrayMessageData = new array_of_MessageData();
        arrayMessageData->length(vMessage.size());  
        for(iterMessage=vMessage.begin(); iterMessage<vMessage.end(); iterMessage++)
		{
            worker = * iterMessage;
            workerData = new MessageData();
            workerData->uid = worker->getUid();
            workerData->id = worker->getId().c_str();
            workerData->uName = worker->getUName().c_str();
            workerData->text = worker->getMessage().c_str();
            (*arrayMessageData)[zaehler] = (*workerData);  
            zaehler++;             
        }
    }
    return arrayMessageData;
}

/* aktuelle Nachricht aendern */
CORBA::Boolean ClientServer::setMessage(const char* message, ::CORBA::Long uid, const char* uName)
{
    Message * msg = NULL;   
    string strMessage(message); //char * in String umwandeln
    string strUName(uName); //char * in String umwandeln
    cout << "Procedure setMessage() called" << endl; 
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
    cout << "Procedure getPreviousMessage() called" << endl; 
    msg = this->messageBoard->getPreviousMessage();
    if(msg != NULL)    
    { 
        mData = new MessageData();
        mData->uid = msg->getUid();
        mData->id = msg->getId().c_str();
        mData->uName = msg->getUName().c_str();
        mData->uName = msg->getUName().c_str(); 
    }
    return mData;
}

/* Naechste Nachricht an Client senden */
MessageData * ClientServer::getNextMessage()
{    
    Message * msg = NULL;
    MessageData * mData = 0;  
    cout << "Procedure getNextMessage() called" << endl;
    msg = this->messageBoard->getNextMessage();
    if(msg != NULL)    
    { 
        mData = new MessageData();
        mData->uid = msg->getUid();
        mData->id = msg->getId().c_str();
        mData->uName = msg->getUName().c_str();
        mData->text = msg->getMessage().c_str(); 
    }
    return mData;
}
