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
        virtual CORBA::Boolean setMessage(const char* message, ::CORBA::Long uid, const char* uName);
        virtual CORBA::Boolean deleteMessage(::CORBA::Long uid);
        virtual CORBA::Boolean createNewMessage(const char* message, ::CORBA::Long uid, const char* uName);
        virtual MessageData * getNextMessage();
        virtual MessageData * getPreviousMessage();
};


#endif
