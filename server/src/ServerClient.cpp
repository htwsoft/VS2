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
    int    argc = 0;       // Dummy variables to support following call.
    char** argv = 0;
    CORBA::ORB_var orb = CORBA::ORB_init(argc, argv);
                                                                                
    //------------------------------------------------------------------------
    // Bind ORB object to name service object.
    // (Reference to Name service root context.)
    //------------------------------------------------------------------------
    CORBA::Object_var obj = orb->resolve_initial_references("NameService");
    assert (!CORBA::is_nil(obj.in()));
                                                                                
    //------------------------------------------------------------------------
    // Narrow this to the naming context (Narrowed reference to root context.)
    //------------------------------------------------------------------------
    CosNaming::NamingContext_var nc =
                        CosNaming::NamingContext::_narrow(obj.in());
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
    CORBA::Object_var obj1 = nc->resolve(_corbaCosName);
    assert(!CORBA::is_nil(obj1.in()));
                                                                                
    m_Data = MessageboardServerInterface::_narrow(obj1.in());
    if (CORBA::is_nil(m_Data.in()))
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
  catch(CORBA::SystemException& ) {
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

ServerClient::~ServerClient()
{

}
