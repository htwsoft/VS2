package server;

import Empfang.*;
import org.omg.CosNaming.*;
import org.omg.CosNaming.NamingContextPackage.*;
import org.omg.CORBA.*;
import org.omg.PortableServer.*;
import org.omg.PortableServer.POA;

import java.util.ArrayList;
import java.util.Properties;

public class EmpfangObj extends EmpfangAppPOA
{
	public String benutzer;
	public String text;
	 ArrayList<String> objtext = new ArrayList<String>();
	 private ORB orb;

	public void setORB(ORB orb_val) {
		orb = orb_val;
	}


	@Override
	public void send(String a)
	{
		objtext.add(benutzer+": "+a);
		System.out.println(benutzer+": "+a);
		
	}

	@Override
	public void benutzername(String name)
	{
		this.benutzer=name;
		
	}


	@Override
	public String getstring() {
		// TODO Auto-generated method stub
		return this.benutzer+": "+this.text;
	}


	@Override
	public String[] getSTringArray() {
		String[] array = new String[objtext.size()];
		
		for (int i = 0; i < objtext.size(); i++) {
		    array[i] = objtext.get(i);
		}
		
		return array;
	}
}
