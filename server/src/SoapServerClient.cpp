#include "SoapServerClient.h"
#include <string>
#include <sstream>
#include <iostream>
#include "SOAP-Client/src/requests/RequestException.h"
#include "SOAP-Client/src/requests/SoapRequest.h"
#include "SOAP-Client/src/requests/DeleteRequest.h"
#include "SOAP-Client/src/requests/ModifyRequest.h"
#include "SOAP-Client/src/requests/SendRequest.h"
#include "SOAP-Client/src/requests/SoapException.h"
#include "SOAP-Client/src/SoapDeliverer.h"

using namespace std;

//
SoapServerClient::SoapServerClient(int serverNr, string serverAdresse)
{
    //this->soapDeliverer = new SoapDeliverer(serverNr, serverAdresse);
}

bool SoapServerClient::isSoapMessage(string messageID)
{
    return messageID.find("SOAP")!=std::string::npos;
}

//Wandeln von String in integer
int SoapServerClient::strToInt(string strNumber)
{
    int rValue = 0;
    try
    {
        istringstream ( strNumber ) >> rValue;
    }
    catch(...)
    {
        rValue = 0;
    }
    return rValue;

}

//Wandeln von Integer in String
string SoapServerClient::intToStr(int number)
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


//Erstellt fuer das SoapBoard die ServerNr der Nachricht
//wird anhand der MessageID ermittelt. Bei Nachricht des eigenen
//Boards wird einfach die verknuepfte SOAP-Server-ID verwendet
int SoapServerClient::createSoapServerNr(string messageID, int soapServerNr, int boardID)
{
    int createdServerNr = 0;
    int strPos = 0;
    string copyStr = "";
    //Pruefen ob es sich um eine Nachricht vom Soap-Board handelt
    if(this->isSoapMessage(messageID))
    {
        //Aufbau: (-)4-SOAP4(ServerNr)1(UserID)2(LaufNr)
        strPos = messageID.find("SOAP") ;
        copyStr = messageID.substr(0, strPos-1);
        createdServerNr = this->strToInt(copyStr);
    }
    else
    {
        //Aufbau: 14-(BoardID)12345(LaufNr)
        strPos = messageID.find("-") ;
        copyStr = messageID.substr(0, strPos);
        createdServerNr = this->strToInt(copyStr);
        //Pruefen ob es sich um eine NAchricht des eigenen Boards handelt
        if(createdServerNr == boardID)
        {
            createdServerNr = soapServerNr;
        }
        else
        {
            //Bei Nachrichten die nicht dem Board gehoeren wird die Server
            //nummer negativ generiert
            createdServerNr = createdServerNr * (-1);
        }
    } 
    return createdServerNr;   
}

//erstellt fuer das SOapBoard die message ID
int SoapServerClient::createSoapMessageId(string messageID, int soapServerNr, int boardId)
{
    int strPos = 0;
    int copyLength = 0;
    string copyStr = "";
    int soapMessageID = 0;
    //Pruefen ob es sich um eine Nachricht vom Soap-Board handelt
    if(this->isSoapMessage(messageID))
    {
        //Aufbau: (-)4-SOAP4(ServerNr)1(UserID)2(LaufNr)
        //soapMessageID = 412
        strPos = messageID.find("SOAP") + 4;
        copyLength = messageID.length()-strPos;
        copyStr = messageID.substr(strPos, copyLength);
        soapMessageID = this->strToInt(copyStr);
    }
    else
    {
        //Aufbau: 14-(BoardID)12345(LaufNr)
        //soapMessageID = soapServerID
        soapMessageID = this->createSoapServerNr(messageID, soapServerNr, boardId);
        strPos = messageID.find("-") ;
        //loeschen bis inkl. "-" zeichen
        copyStr = messageID.erase(0, strPos+1);
        copyStr = this->intToStr(soapMessageID) + copyStr;
        soapMessageID = this->strToInt(copyStr);
        //MessageId soll negativ sein
        if(soapMessageID > 0)
        {
            soapMessageID = soapMessageID * (-1);
        }
    }
    cout << "MessageID: " << soapMessageID << endl;
    return soapMessageID;
}

//Aendern einer Nachricht auf einem SoapBoard
bool SoapServerClient::modifyMessage(string message, string messageID, int soapServerNr, int boardId)
{
    bool rValue = true;
    SoapRequest * soapRequest = NULL;
    int sendMessageID = 0;
    try
    {    
        //ModifyRequest aendern eine Nachricht im Soap-Board an
        sendMessageID = this->createSoapMessageId(messageID, soapServerNr, boardId);
       /*  soapRequest = new ModifyRequest(sendMessageID,  message);
        cout << this->soapDeliverer->deliver(soapRequest) << endl;
        delete soapRequest; */

    }
    catch (...)
    {
        rValue = false;
    }
    return rValue;
}

//Loeschen einer Nachricht auf einem SoapBoard
bool SoapServerClient::deleteMessage(string messageID, int soapServerNr, int boardId)
{
    bool rValue = true;
    SoapRequest * soapRequest = NULL;
    int sendMessageID = 0;
    try
    {
        //DeleteRequest loescht eine Nachricht im Soap-Board an
        sendMessageID = this->createSoapMessageId(messageID, soapServerNr, boardId);
       /* soapRequest = new DeleteRequest(sendMessageID);
        cout << this->soapDeliverer->deliver(soapRequest) << endl;
        delete soapRequest; */

    }
    catch (...)
    {
        rValue = false;
    }
    return rValue;
}

//Anlegen einer Nachricht auf einem SoapBoard
bool SoapServerClient::sendMessage(int soapServerNr, int boardId, string message, string messageID, int userID)
{
    bool rValue = true;
    SoapRequest * soapRequest = NULL;
    int sendMessageID = 0;
    int sendServerNr = 0;
    bool isGlobal = false;
    try
    {
        //SendRequest legt eine Nachricht im Soap-Board an
        sendMessageID = this->createSoapMessageId(messageID, soapServerNr, boardId);
        sendServerNr = this->createSoapServerNr(messageID, soapServerNr, boardId);
        cout << "ServerNr: " << sendServerNr << endl;
       /* isGlobal = sendServerNr < 0;
        soapRequest = new SendRequest(sendMessageID, userID, sendServerNr, message, isGlobal);
        cout << this->soapDeliverer->deliver(soapRequest) << endl;
        delete soapRequest;*/

    }
    catch (...)
    {
        rValue = false;
    }

    return rValue;
}


//
SoapServerClient::~SoapServerClient()
{
    delete this->soapDeliverer;
}