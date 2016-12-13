package server;
    /**
     *
     * @author imed
     */
    import Empfang.*;
     
    import org.omg.CosNaming.*;
    import org.omg.CosNaming.NamingContextPackage.*;
    import org.omg.CORBA.*;
    import org.omg.PortableServer.*;
    import org.omg.PortableServer.POA;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.Inet4Address;
import java.net.InetAddress;
import java.net.MalformedURLException;
import java.net.NetworkInterface;
import java.net.URL;
import java.util.Enumeration;
import java.util.Properties;
     
    public class StartServer {


private static void getPublicIpAddress() {
	
        URL ipAdress;

        try {
            ipAdress = new URL("http://myexternalip.com/raw");

            BufferedReader in = new BufferedReader(new InputStreamReader(ipAdress.openStream()));

            String ip = in.readLine();
            System.out.println(ip);
        } catch (MalformedURLException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }
    
}


      public static void main(String args[]) {
        try{
          // create and initialize the ORB //// get reference to rootpoa &amp; activate the POAManager
          ORB orb = ORB.init(args, null);      
          POA rootpoa = POAHelper.narrow(orb.resolve_initial_references("RootPOA"));
          rootpoa.the_POAManager().activate();
     
          // create servant and register it with the ORB
          EmpfangObj addobj = new  EmpfangObj();
          addobj.setORB(orb); 
     
          // get object reference from the servant
          org.omg.CORBA.Object ref = rootpoa.servant_to_reference(addobj);
          EmpfangApp href = EmpfangAppHelper.narrow(ref);
     
          org.omg.CORBA.Object objRef =  orb.resolve_initial_references("NameService");
          NamingContextExt ncRef = NamingContextExtHelper.narrow(objRef);
     
          NameComponent path[] = ncRef.to_name( "Abteilung1" );
          ncRef.rebind(path, href);
     
          System.out.println(" Server ready and waiting ...\n");
         System.out.println("My ip "+InetAddress.getLocalHost().getHostAddress());
         getPublicIpAddress();
          
          
          // wait for invocations from clients
//          for (;;){
    	  orb.run();

    	 
//          }
        } 
     
          catch (Exception e) {
            System.err.println("ERROR: " + e);
            e.printStackTrace(System.out);
          }
     
          System.out.println("HelloServer Exiting ...");
     
      }
    }