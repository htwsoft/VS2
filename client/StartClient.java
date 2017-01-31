/**
 *
 * @author imed
 */

import java.util.ArrayList;
import org.omg.CosNaming.*;
import org.omg.CosNaming.NamingContextPackage.*;

import java.util.Scanner;

import org.omg.CORBA.*;
import org.omg.CORBA.ORBPackage.InvalidName;
/*
class LesenThread implements Runnable
{
	private Thread t;
	private ClientMessageboardInterface mbImpl;
	MessageData msg;
	LesenThread(ClientMessageboardInterface mbImpl){
		this.mbImpl = mbImpl;
	}
	//FÜR DIE GUI????
	
	@Override
	public void run() {
		
		while(true)
		{
			System.out.println("Obtained a handle on server object: " );
			//Aufruf der entfernten Methode
			msg = mbImpl.getNextMessage();
			System.out.println(msg.text + ", " + msg.id + ", " + msg.uid);
			try {
				Thread.sleep(2000);
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
	}
	   public void start () {
	      System.out.println("Starting lesen ");
	      if (t == null) {
	         t = new Thread (this);
	         t.start ();
	      }
	   }
	
}*/

public class StartClient {

	private String uName;
	private int uid = 12345;
	private String message;
	public MessageData msg;
	private ClientMessageboardInterface mbImpl;
	boolean shutdown;
	ArrayList<MessageData> messageList;
	
	public StartClient() {
		this.messageList = new ArrayList<MessageData>();
		

		String[] url = new String[] { "-ORBInitialPort", "6000", "-ORBInitialHost", "127.0.0.1" };

		String method = "DataServiceName1"; // registrierter Name der
											// implementierten Methode

		try {
			// Initialisiere ORB und beschaffe Zugang zum 'NameService'
			// create and initialize the ORB
			ORB orb = ORB.init(url, null);

			// get the root naming context
			org.omg.CORBA.Object objRef;

			objRef = orb.resolve_initial_references("NameService");

			// Use NamingContextExt instead of NamingContext. This is
			// part of the Interoperable naming Service.
			NamingContextExt ncRef = NamingContextExtHelper.narrow(objRef);

			mbImpl = ClientMessageboardInterfaceHelper.narrow(ncRef.resolve_str(method));
		} catch (Exception e) {
			System.out.println("ERROR : " + e);
			System.exit(0);
		}
	}

	public boolean setMessage(String message, int uid, String uName) {

		return this.mbImpl.setMessage(message, uid, uName);

	}

	public MessageData getPreviousMessage() {

		return this.mbImpl.getPreviousMessage();
	}

	public boolean deleteMessage(int uid, String messageID) {
		int arrayPosAlt=0;
		ArrayList<MessageData> messageListneu = new ArrayList<MessageData>();
		MessageData[] tempArray = mbImpl.getMessages();
		
		if(!this.mbImpl.deleteMessage(uid, messageID)){
			for(int a=0;a<messageList.size();a++){
				if(messageList.get(a).id.equals(messageID)){
					if(messageList.get(a).uid==uid){
						
						for (int y = 0; y < tempArray.length; y++) {
							
							if((tempArray[y].uid==messageList.get(a).uid)||(tempArray[y].text.equals(messageList.get(a).text))||(tempArray[y].uName.equals(messageList.get(a).uName))){
								return this.mbImpl.deleteMessage(tempArray[y].uid, tempArray[y].id);
							}
						}
						
					}
				}
			}
			
		}

		return this.mbImpl.deleteMessage(uid, messageID);
	}

	public ArrayList<MessageData> getMessage() {
		messageList.clear();
		MessageData[] tempArray = mbImpl.getMessages();

		for (int y = 0; y < tempArray.length; y++) {
			messageList.add(tempArray[y]);
		}

		return messageList;

	}

	public boolean schreibeMessage(String message) {
		return mbImpl.createNewMessage(message, this.uid, this.uName);
	}

	public void writeUser(String user) {
		this.uName = user;
	}

	public String getUser() {

		return this.uName;
	}

	private MessageData[] getMessageList() {
		return mbImpl.getMessages();

	}

	public static void main(String args[]) {
		ArrayList<MessageData> messageListtest = new ArrayList<MessageData>();
		
		boolean shutdown = false;
		String messagea;
        String messageID;
		String bName;
        MessageData msgData;
		int loeschuid;
		StartClient test = new StartClient();
		Scanner scan = new Scanner(System.in);
		System.out.println("Username:");
		String username = scan.nextLine();

		test.writeUser(username);
		int i;
		boolean beenden=false;
		
		while (!beenden) {
			System.out.println("\n Was möchten Sie machen?"
					+ "\nBeenden:0 " 
					+ "\nNachricht schreiben :1" 
						+ "\nNachricht löschen 2:"
					+ "\nNachricht ersetzen: 3" 
						+ "\nNachricht Ausgabe: 4 " + "\n -----> ");
			i = scan.nextInt();
			switch (i) {
			case 1:
				
				System.out.println("Message:");
				Scanner scan1 = new Scanner(System.in);
				 messagea = scan1.nextLine();
				 
				test.schreibeMessage(messagea);
				break;

			case 2:
				System.out.println("Loeschen (geht noch nicht muss noch angepasst werden ):");
				System.out.println("UID:");
				loeschuid = scan.nextInt();
				System.out.println("ID:");
				scan = new Scanner(System.in);
               			messageID = scan.nextLine();
                
				if(!test.deleteMessage(loeschuid, messageID)){
					System.out.println("UID: "+loeschuid+" und/oder "
							+ "ID: "+messageID+ " sind falsch ");
				}
				break;

			case 3:
				System.out.println("Ersetzen : \n ");
				System.out.println("Message : ");
				Scanner scan11 = new Scanner(System.in);
				messagea = scan11.nextLine();
				System.out.println("UserName : \n ");
				scan = new Scanner(System.in);
				bName = scan.nextLine();
				System.out.println("UID : \n ");
				scan = new Scanner(System.in);
				loeschuid = scan.nextInt();
				
				if(!test.setMessage(messagea, loeschuid, bName)){
					System.out.println("UID: "+loeschuid+" und/oder "
							+ "Massage: "+messagea
							+ " Bname: bName"
							+ " sind falsch ");
				}
				break;
			case 4:
				
				System.out.println("\n Ausgabe von alle Message auf server:\n");
				messageListtest=test.getMessage();
				for(int y=0;y<messageListtest.size();y++){
					System.out.println("TEXT:"+messageListtest.get(y).text+
							" -BNAME:"+messageListtest.get(y).uName+
							" -UID:"+messageListtest.get(y).uid+
							" -ID:"+messageListtest.get(y).id);
				}
				break;
				
			case 0:
				System.out.println("Beendet");
				beenden=true;
				break;
			default:
				System.out.println("bitte gib eine richtige Eingabe!\n");
				break;

			}

		}

	}
}
