/*
 *
 * LoginServer.cpp
 *
 *  Created on: 29.01.2017
 *      Author: Christian Patzek
 */

#include "./LoginServer.h"

static const int COLUMN_UID = 0;
static const int COLUMN_USER_NAME = 1;
static const int COLUMN_PASSWORD = 2;
static const int COLUMN_ADMIN_RIGHTS = 3;
static const int COLUMN_IP = 4;
static const int COLUMN_PORT = 5;
static const int COLUMN_HOMEBOARD = 6;
const char* LoginServer::DATABASE = "USERDATA";
const char* LoginServer::UIDCOUNT_TABLE = "UIDCOUNT";
int const LoginServer::CONFIRM_USER_DATA = 10;
int const LoginServer::INCREMENT_UID = 11;
int const LoginServer::REG = 12;
int const LoginServer::NEW_DATA = 13;
int const LoginServer::USERNAME = 14;
int const LoginServer::GET_UID = 15;

static int getUIdCallback(void* data, int argc, char **argv, char **azColName);
static int userNameCallback(void* data, int argc, char **argv, char **azColName);
static int newDataCallback(void *data, int argc, char **argv, char **azColName);
static int regCallback(void* data, int argc, char **argv, char **azColName);
static int uIdCallback(void* data, int argc, char **argv, char **azColName);
static int loginCallback(void* data, int argc, char **argv, char **azColName);

