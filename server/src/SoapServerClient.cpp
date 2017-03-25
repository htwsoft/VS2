#include "SoapServerClient.h"
#include <string>
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
    this->soapDeliverer = new SoapDeliverer(serverNr, serverAdresse);
}

//Anlegen einer NAchricht auf einem SoapBoard
bool SoapServerClient::sendMessage(int soapServerNr, string message, string messageID, int userID)
{
    bool rValue = true;
    SoapRequest * soapRequest = NULL;
    try
    {
        //SendRequest legt eine Nachricht im Soap-Board an
        soapRequest = new SendRequest(87, userID, soapServerNr, message);
        cout << this->soapDeliverer->deliver(soapRequest) << endl; //Done = alles ok
        delete soapRequest;
        
    }
    catch ( const string& e )
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