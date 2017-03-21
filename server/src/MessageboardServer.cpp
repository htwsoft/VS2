/*
 * ClientServer.cpp
 *      Author: Marco Palumbo
 */

#include "./MessageboardServer.h"
#include "./VS2SK.cc"
#include "./Message.h"
#include "./ConnectInformation.h"
#include "./BoardInformation.h"
#include "./ServerClient.h"
#include <cstring>
#include <vector>

/* Kosntruktor der ClientServer-Klasse */
MessageboardServer::MessageboardServer()
{
    this->messageBoard = new Messageboard("./messageboard.xml");
}

/* Destruktor der ClientServer-Klasse*/
MessageboardServer::~MessageboardServer()
{
    this->clearJunkData();       
    delete this->messageBoard;
}


/* Wandelt die daten eines ConnectInformation Objektes in ConnectInformationData */
ConnectInformationData * MessageboardServer::getConnectInformationData(ConnectInformation * connectInformation)
{
    ConnectInformationData * ciData = NULL;
    ciData = new ConnectInformationData();
    if(connectInformation != NULL)        
    {
        ciData->port = connectInformation->getPort();
        ciData->ip = connectInformation->getIp().c_str();
    }
    else
    {
        ciData->port = 0;
        ciData->ip = "";
    }
    return ciData;
}

//Nachricht auf Board-Childs veroeffentlichen. Wenn Schalter = true dann auch auf den Childs der Childs
CORBA::Boolean MessageboardServer::publishOnChilds(const char * message, const char * messageID, const VS2::UserData& uData, CORBA::Boolean schalter)
{
    ServerClient * sc = NULL; //Klasse zum Kommunizieren mit einem anderen Server
    ConnectInformation * ciChild = NULL; //Verbindungsinformation eines Childs
    bool rValue = true; //Return Value
    bool workerValue = false;
    int childCount = 0;
    string * childNames = 0; //Array fuer ChildNames
    string childName = ""; //Name eines Childs
    string strMessage(message);
    string strMessageID(messageID);
    cout << "Procedure publishOnChilds() called" << endl;
    //Prüfen on ChildBoards vorhanden sins
    childCount = this->messageBoard->getChildCount();
    if(childCount > 0)
    {
        childNames = this->messageBoard->getChildNames();
        //Verbindung zu den einzelnen childs aufbauen
        for(int i=0; i<childCount; i++)
        {
            childName = childNames[i];
            //Verbindung zum Child-Board aufbauen
            ciChild = this->messageBoard->getConnectInformationChild(childName);
            sc = new ServerClient(ciChild);
            //Vater-Infos beim Child speichern
            workerValue = sc->publishMessage(strMessage, strMessageID, uData);
            //wenn schalter gesetzt und nachricht veroeffentlicht werden konnte 
            //Nachricht auf den childs des Child veroeffentlichen            
            if(workerValue)
            {
                workerValue = sc->iterateChilds(strMessage, strMessageID, uData);
            }       
            //rValue auf false setzen falls ein Fehler aufgetreten ist            
            if(!workerValue && rValue)
            {
                rValue = workerValue;
            }
            delete sc;
        }
    }       
    return rValue;
}

//Nachrichten auf dem Vater-Board veroeffentlichen
CORBA::Boolean MessageboardServer::publishOnFather(const char * message, const char * messageID, const VS2::UserData& uData)
{
    ServerClient * sc = NULL; //Klasse zum Kommunizieren mit einem anderen Server
    bool rValue = false; //Return Value
    string strMessage(message);
    string strMessageID(messageID);
    ConnectInformation * ciFather = NULL;
    cout << "Procedure publishOnFather() called" << endl;
    //Verbindung zum Vater-Board aufbauen
    ciFather = this->messageBoard->getConnectInformationFather();
    sc = new ServerClient(ciFather);
    //Nachricht auf Vater veröffentlichen
    rValue = sc->publishMessage(strMessage, strMessageID, uData);
    delete sc;
    return rValue;
}

//speichert eine Nachricht mit der übergebenen ID im Board
//wird von einem Vater oder child board verwendet
CORBA::Boolean MessageboardServer::saveMessage(const char * message, const char * messageID, const VS2::UserData& uData)
{
    string strMessage(message);
    string strMessageID(messageID);
    string strUserName(uData.userName);
    cout << "Procedure saveMessage() called" << endl;
    return this->messageBoard->createNewMessage(strMessage, strMessageID, uData.userID, strUserName);
}

