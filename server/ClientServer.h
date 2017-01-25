#ifndef CLIENTSERVER_H_
#define CLIENTSERVER_H_

#include "./VS2_klein.hh"
#include "./src/Messageboard.h"

class ClientServer: public POA_ClientMessageboardInterface, public PortableServer::RefCountServantBase
{
    private:
        Messageboard * messageBoard;
    public:
        ClientServer();
        ~ClientServer();
        CORBA::Boolean setMessage(const char* message, ::CORBA::Long uid, const char* uName);
        CORBA::Boolean deleteMessage(::CORBA::Long uid);
        CORBA::Boolean createNewMessage(const char* message, ::CORBA::Long uid, const char* uName);
        MessageData* getNextMessage();
        MessageData* getPreviousMessage();
};


#endif
