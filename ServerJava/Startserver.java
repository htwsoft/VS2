package ServerJava;

import org.omg.CORBA.ORB;
import org.omg.CosNaming.NameComponent;
import org.omg.CosNaming.NamingContextExt;
import org.omg.CosNaming.NamingContextExtHelper;
import org.omg.PortableServer.POA;
import org.omg.PortableServer.POAHelper;
import VS2idl.*;
public class Startserver {
	
	 public static void main(String args[]) {
	        try{
	        	String[] url = new String[]{"-ORBInitialPort","1050","-ORBInitialHost","localhost"};
	    		
	          // create and initialize the ORB //// get reference to rootpoa &amp; activate the POAManager
	          ORB orb = ORB.init(url, null);      
	          POA rootpoa = POAHelper.narrow(orb.resolve_initial_references("RootPOA"));
	          rootpoa.the_POAManager().activate();
	     
	          // create servant and register it with the ORB
	          messageObj messageObj = new messageObj();
	         // messageObj.setORB(orb); 
	     
	          // get object reference from the servant
	          org.omg.CORBA.Object ref = rootpoa.servant_to_reference( messageObj);
	          ClientMessageboardInterface  href = ClientMessageboardInterfaceHelper.narrow(ref);
	     
	          org.omg.CORBA.Object objRef =  orb.resolve_initial_references("NameService");
	          NamingContextExt ncRef = NamingContextExtHelper.narrow(objRef);
	     
	          NameComponent path[] = ncRef.to_name( "DataServiceName1" );
	          ncRef.rebind(path, href);
	     
	          System.out.println("Java Message Server ready and waiting ...");
	     
	          // wait for invocations from clients
	          for (;;){
	    	  orb.run();
	          }
	        } 
	     
	          catch (Exception e) {
	            System.err.println("ERROR: " + e);
	            e.printStackTrace(System.out);
	          }
	     
	          System.out.println("HelloServer Exiting ...");
	     
	      }

}
