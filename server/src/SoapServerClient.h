#ifndef SOAPSERVERCLIENT_H_
#define SOAPSERVERCLIENT_H_

#include <string>
#include "SOAP-Client/src/SoapDeliverer.h"
#include "SOAP-Client/src/requests/SoapRequest.h"

using namespace std;

class SoapServerClient
{
    private:
        SoapDeliverer * soapDeliverer;
        SoapRequest * soapRequest;
        int createSoapMessageId(string messageID, int soapServerNr);
        int createSoapServerNr(string messageID, int soapServerNr, int boardID);
        bool isSoapMessage(string messageID);
        int strToInt(string strNumber);
    public:
        SoapServerClient(int serverNr, string serverAdresse);
        bool sendMessage(int soapServerNr, int boardId, string message, string messageID, int userID);
        bool modifyMessage(string message, string messageID, int soapServerNr);
        bool deleteMessage(int soapServerNr, string messageID);
        ~SoapServerClient();
};

#endif