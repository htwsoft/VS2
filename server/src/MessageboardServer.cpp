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
#include "./SoapServerClient.h"
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

//Funktion liefert true zuruck falls der User ein admin ist
bool MessageboardServer::checkIsAdmin(VS2::UserData& uData)
{
    return uData.isAdmin;
}
//Umwandeln von int in string
string MessageboardServer::intToStr(int number)
{
    string rValue = "";
	ostringstream converter;
    try
    {
        converter << number;
	    rValue = converter.str();
    }
    catch(...)
    {
        rValue = "";
    }
    return rValue;
}

//funktion liefert true zurueck falls die nachricht nur auf dem Board vorhanden ist
//und veraendert werden darf
//wichtig fuer Soap-Messages
bool MessageboardServer::checkGlobalMessageRights(string messageId)
{
    bool rValue = false;
    int boardId = 0;
    string strBoardId = "";
    //Pruefen ob eine Soap-Message mit negativ id eingetragen ist
    if(messageId.find("SOAP")!=std::string::npos)
    {
        //-5-SOAP5123 oder 4-SOAP412
        if(messageId.substr(0,1).compare("-") != 0)
        {
            //Nachricht darf geaendert werden
            rValue = true;
        }
    }
    else
    {
        //Pruefen ob die Nachricht von einem anderen Messageboard kommt
        //Aufbau Msg: 14-12345
        boardId = this->messageBoard->getBoardInformation()->getId();
        strBoardId = this->intToStr(boardId);
        if(messageId.substr(0,strBoardId.length()).compare(strBoardId) == 0)
        {
            //Nachricht ist vom selben Board
            rValue = true;
        }
    }
    return rValue;
}

//Liefert true zurueck falls die Nachricht dem User gehoert
bool checkMessageOwner(VS2::UserData& uData, Message * msg)
{
    return uData.userID == msg->getUid();
}

//Funktion liefert true zurueck falls eine Verbindung mit einer Soap-Tafel besteht
bool MessageboardServer::isConnectedToSoapBoard()
{
    return this->messageBoard->getConnectInformationSoap() != NULL;
}


bool MessageboardServer::modifyMessageOnFather(const char* message, const char* messageID, const VS2::UserData& uData)
{
    ServerClient * sc = NULL; //Klasse zum Kommunizieren mit einem anderen Server
    bool rValue = false; //Return Value
    ConnectInformation * ciFather = NULL;
    cout << "Procedure modifyMessageOnFather() called" << endl;
    try
    {
        //Verbindung zum Vater-Board aufbauen
        ciFather = this->messageBoard->getConnectInformationFather();
        if(ciFather != NULL)
        {
            sc = new ServerClient(ciFather);
            //Nachricht auf Vater veröffentlichen
            rValue = sc->modifyMessage(message, messageID, uData);
            delete sc;
        }
        else
        {
            rValue = true;
        }
    }
    catch(...)
    {
        cout << "Error while modifyMessageOnFather()" << endl;
    }
    return rValue;
}

bool MessageboardServer::modifyMessageOnChilds(const char* message, const char* messageID, const VS2::UserData& uData)
{
    ServerClient * sc = NULL; //Klasse zum Kommunizieren mit einem anderen Server
    ConnectInformation * ciChild = NULL; //Verbindungsinformation eines Childs
    bool rValue = true; //Return Value
    bool workerValue = false;
    int childCount = 0;
    string * childNames = 0; //Array fuer ChildNames
    string childName = ""; //Name eines Childs
    cout << "Procedure modifyMessageOnChilds() called" << endl;
    //Prüfen on ChildBoards vorhanden sins
    childCount = this->messageBoard->getChildCount();
    if(childCount > 0)
    {
        childNames = this->messageBoard->getChildNames();
        //Verbindung zu den einzelnen childs aufbauen
        for(int i=0; i<childCount; i++)
        {
            childName = childNames[i];
            try
            {
                //Verbindung zum Child-Board aufbauen
                ciChild = this->messageBoard->getConnectInformationChild(childName);
                if(ciChild != NULL)
                {
                    sc = new ServerClient(ciChild);
                    //Vater-Infos beim Child speichern
                    workerValue = sc->modifyMessage(message, messageID, uData);  
                    //rValue auf false setzen falls ein Fehler aufgetreten ist            
                    delete sc;
                }
                else
                {
                    rValue = true;
                }
                if(!workerValue && rValue)
                {
                    rValue = workerValue;
                }
            }
            catch(...)
            {
                cout << "Error while modifyMessageOnChilds()" << endl;
            }
        }
    }
    else
    {
        rValue = true;
    }       
    return rValue;
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
        if(this->isConnectedToSoapBoard())
        {
            setOk = this->modifyMessageOnSoapBoard(message, messageID);
            if(setOk)
            {
                this->messageBoard->setMessage(strMessage, uData.userID, strUName);
                setOk = true;
            }
        }
        else
        {
             this->messageBoard->setMessage(strMessage, uData.userID, strUName);
             setOk = true;
        }
    }    
    return setOk;
}

