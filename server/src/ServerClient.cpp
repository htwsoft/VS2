#include <assert.h>
#include "./ServerClient.h"
#include "./VS2.hh"

using namespace VS2;

ServerClient::ServerClient(ConnectInformation * connectInformation)
{
    //Init parameter für Servclient erstellen
    this->connectInformation = new ConnectInformation(connectInformation->getIp(), connectInformation->getPort());
    this->createInitParameter();
}

bool ServerClient::connectToServer()
{
    bool connected = false;
    try
    {
        this->orb = CORBA::ORB_init(this->initParameterCount, this->initParameter, "omniORB4");                                                                              
        //------------------------------------------------------------------------
        // Bind ORB object to name service object.
        // (Reference to Name service root context.)
        //------------------------------------------------------------------------
        this->orbObj = this->orb->resolve_initial_references("NameService");
        assert (!CORBA::is_nil(this->orbObj.in()));
                                                                                    
        //------------------------------------------------------------------------
        // Narrow this to the naming context (Narrowed reference to root context.)
        //------------------------------------------------------------------------
        CosNaming::NamingContext_var nc =
                            CosNaming::NamingContext::_narrow(this->orbObj.in());
        assert (!CORBA::is_nil(nc.in()));
                                                                                    
        //------------------------------------------------------------------------
        // The "name text" put forth by CORBA server in name service.
        // This sam0e name ("DataServiceName1") is used by the CORBA server when
        // binding to the name server (CosNaming::Name).
        //------------------------------------------------------------------------   
        CosNaming::Name _corbaCosName;
        _corbaCosName.length(1);
        _corbaCosName[0].id=CORBA::string_dup("DataServiceName2");
                                                                                    
        //------------------------------------------------------------------------
        // Resolve "name text" identifier to an object reference.
        //------------------------------------------------------------------------
        this->resObj = nc->resolve(_corbaCosName);
        assert(!CORBA::is_nil(this->resObj.in()));
                                                                                    
        this->m_Data = MessageboardServerInterface::_narrow(this->resObj.in());
        if (CORBA::is_nil(this->m_Data.in()))
        {
            cerr << "IOR is not an SA object reference." << endl;
        }
        connected = true;
    }
    catch(CORBA::COMM_FAILURE& ex) 
    {
        cerr << "Caught system exception COMM_FAILURE -- unable to contact the "
            << "object." << endl;
    }
    catch(CORBA::SystemException&) 
    {
        cerr << "Caught a CORBA::SystemException." << endl;
    }
    catch(CORBA::Exception& ) 
    {
        cerr << "Caught CORBA::Exception." << endl;
    }  catch(omniORB::fatalException& fe) 
    {
        cerr << "Caught omniORB::fatalException:" << endl;
        cerr << "  file: " << fe.file() << endl;
        cerr << "  line: " << fe.line() << endl;
        cerr << "  mesg: " << fe.errmsg() << endl;
    }
    catch(...) 
    {
        cerr << "Caught unknown exception." << endl;
    }
    return connected;
}

/* Veroeffentlichen von Nachrichten auf den Childs eines Childs */
bool ServerClient::iterateChilds(string message, string messageID, const VS2::UserData& uData)
{
    bool rValue = false;
    try
    {
        rValue = this->m_Data->publishOnChilds(message.c_str(), messageID.c_str(), uData, true);
    }
    catch(...)
    {
        cout << "Error in iterateChilds()" << endl;
    }
    return rValue;
}

/* loeschen von Nachrichten auf den childs */
bool ServerClient::deleteMessage(const char * messageID, const VS2::UserData& uData)
{
    bool rValue = false;
    try
    {
        rValue = this->m_Data->deleteMessage(messageID, uData);
    }
    catch(...)
    {
        cout << "Error in deleteMessage()" << endl;
    }
    return rValue;
}

//Aendern einer Nachricht
bool ServerClient::modifyMessage(const char* message, const char* messageID, const VS2::UserData& uData)
{
    bool rValue = false;
    try
    {
        rValue = this->m_Data->setMessage(message, messageID, uData);
    }
    catch(...)
    {
        cout << "Error in modifyMessage()" << endl;
    }
    return rValue;
    
}