//Teilt den child boards mit das es nun das Vater-Board ist
void MessageboardServer::notifyChildren(const VS2::UserData& uData)
{
    ServerClient * sc = NULL; //Klasse zum Kommunizieren mit einem anderen Server
    ConnectInformation * ciChild = NULL;
    ConnectInformation * ciMB = NULL;
    BoardInformation * mbInformation = NULL; //Daten des Server-Boards
    string name = "";
    int id = 0;
    int childCount = 0;
    string * childNames = 0; //Array mit Child-Names
    string childName = "";
    cout << "Procedure notifyChildren() called" << endl;
    //Daten des Server-Boards auslesen
    mbInformation = this->messageBoard->getBoardInformation();
    name = mbInformation->getName();
    id = mbInformation->getId();
    ciMB = mbInformation->getConnectInformation();
    //Prüfen on ChildBoards vorhanden sins
    childCount = this->messageBoard->getChildCount();
    if(childCount > 0)
    {
        childNames = this->messageBoard->getChildNames();
        //Verbindung zu den einzelnen childs aufbauen
        for(int i=0; i<childCount; i++)
        {
            childName = childNames[i];
            //Verbindung zum Child-Board aufbauen
            ciChild = this->messageBoard->getConnectInformationChild(childName);
            sc = new ServerClient(ciChild);
            //Vater-Infos beim Child speichern
            sc->saveFatherInformation(id, name , ciMB, uData); 
            delete sc;
        }
    }
}

//Teilt dem Vater-Board mit das es jetzt ein Kind von Ihm ist
void MessageboardServer::notifyFather(const VS2::UserData& uData)
{
    ServerClient * sc = NULL; //Klasse zum Kommunizieren mit einem anderen Server
    ConnectInformation * ciFather = NULL;
    ConnectInformation * ciMB = NULL;
    BoardInformation * mbInformation = NULL; //Daten des Server-Boards
    string name = "";
    int id = 0;
    cout << "Procedure notifyFather() called" << endl;
    //Daten des Server-Boards auslesen
    mbInformation = this->messageBoard->getBoardInformation();
    name = mbInformation->getName();
    id = mbInformation->getId();
    ciMB = mbInformation->getConnectInformation();
    //Verbindung zum Vater-Board aufbauen
    ciFather = this->messageBoard->getConnectInformationFather();
    sc = new ServerClient(ciFather);
    //Child-Infos beim Vater speichern
    sc->saveChildInformation(id, name , ciMB, uData); 
    delete sc;
}

/* speichert die neuen Kontakt-Infos des Vaters */
void MessageboardServer::saveFatherInformation(::CORBA::Long id, const char* name, const ::VS2::ConnectInformationData& ciData, const VS2::UserData& uData)
{
    string strName(name);
    string strIp(ciData.ip); 
    ConnectInformation * newCI = NULL;
    cout << "Procedure saveFatherInformation() called" << endl;
    newCI = new ConnectInformation(strIp, ciData.port);
    //saveFatherInformation(int id, string name, ConnectInformation * connectInformation)
    this->messageBoard->saveFatherInformation(id, strName, newCI);
    delete newCI;
}

/* speichert die neuen Kontakt-Infos eines Childs */
void MessageboardServer::saveChildInformation(::CORBA::Long id, const char* name, const ::VS2::ConnectInformationData& ciData, const VS2::UserData& uData)
{
    string strName(name);
    string strIp(ciData.ip); 
    ConnectInformation * newCI = NULL;
    cout << "Procedure saveChildInformation() called" << endl;
    newCI = new ConnectInformation(strIp, ciData.port);
    //saveFatherInformation(int id, string name, ConnectInformation * connectInformation)
    this->messageBoard->saveChildrenInformation(id, strName, newCI);
    delete newCI;
} 

/* Liefert die ConnectInformationData fuer den Vater */
ConnectInformationData * MessageboardServer::connectToFather(const VS2::UserData& uData)
{
    ConnectInformation * connectInformation = NULL;
    ConnectInformationData * ciData = NULL;
    cout << "Procedure connectToFather() called" << endl;
    connectInformation = this->messageBoard->getConnectInformationFather();
    ciData = this->getConnectInformationData(connectInformation);
    return ciData;
}

/* Liefert die ConnectInformationData für ein Child */
ConnectInformationData * MessageboardServer::connectToChild(const char* childName)
{
    string strChildName(childName);
    ConnectInformation * connectInformation = NULL;
    ConnectInformationData * ciData = NULL;
    cout << "Procedure connectToChild() called" << endl;
    connectInformation = this->messageBoard->getConnectInformationChild(strChildName);
    ciData = this->getConnectInformationData(connectInformation);
    return ciData;
}