/* uebergeben Nachricht loeschen Nachricht loeschen */
CORBA::Boolean MessageboardServer::deleteMessage(const char* messageID, const VS2::UserData& uData)
{
    bool deleted = false;
    bool msgShared = false;
    Message * message = NULL;
    string strMessageID(messageID); //char * in String convertieren
    cout << "Procedure deleteMessage() called" << endl; 
    //Suchen der Message um Highlighted zu setzen  
    message = this->searchMessage(strMessageID);
    msgShared = message->getShared();
    if(message != NULL)
    {
        //Pruefen ob eine Verknuepfung zu einer Soap-Tafel besteht
        if(this->isConnectedToSoapBoard())
        {
            deleted = this->deleteMessageOnSoapBoard(messageID);
            if(deleted)
            {
                deleted = this->messageBoard->deleteMessage(uData.userID);
            }
        }
        else
        {
            deleted = this->messageBoard->deleteMessage(uData.userID);
        }

        if(deleted && msgShared)
        {
            this->deleteMessageOnFather(messageID, uData);
            this->deleteMessageOnChilds(messageID, uData);
        }
    } 
    return deleted;
}

/*Erstellt die URL fuer Soap Requests */
string MessageboardServer::getSoapAdresse(ConnectInformation * connectInformation)
{
    string rValue = "";
    string soapIP = "";
    int soapPort = 0;
    string strSoapPort = "";
    soapIP = connectInformation->getIp();
    soapPort = connectInformation->getPort();  
    strSoapPort = this->intToStr(soapPort);
    rValue = "http://" + soapIP + ":" + strSoapPort + "/TafelWS/serverws?wsdl";
    return rValue;
} 

/* Neue Nachricht erstellen */
CORBA::Boolean MessageboardServer::createNewMessage(const char* message, const VS2::UserData& uData)
{
    bool created = false;
    cout << "Procedure createNewMessage() called" << endl;
    string strMessage(message); //char * in String umwandeln
    string strUserName(uData.userName);
    Message * messageObj = NULL;
    string msgID = "";
    //Pruefen ob eine Verknuepfung zu einer Soap-Tafel besteht
    created = this->messageBoard->createNewMessage(strMessage, uData.userID, strUserName, false);
    if(created && this->isConnectedToSoapBoard())
    {
        messageObj = this->messageBoard->getFirstMessage();
        msgID = messageObj->getId();
        created = this->sendMessageToSoapBoard(message, msgID, uData.userID);
        if(!created)
        {
            this->messageBoard->deleteMessage(uData.userID);
        }
    }
    return created;
}

//Senden einer Nachricht zu einer Verknuepften SOAP-Tafel
bool MessageboardServer::sendMessageToSoapBoard(const char * message, string messageID, int userId)
{
    bool rValue = true;
    ConnectInformation * ciSoap = NULL;
    string soapAdresse = "";
    int serverId = 0;
    string strMessage(message);
    SoapServerClient * ssc = NULL; //Klasse um mit dem Soap-Server zu kommunizieren
    int boardId = 0;
    cout << "Procedure sendMessageToSoapBoard() called" << endl;
    ciSoap = this->messageBoard->getConnectInformationSoap();
    soapAdresse = this->getSoapAdresse(ciSoap);
    serverId = this->messageBoard->getSoapBoardId();
    boardId = this->messageBoard->getBoardInformation()->getId();
    try
    {
        ssc = new SoapServerClient(serverId, soapAdresse);
        rValue = ssc->sendMessage(serverId, boardId, strMessage, messageID, userId);
        delete ssc; 
    }
    catch(...)
    {
        rValue = false;
    }
    return rValue;
}

