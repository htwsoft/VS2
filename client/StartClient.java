/**
 *
 * @author imed
 */
import org.omg.CosNaming.*;
import org.omg.CosNaming.NamingContextPackage.*;

//import VS2idl.MessageData;

import java.util.Scanner;

import org.omg.CORBA.*;

class LesenThread implements Runnable {
	private Thread t;
	private ClientMessageboardInterface mbImpl;

	LesenThread(ClientMessageboardInterface mbImpl) {
		this.mbImpl = mbImpl;
	}

	@Override
	public void run() {
		MessageData msg;

		while (true) {
			// System.out.println("Obtained a handle on server object: " +
			// method);
			// Aufruf der entfernten Methode
			msg = mbImpl.getNextMessage();
			System.out.println(msg.text + ", " + msg.id + ", " + msg.uid);
		}
	}

	public void start() {
		System.out.println("Starting lesen ");
		if (t == null) {
			t = new Thread(this);
			t.start();
		}
	}

}

public class StartClient {

	private String uName;
	private int uid = 12345;
	private String message;
	public MessageData msg;
	public ClientMessageboardInterface mbImpl;
	boolean shutdown;

	public StartClient() {
		String[] url = new String[] { "-ORBInitialPort", "1050", "-ORBInitialHost", "127.0.0.1" };

		String method = "DataServiceName1"; // registrierter Name der
											// implementierten Methode

		try {
			// Initialisiere ORB und beschaffe Zugang zum 'NameService'
			// create and initialize the ORB
			ORB orb = ORB.init(url, null);

			// get the root naming context
			org.omg.CORBA.Object objRef = orb.resolve_initial_references("NameService");
			// Use NamingContextExt instead of NamingContext. This is
			// part of the Interoperable naming Service.
			NamingContextExt ncRef = NamingContextExtHelper.narrow(objRef);
			mbImpl = ClientMessageboardInterfaceHelper.narrow(ncRef.resolve_str(method));

		} catch (Exception e) {
			System.out.println("ERROR : " + e);
			e.printStackTrace(System.out);
		}
	}

	public void writeUser(String user) {
		this.uName = user;
	}

	public String getUser() {
		// TODO Auto-generated method stub
		return this.uName;
	}

	public MessageData getPreviousMessage() {

		return this.mbImpl.getPreviousMessage();
	}

	public MessageData getNextMessage() {

		return this.mbImpl.getNextMessage();
	}

	public boolean deleteMessage(int uid) {

		return this.mbImpl.deleteMessage(uid);
	}

	public boolean schreibeMessage(String message) {
		System.out.println(message+this.uid+this.uName);
		return mbImpl.createNewMessage(message, this.uid, this.uName);
	}

	public boolean setMessage(String message, int uid, String uName){
		
		return this.mbImpl.setMessage(message, uid, uName);
		
	}
	public static void main(String args[]) {

		StartClient test = new StartClient();

		System.out.println(test.mbImpl.getNextMessage().text);

		Scanner scan = new Scanner(System.in);
		System.out.println("Username:");
		test.uName = scan.nextLine();

		while (true) {
			System.out.println("\n \n\n ");
			System.out.println("Message:");
			String messagea = scan.nextLine();
			test.schreibeMessage(messagea);
			System.out.println("\n \n\n Ausgabe von alle Message auf server:");

			System.out.println(
					test.getNextMessage().text + " " + test.getNextMessage().uid + " " + test.getNextMessage().uName);

		}

	}
}