LoginServer::LoginServer()
{
	openDataBase(GET_UID);
	try
	{
	    cout << "Server gestartet..." << endl;
	    CORBA::ORB_var orb = CORBA::ORB_init(argc, args, "omniORB4");
	    cout << "Registriere POA ..." << endl;
	    CORBA::Object_var obj = orb->resolve_initial_references("RootPOA");
	    PortableServer::POA_var _poa = PortableServer::POA::_narrow(obj);
	    cout << "Create MessageboardServer-Objekt ..." << endl;
	    PortableServer::Servant_var<MessageboardServer> messageboardServer = new MessageboardServer();
	    PortableServer::ObjectId_var messageboardServer_oid
	                                = _poa->activate_object(messageboardServer);
	    CORBA::Object_var SA_obj = messageboardServer->_this();
	    CORBA::String_var sior(orb->object_to_string(SA_obj));
	    cerr << "'" << (char*)sior << "'" << endl;
	    cout << "Bind NameService ..." << endl;
	    CORBA::Object_var obj1=orb->resolve_initial_references("NameService");
	    assert(!CORBA::is_nil(obj1));

	    CosNaming::NamingContext_var nc = CosNaming::NamingContext::_narrow(obj1);
	    assert(!CORBA::is_nil(nc.in()));
	    cout << "Bind Corba-NameService ..." << endl;
	    CosNaming::Name name;
	    name.length(1);
	    name[0].id=CORBA::string_dup("DataServiceName1");
	    nc->rebind (name,SA_obj.in());
	    LoginServer->_remove_ref();
	    PortableServer::POAManager_var pmgr = _poa->the_POAManager();
	    pmgr->activate();
	    cout << "Server is running ..." << endl;
	    orb->run();
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
}

static int getUIdCallback(void* data, int argc, char **argv, char **azColName)
{
	LoginServer* ptrToData = (LoginServer*)data;	
	ptrToData->setUIdCount(atoi(argv[0]));
	return 0;
}

static int loginCallback(void* data, int argc, char **argv, char **azColName)
{
	LoginServer* ptrToData = (LoginServer*)data;	
	if(argv[COLUMN_USER_NAME]==ptrToData->getLoginData().getUserName()&&argv[COLUMN_PASSWORD]==ptrToData->getLoginData().getPassword())
	{
		ptrToData->getServerInformation().getServer().setIp(argv[COLUMN_IP]);
		ptrToData->getServerInformation().getServer().setPort(atoi(argv[COLUMN_PORT]));
		ptrToData->getServerInformation().setUId(atoi(argv[COLUMN_UID]));
		if(argv[COLUMN_ADMIN_RIGHTS]==(char*)"true")
			ptrToData->getServerInformation().setAdminRights(true);
		else
			ptrToData->getServerInformation().setAdminRights(false);
		return 0;
	}
	else
	{
		ptrToData->getLoginData().setUserName("Err USER");
		return 1;
	}
}

static int regCallback(void* data, int argc, char **argv, char **azColName)
{
	LoginServer* ptrToData = (LoginServer*)data;	
	if(argv[COLUMN_HOMEBOARD]==ptrToData->getBoardName())
	{
		ptrToData->getServerInformation().getServer().setIp(argv[COLUMN_IP]);
		ptrToData->getServerInformation().getServer().setPort(atoi(argv[COLUMN_PORT]));
		return 0;
	}
	else
		return 1;

}

static int newDataCallback(void* data, int argc, char **argv, char **azColName)
{
	return 0;
}

static int userNameCallback(void* data, int argc, char **argv, char **azColName)
{
	LoginServer* ptrToData = (LoginServer*)data;	
	if(argv[COLUMN_USER_NAME]==ptrToData->getLoginData().getUserName())
		return 1;
	else
		return 0;
}

static int uIdCallback(void* data, int argc, char **argv, char **azColName)
{
	return 0;
}

LoginInformation LoginServer::login(UserData loginData)
{
	this->loginData=loginData;
	confirmUserData();
	return serverInformation;
}


bool LoginServer::confirmUserData()
{
	serverInformation.getServer().setIp("Err DB");
	serverInformation.getServer().setPort(10000);
	serverInformation.setAdminRights(false);
	bool assert=openDataBase(CONFIRM_USER_DATA);
	return assert;
}

void LoginServer::incrementUIdCount()
{
	uIdCount++;
	bool assert=openDataBase(INCREMENT_UID);
}

bool LoginServer::reg(UserData loginData, string serverName)
{
	this->loginData=loginData;
	return openDataBase(REG, serverName);
}

bool LoginServer::createNewData(string serverName)
{
	return openDataBase(NEW_DATA, serverName);
}

bool LoginServer::confirmUserName(string userName)
{
	loginData.setUserName(userName);
	return openDataBase(USERNAME);
}

bool LoginServer::openDataBase(int callback, string serverName)
{
	this->boardName=serverName;	
	int rc;
	bool assert;
	sqlite3* db;
	char* errMsg;
	string sqlCommand;
	char* count;
	sprintf(count, "%d", uIdCount);
	rc=sqlite3_open(DATABASE, &db);
	if(rc)
	{
		cout << "Err DB: " << sqlite3_errmsg(db) << endl;
		return false;
	}
	else
	{
		switch(callback)
		{
			case CONFIRM_USER_DATA:
				sqlCommand = "SELECT "+loginData.getUserName()+" from "+(string)DATABASE;
				rc=sqlite3_exec(db, sqlCommand.c_str(), loginCallback, (void*)this, &errMsg);
				if(rc!=SQLITE_OK)
				{
					cout << "Err DB: " << sqlite3_errmsg(db) << endl;
					return false;
				}break;
			case INCREMENT_UID:
				sqlCommand = "UPDATE "+(string)UIDCOUNT_TABLE+" SET UIDCOUNT = "+(string)count;
				rc=sqlite3_exec(db, sqlCommand.c_str(), uIdCallback, 0, &errMsg);
				if(rc!=SQLITE_OK)
				{
					cout << "Err DB: " << sqlite3_errmsg(db) << endl;
					return false;
				}break;
			case REG:
				if(confirmUserName(loginData.getUserName()))
						return false;
				else
				{
					sqlCommand = "SELECT "+serverName+" from "+(string)DATABASE;
					rc=sqlite3_exec(db, sqlCommand.c_str(), regCallback, (void*)this, &errMsg);
					if(rc!=SQLITE_OK)
					{
						cout << "Err DB: " << sqlite3_errmsg(db) << endl;
						return false;
					}
				}
				assert=createNewData(serverName);
				incrementUIdCount();break;
			case NEW_DATA:
				char* port;
				sprintf(port, "%d", serverInformation.getServer().getPort());
				sqlCommand = "INSERT INTO "+(string)DATABASE+"(UID,USERNAME,PASSWORD,ADMINRIGHTS,IP,PORT,HOMEBOARD)"
					     +"VALUES("+(string)count+", "+loginData.getUserName()+", "+loginData.getPassword()
					     +", false, "+serverInformation.getServer().getIp()+", "+(string)port+", "+serverName;
				rc=sqlite3_exec(db, sqlCommand.c_str(), newDataCallback, 0, &errMsg);
				if(rc!=SQLITE_OK)
				{
					cout << "Err DB: " << sqlite3_errmsg(db) << endl;
					return false;
				}break;
			case USERNAME:
				sqlCommand = "SELECT "+loginData.getUserName()+" from "+(string)DATABASE;
				rc=sqlite3_exec(db, sqlCommand.c_str(), userNameCallback, (void*)this, &errMsg);
				if(rc!=SQLITE_OK)
				{
					cout << "Err DB: " << sqlite3_errmsg(db) << endl;
					return false;
				}break;
			case GET_UID:
				sqlCommand = "SELECT UID FROM "+(string)UIDCOUNT_TABLE;
				rc=sqlite3_exec(db, sqlCommand.c_str(), getUIdCallback, (void*)this, &errMsg);
				if(rc!=SQLITE_OK)
				{
					cout << "Err DB: " << sqlite3_errmsg(db) << endl;
					return false;
				}break;
		}
	}
	sqlite3_close(db);
	return true;
}
