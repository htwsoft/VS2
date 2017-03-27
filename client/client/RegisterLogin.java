package client;

import org.omg.CosNaming.*;
import org.omg.CORBA.*;
import VS2.*;

public class RegisterLogin {
	 
	private static final String METHOD = "DataServiceName";
	private LoginServerInterface dbImpl;
	private LoginInformation loginInfo;
	private boolean angemeldet = true;//wenn db da ist auf false setzten
	private String[] url;
	int port;
	String ip;
	ORB orb;
	
	public boolean connectLoginServer(){
		try {
			// Initialisiere ORB und beschaffe Zugang zum 'NameService'

			// create and initialize the ORB
			this.orb = ORB.init(url, null);

			// get the root naming context
			org.omg.CORBA.Object objRef;
			objRef = orb.resolve_initial_references("NameService");

			// Use NamingContextExt instead of NamingContext. This is
			// part of the Interoperable naming Service.
			NamingContextExt ncRef = NamingContextExtHelper.narrow(objRef);
			dbImpl = LoginServerInterfaceHelper.narrow(ncRef.resolve_str(this.METHOD));

			return true;
			
		} catch (Exception e) {
			System.out.println("ERROR : " + e);
			return false;
		}
		
	}
	
	public RegisterLogin(int dbPort,String dbIP)
	{
		this.port=dbPort;
		this.ip= dbIP;
		this.url = new String[] { "-ORBInitialPort", Integer.toString(this.port), "-ORBInitialHost", this.ip };
		
	}
	
	public boolean register(UserData userData, String regData)
	{
		if(regData.isEmpty() || userData.userName.isEmpty() || userData.password.isEmpty())
			return false;
		
		return dbImpl.reg(userData, regData);
	}
	
	
	public LoginInformation login(UserData userData)
	{
		
		if(userData.userName.isEmpty() || userData.password.isEmpty()){
			return null;
		}
		
		if((loginInfo = dbImpl.login(userData))!=null){
			return loginInfo;
		}else{
			return null;
		}
		
	}
}

