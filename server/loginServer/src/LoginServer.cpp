/*
 *
 * LoginServer.cpp
 *
 *  Created on: 29.01.2017
 *      Author: Christian Patzek
 */

#include "./LoginServer.h"

static const int LoginServer::COLUMN_UID = 0;
static const int LoginServer::COLUMN_USER_NAME = 1;
static const int LoginServer::COLUMN_PASSWORD = 2;
static const int LoginServer::COLUMN_ADMIN_RIGHTS = 3;
static const int LoginServer::COLUMN_IP = 4;
static const int LoginServer::COLUMN_PORT = 5;
static const int LoginServer::COLUMN_HOMEBOARD = 6;
static const string LoginServer::DATABSE = "USERDATA";
static const string LoginServer::UIDCOUNT_TABLE = "UIDCOUNT";
static const int LoginServer::CONFIRM_USER_DATA = 10;
static const int LoginServer::INCREMENT_UID = 11;
static const int LoginServer::REG = 12;
static const int LoginServer::NEW_DATA = 13;
static const int LoginServer::USERNAME = 14;
static const int LoginServer::GET_UID = 15;

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
	  return 0;
};

static const int LoginServer::getUIdCallback()
{
	uIdCount=atoi(argv[0]);
}

LoginInformation LoginServer::login(UserData loginData)
{
	this->loginData=loginData;
	confirmUserData();
	return serverInformation;
}


void LoginServer::confirmUserData()
{
	serverInformation.server.setIp("Err DB");
	serverInformation.server.setPort("10000");
	serverInformation.setAdminRights(false);
	bool assert=openDataBase(CONFIRM_USER_DATA);
}

static int LoginServer::loginCallback(void *data, int argc, char **argv, char **azColName)
{
	if(argv[COLUMN_USER_NAME]==loginData.getUserName()&&argv[COLUMN_PASSWORD]==loginData.getPassword())
	{
		serverInformation.server.setIp(argv[COLUMN_IP]);
		serverInformation.server.setPort(argv[COLUMN_PORT]);
		if(argv[COLUMN_ADMIN_RIGHTS]=="true")
			serverInformation.setAdminRights(true);
		else
			serverInformation.setAdminRights(false);
		return 0;
	}
	else
	{
		serverInformation.server.setUserName("Err USER");
		return 1;
	}
}

static int LoginServer::uIdCallback(void *data, int argc, char **argv, char **azColName)
{
	return 0;
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

static int LoginServer::regCallback(void *data, int argc, char **argv, char **azColName)
{
	string serverName = *data;
	if(argv[COLUMN_HOMEBOARD]==serverName)
	{
		serverInformation.server.setIp(argv[COLUMN_IP]);
		serverInformation.server.setPort(argv[COLUMN_PORT]);
		return 0;
	}
	else
		return 1;

}

bool LoginServer::createNewData(string serverName)
{
	return openDataBase(NEW_DATA, serverName);
}

static int LoginServer::newDataCallback(void *data, int argc, char **argv, char **azColName)
{
	return 0;
}

bool LoginServer::confirmUserName(string userName)
{
	loginData.setUserName(userName);
	return openDataBase(USERNAME);
}

static int LoginServer::userNameCallback(void *data, int argc, char **argv, char **azColName)
{
	if(argv[COLUMN_USER_NAME]==loginData.getUserName())
		return 1;
	else
		return 0;
}

bool LoginServer::openDataBase(int callback, string serverName=" ")
{
	int rc;
	bool assert;
	sqlite3* db;
	string errMsg;
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
				string sqlCommand = "SELECT "+loginData.getUserName()+" from "+DATABASE;
				rc=sqlite3_exec(db, sqlCommand, loginCallback, (void*) serverName, &errMsg);
				if(rc!=SQLITE_OK)
				{
					cout << "Err DB: " << sqlite3_errmsg(db) << endl;
					return false;
				}break;
			case INCREMENT_UID:
				string count = itoa(uIdCount);;
				string sqlCommand = "UPDATE "+UIDCOUNT_TABLE+" SET UIDCOUNT = "+count;
				rc=sqlite3_exec(db, sqlCommand, uIdCallback, (void*) serverName, &errMsg);
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
					string sqlCommand = "SELECT "+serverName+" from "+DATABASE;
					rc=sqlite3_exec(db, sqlCommand, regCallback, (void*) serverName, &errMsg);
					if(rc!=SQLITE_OK)
					{
						cout << "Err DB: " << sqlite3_errmsg(db) << endl;
						return false;
					}
				}
				assert=createNewData(serverName);
				incrementUIdCount();break;
			case NEW_DATA:
				string uidcount = itoa(uIdCount);
				string sqlCommand = "INSERT INTO"+DATABASE+"(UID,USERNAME,PASSWORD,ADMINRIGHTS,IP,PORT,HOMEBOARD)"
									+"VALUES("+uidcount+", "+loginData.getUserName()", "+loginData.getPassword()
									+", false, "+serverInformation.getIp()+", "+serverInformation.getPort()", "+serverName;
				rc=sqlite3_exec(db, sqlCommand, newDataCallback, (void*) serverName, &errMsg);
				if(rc!=SQLITE_OK)
				{
					cout << "Err DB: " << sqlite3_errmsg(db) << endl;
					return false;
				}break;
			case USERNAME:
				string sqlCommand = "SELECT "+loginData.getUserName()+" from "+DATABASE;
				rc=sqlite3_exec(db, sqlCommand, regCallback, (void*) serverName, &errMsg);
				if(rc!=SQLITE_OK)
				{
					cout << "Err DB: " << sqlite3_errmsg(db) << endl;
					return false;
				}break;
			case GET_UID:
				string sqlCommand = "SELECT UID FROM "+UIDCOUNT_TABLE;
				rc=sqlite3_exec(db, sqlCommand, getUIdCallback, (void*) serverName, &errMsg);
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
