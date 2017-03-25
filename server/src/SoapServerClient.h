#ifndef MESSAGEBOARDSERVER_H_
#define MESSAGEBOARDSERVER_H_

#include <string>
#include "SOAP-Client/src/SoapDeliverer.h"
#include "SOAP-Client/src/requests/SoapRequest.h"

using namespace std;

class SoapServerClient
{
    private:
        SoapDeliverer * soapDeliverer;
        SoapRequest * soapRequest;
        int createSoapMessageId(string messageID);
    public:
        SoapServerClient(int serverNr, string serverAdresse);
        bool sendMessage(int soapServerNr, int boardId, string message, string messageID, int userID);
        ~SoapServerClient();
};

#endif