/**
 * Created by E.E on 30.10.2016.
 */

import AdditionApp.*;
import org.omg.CosNaming.*;
import org.omg.CosNaming.NamingContextPackage.*;
import org.omg.CORBA.*;
import org.omg.PortableServer.*;
import org.omg.PortableServer.POA;
import java.util.Properties;

public class StartServer
{

    public static void main(String args[])
    {
        try
        {
            // ORB (Object Request Broker)  erstellen und init //// get reference to rootpoa &amp; activate the POAManager
            ORB orb = ORB.init(args, null);
            POA rootpoa = POAHelper.narrow(orb.resolve_initial_references("RootPOA")); //Portable Object Adapter
            rootpoa.the_POAManager().activate();

            // create servant and register it with the ORB
            AdditionObj addobj = new AdditionObj();
            addobj.setORB(orb);

            // get object reference from the servant
            org.omg.CORBA.Object ref = rootpoa.servant_to_reference(addobj);
            Addition href = AdditionHelper.narrow(ref);

            org.omg.CORBA.Object objRef =  orb.resolve_initial_references("NameService");
            NamingContextExt ncRef = NamingContextExtHelper.narrow(objRef);

            NameComponent path[] = ncRef.to_name( "ABC" );
            ncRef.rebind(path, href);

            System.out.println("Rechner-Server ready und wartet ...");

            // warte auf Anfragen vom Client
            for (;;)
            {
                orb.run();
            }
        }

        catch (Exception e)
        {
            System.err.println("Fehler: " + e);
            e.printStackTrace(System.out);
        }

        System.out.println("Server beendet ...");
    }
}