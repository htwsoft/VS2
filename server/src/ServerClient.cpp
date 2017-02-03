#include <assert.h>
#include "./ServerClient.h"
#include "./VS2.hh"

using namespace VS2;

ServerClient::ServerClient(ConnectInformation * connectInformation)
{
 try {
    //------------------------------------------------------------------------
    // Initialize ORB object.
    //------------------------------------------------------------------------
    
    //Init parameter für Servclient erstellen
    this->connectInformation = connectInformation;
    this->createInitParameter();
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
    // This same name ("DataServiceName1") is used by the CORBA server when
    // binding to the name server (CosNaming::Name).
    //------------------------------------------------------------------------   
    CosNaming::Name _corbaCosName;
    _corbaCosName.length(1);
    _corbaCosName[0].id=CORBA::string_dup("DataServiceName1");
                                                                                
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
  }
  catch(CORBA::COMM_FAILURE& ex) {
    cerr << "Caught system exception COMM_FAILURE -- unable to contact the "
         << "object." << endl;
    throw DS_ServerConnectionException();
    return;
  }
  catch(CORBA::SystemException&) {
    cerr << "Caught a CORBA::SystemException." << endl;
    throw DS_SystemException();
    return;
  }
  catch(CORBA::Exception& ) {
    cerr << "Caught CORBA::Exception." << endl;
    throw DS_Exception();
    return;
  }  catch(omniORB::fatalException& fe) {
    cerr << "Caught omniORB::fatalException:" << endl;
    cerr << "  file: " << fe.file() << endl;
    cerr << "  line: " << fe.line() << endl;
    cerr << "  mesg: " << fe.errmsg() << endl;
    throw DS_FatalException();
    return;
  }
  catch(...) {
    cerr << "Caught unknown exception." << endl;
    throw DS_Exception();
    return;
  }
  return;
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
    string strInitName = "-ORBInitRef";
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
    orb->destroy();
}
