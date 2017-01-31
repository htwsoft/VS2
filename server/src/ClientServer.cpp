#include "./ClientServer.h"
#include "./VS2_kleinSK.cc"
#include "./Message.h"
#include "./ConnectInformation.h"
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
    this->clearJunkData();       
    delete this->messageBoard;
}

/* Wandelt die daten eines ConnectInformation Objektes in ConnectInformationData */
ConnectInformationData * ClientServer::getConnectInformationData(ConnectInformation * connectInformation)
{
    ConnectInformationData * ciData = NULL;
    if(connectInformation != NULL)
    {
        ciData = new ConnectInformationData();
        ciData->port = connectInformation->getPort();
        ciData->ip = connectInformation->getIp().c_str();
    }
    return ciData;
}

/* Liefert die ConnectInformationData fuer den Vater */
ConnectInformationData * ClientServer::connectToFather()
{
    ConnectInformation * connectInformation = NULL;
    ConnectInformationData * ciData = NULL;
    connectInformation = this->messageBoard->connectToFather();
    ciData = this->getConnectInformationData(connectInformation);
    return ciData;
}

/* Liefert die ConnectInformationData für ein Child */
ConnectInformationData * ClientServer::connectToChild(const char* childName)
{
    string strChildName(childName);
    ConnectInformation * connectInformation = NULL;
    ConnectInformationData * ciData = NULL;
    connectInformation = this->messageBoard->connectToChild(strChildName);
    ciData = this->getConnectInformationData(connectInformation);
    return ciData;
}

/* Loeschen der erstelleten MessageData-Objekte */
void ClientServer::clearJunkData()
{
	if(this->junkData.size() > 0)
	{
		//alle Childs suchen und im Speicher freigeben
		for(iterjunkData=this->junkData.begin(); iterjunkData<this->junkData.end(); iterjunkData++)
		{
            if(*iterjunkData != NULL)
            {
			    delete *iterjunkData;
            }
		}
		junkData.clear();	
	}
}

/* setzen der Highlighted Message des Boards */
MessageData* ClientServer::setHighlightedMessage(const char* messageID)
{
    Message * msg = NULL;
    MessageData * mData = NULL;
    msg = this->searchMessage(messageID);
    mData = this->getMessageData(msg);  
    return mData;

}

/* Liefert den Namen des Fatherboards */
char * ClientServer::getFatherName()
{

    string fatherName = "";
    char * cFatherName = NULL;
    cout << "Procedure getFatherName() called" << endl;
    fatherName = this->messageBoard->getFatherName();
    strcpy(cFatherName, fatherName.c_str());
    return cFatherName;
}

/* Liefert die Namen aller Childs */
array_of_String * ClientServer::getChildNames()
{
    string * childNames = NULL;
    string childName = "";
    array_of_String * arrayChildNames = NULL;
    int anzChilds = 0;
    cout << "Procedure getChildNames() called" << endl;
    arrayChildNames = new array_of_String();
    arrayChildNames->length(anzChilds);
    childNames = this->messageBoard->getChildNames();
    anzChilds = this->messageBoard->getChildCount();
    for(int i = 0; i<anzChilds; i++)
    {
        childName = childNames[i];
        (*arrayChildNames)[i] = childName.c_str();            
    }    
    return arrayChildNames;
}

/* liefert die MessageData zu einer uebergebenen Message */
MessageData * ClientServer::getMessageData(Message * msg)
{
    MessageData * mData = NULL;
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

/* Liefert die zuletzt ausewaehlte Message vom Board */
MessageData* ClientServer::getHighlightedMessage()
{
    Message * msg = NULL;
    MessageData * mData = NULL;
    cout << "Procedure getHighlightedMessage() called" << endl;
    msg = this->messageBoard->getHighlightedMessage();
    mData = this->getMessageData(msg);
    if(mData != NULL)
    {    
        this->junkData.push_back(mData);
    }
    return mData;
}

/* Anfragen einer bestimmten Nachricht */
MessageData * ClientServer::getMessageWithId(const char* messageID)
{
    MessageData * mData = NULL;
    Message * msg = NULL;
    string strMessageID(messageID); //char * in String convertieren
    cout << "Procedure getMessageWithId() called" << endl; 
    //Suchen der Message mit messageID  
    msg = this->searchMessage(strMessageID);       
    mData = this->getMessageData(msg);
    if(mData != NULL)
    {    
        this->junkData.push_back(mData);
    }     
    return mData;
}

/* sucht eine Message anhand der ID und liefert diese zurueck */
Message * ClientServer::searchMessage(string messageID)
{
    bool notFound = true;
    Message * worker = NULL;
    Message * searchedMsg = NULL;
    worker = this->messageBoard->getFirstMessage();
    while(worker != NULL && notFound)
    {
        //Pruefen ob zu loeschende Nachricht gefunden wurde
        if(messageID.compare(worker->getId()) == 0)
        {
            //Message wurde gefunden
            searchedMsg = worker;
            notFound = false;
        }
        else
        {
            worker = this->messageBoard->getNextMessage();
        }
    }  
    return searchedMsg;
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

/* uebergeben Nachricht loeschen Nachricht loeschen */
CORBA::Boolean ClientServer::deleteMessage(::CORBA::Long uid, const char* messageID)
{
    bool deleted = false;
    Message * message = NULL;
    string strMessageID(messageID); //char * in String convertieren
    cout << "Procedure deleteMessage() called" << endl; 
    //Suchen der Message um Highlighted zu setzen  
    message = this->searchMessage(strMessageID);
    if(message != NULL)
    {
        deleted = this->messageBoard->deleteMessage(uid); 
    } 
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
            workerData = this->getMessageData(worker);
            (*arrayMessageData)[zaehler] = (*workerData);  
            zaehler++;             
        }
    }
    return arrayMessageData;
}

/* aktuelle Nachricht aendern */
CORBA::Boolean ClientServer::setMessage(const char* message, const char* messageID, ::CORBA::Long uid, const char* uName)
{
    Message * msg = NULL;
    bool setOk = false;   
    string strMessage(message); //char * in String umwandeln
    string strUName(uName); //char * in String umwandeln
    cout << "Procedure setMessage() called" << endl; 
    msg = this->searchMessage(messageID);
    if(msg != NULL)
    {
        msg->setMessage(strMessage);
        msg->setUid(uid);
        msg->setUName(strUName);
        setOk = true;
    }    
    return setOk;
}



/* Vorherige Nachricht an Client senden */
MessageData * ClientServer::getPreviousMessage()
{
    Message * msg = NULL;
    MessageData * mData = NULL; 
    cout << "Procedure getPreviousMessage() called" << endl; 
    msg = this->messageBoard->getPreviousMessage();
    mData = this->getMessageData(msg);
    if(mData != NULL)
    {    
        this->junkData.push_back(mData);
    }
    return mData;
}

/* Naechste Nachricht an Client senden */
MessageData * ClientServer::getNextMessage()
{    
    Message * msg = NULL;
    MessageData * mData = NULL;  
    cout << "Procedure getNextMessage() called" << endl;
    msg = this->messageBoard->getNextMessage();
    mData = this->getMessageData(msg);
    if(mData != NULL)
    {    
        this->junkData.push_back(mData);
    }
    return mData;
}
