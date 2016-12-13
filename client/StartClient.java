package client;

/**
 *
 * @author imed
 */
import Empfang.*;


import org.omg.CosNaming.*;
import org.omg.CosNaming.NamingContextPackage.*;
import org.omg.CORBA.*;
import java.io.*;
import java.util.*;


class schreiben implements Runnable{
	private Thread t;
	private EmpfangApp messgOBJ;
	String benutzer;
	schreiben(EmpfangApp addobj,String benutzer){
		this.messgOBJ=addobj;
		this.benutzer=benutzer;
	}
	@Override
	public void run() {
		Scanner c = new Scanner(System.in);
		String aa = c.nextLine();
		String[] text;
		for(;;){
			System.out.println("Enter Text:");
			aa = c.nextLine();
			messgOBJ.send(aa);

			System.out.println("-----------------------------------");
			try {
				Thread.sleep(100);
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
	
		
	}

	   public void start () {
	      System.out.println("Starting Schreiben "+this.benutzer );
	      if (t == null) {
	         t = new Thread (this,this.benutzer);
	         t.start ();
	      }
	   }
	
}


public class StartClient {

	/**
	 * @param args
	 *            the command line arguments
	 */
	



	public static void main(String[] args) {
		try {
			
			String[] test =new String[]{"-ORBInitialPort","1050","-ORBInitialHost","localhost"};
			
			ORB orb = ORB.init(args, null);
			org.omg.CORBA.Object objRef = orb.resolve_initial_references("NameService");
		
			NamingContextExt ncRef = NamingContextExtHelper.narrow(objRef);
			EmpfangApp addobj = (EmpfangApp) EmpfangAppHelper.narrow(ncRef.resolve_str("Abteilung1"));
			
			
			Scanner c = new Scanner(System.in);
			System.out.println("Enter Bneutzername:");
			String aa = c.nextLine();
			addobj.benutzername(aa);
//			schreiben s1=new schreiben(addobj,aa);
//			lesen l1=new lesen(addobj,aa);
//			
//			s1.start();
//			l1.start();
			
			for(;;){
				System.out.println("Enter Text:");
				aa = c.nextLine();
				addobj.send(aa);
				String[] text;
				text = addobj.getSTringArray();
				System.out.println("-Nachrichten vom Server----------------------------------");
				for (int i = 0; i < text.length; i++) {
					System.out.println(text[i].toString());
				}
				System.out.println("-----------------------------------");
				try {
					Thread.sleep(100);
				} catch (InterruptedException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
			}
			

		} catch (Exception e) {
			System.out.println("Hello Client exception: " + e);
			e.printStackTrace();
		}

	}

}