/* veröffentlichen einer Nachricht auf einem Child oder Father-Board */
/* wird nur von sendendem Board aufgerufen. nicht von Client */
bool ServerClient::publishMessage(string message, string messageID, const VS2::UserData& uData)
{
    bool rValue = false;
    try
    {
        rValue = this->m_Data->saveMessage(message.c_str(), messageID.c_str(), uData);
    }
    catch(...)
    {
        cout << "Error in publishMessage()" << endl;
    }
    return rValue;
}

/* Liefert die ConnectInformationen des Vaters */
ConnectInformation ServerClient::connectToFather(const VS2::UserData& uData)
{
    ConnectInformation newCI("", 0);
    try
    {
        ConnectInformationData * ciData = NULL;
        ciData = this->m_Data->connectToFather(uData);
        string strIp(ciData->ip);
        newCI.setPort(ciData->port);
        newCI.setIp(strIp);
    }
    catch(...)
    {
        cout << "Error in connectToFather()" << endl;
    }   
    return newCI;
}

/* Funktion nur zum Testen*/
void ServerClient::notifyFather(const VS2::UserData& uData)
{
    try
    {
        this->m_Data->notifyFather(uData);
    }
    catch(...)
    {
        cout << "Error in notifyFather()" << endl;
    }       
}

/* Liefert die ConnectInformationen eines Childs */ 
ConnectInformation ServerClient::connectToChild(string childName)
{
    ConnectInformation newCI("", 0);
    try
    {
        ConnectInformationData * ciData = NULL;
        ciData = this->m_Data->connectToChild(childName.c_str());
        string strIp(ciData->ip);
        newCI.setPort(ciData->port);
        newCI.setIp(strIp);
    }
    catch(...)
    {
        cout << "Error in connectToChild()" << endl;
    } 
    return newCI;
}

/* speichern von Fathe-Informationen eines Servers */
void ServerClient::saveFatherInformation(int id, string name, const ConnectInformation * connectInformation, const VS2::UserData& uData)
{
    try
    {
        ConnectInformationData ciData;
        ciData.ip = connectInformation->getIp().c_str();
        ciData.port = connectInformation->getPort();
        this->m_Data->saveFatherInformation(id, name.c_str(), ciData, uData);
    }
    catch(...)
    {
        cout << "Error in saveFatherInformation()" << endl;
    } 
}

/* speichern von Child-Informationen eines Servers */
void ServerClient::saveChildInformation(int id, string name, const ConnectInformation * connectInformation, const VS2::UserData& uData)
{
    try
    {
        ConnectInformationData ciData;
        ciData.ip = connectInformation->getIp().c_str();
        ciData.port = connectInformation->getPort();
        this->m_Data->saveChildInformation(id, name.c_str(), ciData, uData);
    }
    catch(...)
    {
        cout << "Error in saveChildInformation()" << endl;
    } 
}

/* Funktion macht aus einem String ein char * Objekt */
char * ServerClient::copyString(string zeichen)
{
    char * cZeichen = 0;
    cZeichen = new char[zeichen.length()];
    strcpy(cZeichen, zeichen.c_str());    
    return cZeichen;
}

/* Funktion erstellt die Startparameter für eine OmniOrb client */
void ServerClient::createInitParameter()
{
    string strPort = std::to_string(this->connectInformation->getPort());
    string strInitName = "-ORBendPointPublish";
    
    string strInitParam = "NameService=corbaloc::"+ this->connectInformation->getIp() + ":" + strPort + "/NameService";
    string strTraceName = "-ORBtraceLevel";
    string strTraceParam = "5";
    char * cInitName = copyString(strInitName);
    char * cInitParam = copyString(strInitParam);
    char * cTraceName = copyString(strTraceName);
    char * cTraceParam = copyString(strTraceParam);
    this->initParameter[0] = cInitName;
    this->initParameter[1] = cInitParam;
    this->initParameter[2] = cTraceName;
    this->initParameter[3] = cTraceParam;    
}

ServerClient::~ServerClient()
{
    delete this->connectInformation;
    orb->destroy();
}