/* Loeschen der erstelleten MessageData-Objekte */
void MessageboardServer::clearJunkData()
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
MessageData* MessageboardServer::setHighlightedMessage(const char* messageID)
{
    Message * msg = NULL;
    MessageData * mData = NULL;
    cout << "Procedure setHighlightedMessage() called" << endl;
    msg = this->searchMessage(messageID);
    mData = this->getMessageData(msg);  
    return mData;

}

/* Liefert den Namen des Fatherboards */
char * MessageboardServer::getFatherName()
{

    string fatherName = "";
    char * cFatherName = NULL;
    cout << "Procedure getFatherName() called" << endl;
    fatherName = this->messageBoard->getFatherName();
    cFatherName = new char[fatherName.length()];
    strcpy(cFatherName, fatherName.c_str());
    return cFatherName;
}

/* Liefert die Namen aller Childs */
array_of_String * MessageboardServer::getChildNames()
{
    string * childNames = NULL;
    string childName = "";
    array_of_String * arrayChildNames = NULL;
    int anzChilds = 0;
    cout << "Procedure getChildNames() called" << endl;
    arrayChildNames = new array_of_String();
    childNames = this->messageBoard->getChildNames();
    anzChilds = this->messageBoard->getChildCount();
    if(anzChilds >  0)
    {
        arrayChildNames->length(anzChilds);
        for(int i = 0; i<anzChilds; i++)
        {
            childName = childNames[i];
            (*arrayChildNames)[i] = childName.c_str();        
        }   
    }
    else
    {
        //Wenn keine Childs vorhanden Array mit lee, const VS2::UserData& uDatarString
        arrayChildNames->length(1);
        (*arrayChildNames)[0] = "";
    }
    return arrayChildNames;
}

/* liefert die MessageData zu einer uebergebenen Message */
MessageData * MessageboardServer::getMessageData(Message * msg)
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
MessageData* MessageboardServer::getHighlightedMessage()
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
MessageData * MessageboardServer::getMessageWithId(const char* messageID)
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
Message * MessageboardServer::searchMessage(string messageID)
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
CORBA::Boolean MessageboardServer::createNewMessage(const char* message, const VS2::UserData& uData)
{
    bool created = false;
    cout << "Procedure createNewMessage() called" << endl;
    string strMessage(message); //char * in String umwandeln
    string strUserName(uData.userName);
    created = this->messageBoard->createNewMessage(strMessage, uData.userID, strUserName);
    return created;
}

/* uebergeben Nachricht loeschen Nachricht loeschen */
CORBA::Boolean MessageboardServer::deleteMessage(const char* messageID, const VS2::UserData& uData)
{
    bool deleted = false;
    Message * message = NULL;
    string strMessageID(messageID); //char * in String convertieren
    cout << "Procedure deleteMessage() called" << endl; 
    //Suchen der Message um Highlighted zu setzen  
    message = this->searchMessage(strMessageID);
    if(message != NULL)
    {
        deleted = this->messageBoard->deleteMessage(uData.userID); 
    } 
    return deleted;
}

/* Liefert alle Messages in einem Array */
array_of_MessageData* MessageboardServer::getMessages()
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
    arrayMessageData = new array_of_MessageData();
    //Vector in arrayMessageData speichern
    if(vMessage.size() > 0)
    {
        //neues Array erstellen
        arrayMessageData->length(vMessage.size());  
        for(iterMessage=vMessage.begin(); iterMessage<vMessage.end(); iterMessage++)
		{
            worker = * iterMessage;
            workerData = this->getMessageData(worker);
            (*arrayMessageData)[zaehler] = (*workerData);  
            zaehler++;             
        }
    }
    else
    {
        //Wenn keine Messages vorhanden Array mit leerdaten erzeugen
        arrayMessageData->length(1);
        workerData = new MessageData();
        (*arrayMessageData)[0] = (*workerData);
        this->junkData.push_back(workerData);
    }
    return arrayMessageData;
}

/* aktuelle Nachricht aendern */
CORBA::Boolean MessageboardServer::setMessage(const char* message, const char* messageID, const VS2::UserData& uData)
{
    Message * msg = NULL;
    bool setOk = false;   
    string strMessage(message); //char * in String umwandeln
    string strUName(uData.userName); //char * in String umwandeln
    cout << "Procedure setMessage() called" << endl; 
    msg = this->searchMessage(messageID);
    if(msg != NULL)
    {
        msg->setMessage(strMessage);
        msg->setUid(uData.userID);
        msg->setUName(strUName);
        setOk = true;
    }    
    return setOk;
}



/* Vorherige Nachricht an Client senden */
MessageData * MessageboardServer::getPreviousMessage()
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
MessageData * MessageboardServer::getNextMessage()
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