//loeschen einer auf einer Verknuepften SOAP-Tafel
bool MessageboardServer::deleteMessageOnSoapBoard(const char * messageID)
{
    bool rValue = true;
    ConnectInformation * ciSoap = NULL;
    string soapAdresse = "";
    string strMessageID(messageID);
    SoapServerClient * ssc = NULL; //Klasse um mit dem Soap-Server zu kommunizieren
    int serverId = 0;
    int boardId = 0;
    cout << "Procedure deleteMessageOnSoapBoard() called" << endl;
    ciSoap = this->messageBoard->getConnectInformationSoap();
    serverId = this->messageBoard->getSoapBoardId();
    soapAdresse = this->getSoapAdresse(ciSoap);
    boardId = this->messageBoard->getBoardInformation()->getId();
    try
    {
        ssc = new SoapServerClient(serverId, soapAdresse);
        ssc->deleteMessage(strMessageID, serverId, boardId);
    }
    catch(...)
    {
        rValue = false;
    }
    delete ssc;
    return rValue;
}

//aendern einer auf einer Verknuepften SOAP-Tafel
bool MessageboardServer::modifyMessageOnSoapBoard(const char * message, const char * messageID)
{
    bool rValue = false;
    ConnectInformation * ciSoap = NULL;
    string soapAdresse = "";
    string strMessage(message);
    string strMessageID(messageID);
    SoapServerClient * ssc = NULL; //Klasse um mit dem Soap-Server zu kommunizieren
    int serverId = 0;
    int boardId = 0;
    cout << "Procedure modifyMessageOnSoapBoard() called" << endl;
    ciSoap = this->messageBoard->getConnectInformationSoap();
    serverId = this->messageBoard->getSoapBoardId();
    boardId = this->messageBoard->getBoardInformation()->getId();
    soapAdresse = this->getSoapAdresse(ciSoap);
    try
    {
        ssc = new SoapServerClient(serverId, soapAdresse);
        rValue = ssc->modifyMessage(strMessage, strMessageID, serverId, boardId);
    }
    catch(...)
    {
        rValue = false;
    }
    delete ssc;
    return rValue;
}


CORBA::Boolean MessageboardServer::modifyMessageSoap(const char* message, const char* messageID, ::CORBA::Long serverNr, const ::VS2::UserData& uData)
{
    cout << "Procedure modifyMessageSoap() called" << endl;
    return this->setMessage(message, messageID, uData);
}

CORBA::Boolean MessageboardServer::deleteMessageSoap(const char * messageID, const VS2::UserData& uData)
{
    cout << "Procedure deleteMessageSoap() called" << endl;
    return this->deleteMessage(messageID, uData);

}

CORBA::Boolean MessageboardServer::createMessageSoap(const char* message, const char * messageID, CORBA::Long serverNr, const VS2::UserData& uData)
{
    cout << "Procedure createMessageSoap() called" << endl;
    return this->saveMessage(message, messageID, uData);
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
    Message * msg = NULL;
    cout << "Procedure publishOnChilds() called" << endl;
    //Message als shared makieren
    msg = this->searchMessage(strMessageID);
    if(msg != NULL)
    {
        msg->setShared(true);
        this->messageBoard->saveBoard();
        //Prüfen on ChildBoards vorhanden sins
        childCount = this->messageBoard->getChildCount();
        if(childCount > 0)
        {
            childNames = this->messageBoard->getChildNames();
            //Verbindung zu den einzelnen childs aufbauen
            for(int i=0; i<childCount; i++)
            {
                childName = childNames[i];
                try
                {
                    //Verbindung zum Child-Board aufbauen
                    ciChild = this->messageBoard->getConnectInformationChild(childName);
                    if(ciChild != NULL)
                    {
                        try
                        {
                            sc = new ServerClient(ciChild);
                            //Vater-Infos beim Child speichern
                            workerValue = sc->publishMessage(strMessage, strMessageID, uData);
                            //wenn schalter gesetzt und nachricht veroeffentlicht werden konnte 
                            //Nachricht auf den childs des Child veroeffentlichen            
                            if(workerValue)
                            {
                                workerValue = sc->iterateChilds(strMessage, strMessageID, uData);
                            }       
                        }
                        catch(...)
                        {

                        }
                        //rValue auf false setzen falls ein Fehler aufgetreten ist            
                        delete sc;
                    }
                    else
                    {
                        rValue = true;
                    }
                    if(!workerValue && rValue)
                    {
                        rValue = workerValue;
                    }
                }
                catch(...)
                {
                    cout << "Error while publishOnChilds()" << endl;
                }
            }
        }
        else
        {
            rValue = true;
        }     
    }  
    return rValue;
}

