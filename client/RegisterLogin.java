package client;

import org.omg.CosNaming.*;
import org.omg.CORBA.*;
import VS2.*;

public class RegisterLogin {
	
	private LoginServerInterface dbImpl;
	private LoginInformation loginInfo;
	private boolean angemeldet = true;//wenn db da ist auf false setzten
	
	public RegisterLogin()
	{
		dbImpl = LoginServerInterfaceHelper.narrow(ncRef.resolve_str(this.METHOD));
		angemeldet = false;
		
	}
	
	public boolean register(UserData userData, String regData)
	{
		if(regData.isEmpty() || userData.userName.isEmpty() || userData.password.isEmpty())
			return false;
		
		return dbImpl.reg(userData, regData);
	}
	
	
	public boolean login(UserData userData)
	{
		angemeldet = false;
		if(userData.userName.isEmpty() || userData.password.isEmpty())
			return false;
		
		loginInfo = dbImpl.login(userData);
		angemeldet = true;
		return true;
	}
}
