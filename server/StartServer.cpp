#include <iostream>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <assert.h>
#include <signal.h>
#include <unistd.h>
#include "./src/MessageboardServer.h"
#include "./src/VS2.hh"

using namespace std;
using namespace VS2;

int main(int argc, char ** args)
{
  // --------------------------------------------------------------------------
  // Start CORBA server:
  // --------------------------------------------------------------------------
                                                                                
  try {
    //------------------------------------------------------------------------
    // 1) Initialize ORB
    // 2) Get reference to root POA
    // 3) Bind to name service
    // 4) Initialize servant object
    //------------------------------------------------------------------------
                                                                                
    //------------------------------------------------------------------------
    // Initialize CORBA ORB - "orb"
    //------------------------------------------------------------------------
	cout << "Server gestartet..." << endl; 
    CORBA::ORB_var orb = CORBA::ORB_init(argc, args, "omniORB4");
                                                                                
    //------------------------------------------------------------------------
    // Servant must register with POA in order to be made available for client
    // Get reference to the RootPOA.
    //------------------------------------------------------------------------
    cout << "Registriere POA ..." << endl;
    CORBA::Object_var obj = orb->resolve_initial_references("RootPOA");
    PortableServer::POA_var _poa = PortableServer::POA::_narrow(obj);                                                                           
    //------------------------------------------------------------------------
    // Operations defined in object interface invoked via an object reference.
    // Instance of CRequestSocketStream_i servant is initialized.
    //------------------------------------------------------------------------     
    cout << "Create MessageboardServer-Objekt ..." << endl;
    PortableServer::Servant_var<MessageboardServer> messageboardServer = new MessageboardServer();                                                               
    //------------------------------------------------------------------------
    // ObjectId_var class defined in poa.h
    // typedef String_var ObjectId_var; CORBA_ORB.h
    // ???????
                                                                                
    //------------------------------------------------------------------------
    // Servant object activated in RootPOA.
    // (Object id used for various POA operations.)
    //------------------------------------------------------------------------
    PortableServer::ObjectId_var messageboardServer_oid
                                = _poa->activate_object(messageboardServer);
                                                                                
    //------------------------------------------------------------------------
    // Obtain object reference from servant and register in naming service(??)
    //------------------------------------------------------------------------
    CORBA::Object_var SA_obj = messageboardServer->_this();
                                                                                
    //------------------------------------------------------------------------
    // Obtain a reference to the object, and print it out as string IOR.
    //------------------------------------------------------------------------
    CORBA::String_var sior(orb->object_to_string(SA_obj));
    cerr << "'" << (char*)sior << "'" << endl;
                                                                                
    //========================================================================
    // Bind (rebind) object (orb) to name (SA_obj)
    //========================================================================
                                                                                
    //------------------------------------------------------------------------
    // Bind object to name service as defined by directive InitRef
    // and identifier "OmniNameService" in config file omniORB.cfg.
    //------------------------------------------------------------------------
    cout << "Bind NameService ..." << endl;
    CORBA::Object_var obj1=orb->resolve_initial_references("NameService");
    assert(!CORBA::is_nil(obj1));                                  
    //------------------------------------------------------------------------
    // narrow this to the naming context
    //------------------------------------------------------------------------
    CosNaming::NamingContext_var nc = CosNaming::NamingContext::_narrow(obj1);
    assert(!CORBA::is_nil(nc.in()));
                                                                                
    //------------------------------------------------------------------------
    // Bind to CORBA name service. Same name to be requested by client.
    //------------------------------------------------------------------------
    cout << "Bind Corba-NameService ..." << endl;  
    CosNaming::Name name;
    name.length(1);
    name[0].id=CORBA::string_dup("DataServiceName1");
    nc->rebind (name,SA_obj.in());                                                                              
    //========================================================================
                                                                                
    messageboardServer->_remove_ref();
                                                                                
    //------------------------------------------------------------------------
    // Activate the POA manager
    //------------------------------------------------------------------------
    PortableServer::POAManager_var pmgr = _poa->the_POAManager();
    pmgr->activate();
                                                                                
    //------------------------------------------------------------------------
    // Accept requests from clients
    //------------------------------------------------------------------------
    cout << "Server is running ..." << endl;    
    orb->run();                                                        
    //------------------------------------------------------------------------
    // If orb leaves event handling loop.
    // - currently configured never to time out (??)
    //------------------------------------------------------------------------
    orb->destroy();
                                                                                
    free(name[0].id); // str_dup does a malloc internally
  }
                                                                                
  catch(CORBA::SystemException&) {
    cerr << "Caught CORBA::SystemException." << endl;
  }
  catch(CORBA::Exception&) {
    cerr << "Caught CORBA::Exception." << endl;
  }
  catch(omniORB::fatalException& fe) {
    cerr << "Caught omniORB::fatalException:" << endl;
    cerr << "  file: " << fe.file() << endl;
    cerr << "  line: " << fe.line() << endl;
    cerr << "  mesg: " << fe.errmsg() << endl;
  }
  catch(exception& e) {
    cerr << "Error: " << e.what() << endl;
  }   
  catch(...) {
    cerr << "Caught unknown exception." << endl;
  }       
  cout << "Server closed" << endl;                                                                      
  return 0;    
} 