//Shared Message auch beim Vater-Board loeschen
bool MessageboardServer::deleteMessageOnFather(const char * messageID, const VS2::UserData& uData)
{
    ServerClient * sc = NULL; //Klasse zum Kommunizieren mit einem anderen Server
    bool rValue = false; //Return Value
    ConnectInformation * ciFather = NULL;
    cout << "Procedure deleteMessageOnFather() called" << endl;
    try
    {
        //Verbindung zum Vater-Board aufbauen
        ciFather = this->messageBoard->getConnectInformationFather();
        if(ciFather != NULL)
        {
            sc = new ServerClient(ciFather);
            //Nachricht auf Vater veröffentlichen
            rValue = sc->deleteMessage(messageID, uData);
            delete sc;
        }
        else
        {
            rValue = true;
        }
    }
    catch(...)
    {
        cout << "Error while deleteMessageOnFather()" << endl;
    }
    return rValue;
}

/**/
bool MessageboardServer::deleteMessageOnChilds(const char * messageID, const VS2::UserData& uData)
{
   ServerClient * sc = NULL; //Klasse zum Kommunizieren mit einem anderen Server
    ConnectInformation * ciChild = NULL; //Verbindungsinformation eines Childs
    bool rValue = true; //Return Value
    int childCount = 0;
    string * childNames = 0; //Array fuer ChildNames
    string childName = ""; //Name eines Childs
    cout << "Procedure deleteMessageOnChilds() called" << endl;
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
            try
            {
                ciChild = this->messageBoard->getConnectInformationChild(childName);
                if(ciChild != NULL)
                {
                    sc = new ServerClient(ciChild);
                    //Vater-Infos beim Child speichern
                    rValue = sc->deleteMessage(messageID, uData); 
                    delete sc;
                }
                else
                {
                    rValue = true;
                }
            }
            catch(...)
            {
                cout << "Error while deleteMessageOnChilds()" << endl;
            }
        }
    } 
    else
    {
        rValue = true;
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
    Message * msg = NULL;
    cout << "Procedure publishOnFather() called" << endl;
    //Message als shared makieren
    msg = this->searchMessage(strMessageID);
    if(msg != NULL)
    {
        msg->setShared(true);
        this->messageBoard->saveBoard();
        //Verbindung zum Vater-Board aufbauen
        ciFather = this->messageBoard->getConnectInformationFather();
        if(ciFather != NULL)
        {
            try
            {        
                sc = new ServerClient(ciFather);
                //Nachricht auf Vater veröffentlichen
                rValue = sc->publishMessage(strMessage, strMessageID, uData);
                delete sc;
            }
            catch(...)
            {
                cout << "Error while publishOnFather()" << endl;
            }
        }
        else
        {
            rValue = true;
        }
    }
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
    //Message als shared markieren
    return this->messageBoard->createNewMessage(strMessage, strMessageID, uData.userID, strUserName, true);
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
            if(ciChild != NULL)
            {
                try
                {
                    sc = new ServerClient(ciChild);
                    //Vater-Infos beim Child speichern
                    sc->saveFatherInformation(id, name , ciMB, uData); 
                    delete sc;
                }
                catch(...)
                {
                    cout << "Error while notifyChildren()" << endl;
                }
            }
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
    if(ciFather != NULL)
    {
        sc = new ServerClient(ciFather);
        //Child-Infos beim Vater speichern
        sc->saveChildInformation(id, name , ciMB, uData); 
        delete sc;
    }
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
