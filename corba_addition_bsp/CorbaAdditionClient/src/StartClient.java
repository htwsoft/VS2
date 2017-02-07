/**
 * Created by E.E on 30.10.2016.
 */
import AdditionApp.*;

import org.omg.CosNaming.*;
import org.omg.CosNaming.NamingContextPackage.*;
import org.omg.CORBA.*;
import java.io.*;
import java.util.*;

public class StartClient
{
    public static void main(String[] args)
    {
        try
        {
            ORB orb = ORB.init(args, null);
            org.omg.CORBA.Object objRef =   orb.resolve_initial_references("NameService");
            NamingContextExt ncRef = NamingContextExtHelper.narrow(objRef);
            Addition addobj = (Addition) AdditionHelper.narrow(ncRef.resolve_str("ABC"));

            Scanner c = new Scanner(System.in);
            System.out.println("Hallo, hier werden zwei Zahlen addiert:");
            for(;;)
            {
                System.out.println("Erste Zahl eingeben:");
                String aa = c.nextLine();
                System.out.println("Zweite Zahl eingeben:");
                String bb = c.nextLine();
                int a = Integer.parseInt(aa);
                int b = Integer.parseInt(bb);
                int r = addobj.add(a,b);
                System.out.println("Ergebnis : " + r);
                System.out.println("-----------------------------------");
            }
        }
        catch (Exception e) {
            System.out.println("Client Fehler: " + e);
            e.printStackTrace();
        }

    }

}