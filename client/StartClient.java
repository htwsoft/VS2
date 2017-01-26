/**
 *
 * @author imed
 */
import org.omg.CosNaming.*;
import org.omg.CosNaming.NamingContextPackage.*;
import org.omg.CORBA.*;



public class StartClient{
  /* 
   Aufruf:
     java HelloClient -ORBInitialPort 1050
          [-ORBInitialHost nameserverhost] [-shutdown] [-n name] [-val x y]
   Parameter:
     1050            wählbare Portnummer, die der ORB des Servers auf
                     Anforderungen abhört
     nameserverhost  Rechner auf dem der ORB-Dämon (orbd) läuft
     name            beliebige Zeichenkette als Vorname in der 'person'-Struktur
     x, y            2 ganze Zahlen, die addiert werden sollen
  */
  
  public static void main(String args[]){
    boolean shutdown = false;
    String name = "Moritz";
    int uid = 12345;
    
    String method = "DataServiceName1";  //registrierter Name der implementierten Methode

    try {
      // Initialisiere ORB und beschaffe Zugang zum 'NameService'
      // create and initialize the ORB
      ORB orb = ORB.init(args, null);

      // get the root naming context
      org.omg.CORBA.Object objRef = 
	  orb.resolve_initial_references("NameService");
	  
      // Use NamingContextExt instead of NamingContext. This is 
      // part of the Interoperable naming Service.  
      NamingContextExt ncRef = NamingContextExtHelper.narrow(objRef);
      ClientMessageboardInterface mbImpl = ClientMessageboardInterfaceHelper.narrow(ncRef.resolve_str(method));
      System.out.println("Obtained a handle on server object: " + method);
      //Aufruf der entfernten Methode
      MessageData msg = mbImpl.getNextMessage();
      System.out.println(msg.text + ", " + msg.id + ", " + msg.uid);
    } catch (Exception e) {
      System.out.println("ERROR : " + e) ;
      e.printStackTrace(System.out);
    }
  }
}
