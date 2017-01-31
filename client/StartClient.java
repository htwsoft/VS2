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


public class StartClient {
	private String pWord;
	private String uName;
	private int uid = 12345;
	private String message;
	private String fatherName;
	
	public MessageData msg;
	private ClientMessageboardInterface mbImpl;
	boolean shutdown;
	
	
	ArrayList<MessageData> messageList;
	
	ORB orb;
	private String[] url ;
	private String METHOD = "DataServiceName1"; 
	private void connectToServer(){
		try {
			// Initialisiere ORB und beschaffe Zugang zum 'NameService'
		
		// create and initialize the ORB
			this.orb = ORB.init(url, null);

			// get the root naming context
			org.omg.CORBA.Object objRef;

			objRef = orb.resolve_initial_references("NameService");
			
			// Use NamingContextExt instead of NamingContext. This is
			// part of the Interoperable naming Service.
			NamingContextExt ncRef = NamingContextExtHelper.narrow(objRef);

			mbImpl = ClientMessageboardInterfaceHelper.narrow(ncRef.resolve_str(this.METHOD));
			
			
			
		} catch (Exception e) {
			System.out.println("ERROR : " + e);
			System.exit(0);
		}
	}
	public StartClient(String ip,int port) {
		System.out.println(ip+port);
		this.messageList = new ArrayList<MessageData>();
		this.url = new String[] { "-ORBInitialPort", Integer.toString(port), "-ORBInitialHost", ip };
		this.connectToServer();
	}
	public StartClient(String[] url) {
		
		this.messageList = new ArrayList<MessageData>();
		//this.url = new String[] { "-ORBInitialPort", Integer.toString(port), "-ORBInitialHost", ip };
		this.url=url;
		this.connectToServer();
	}
	
	/*
	 * MessageBoard hat fatherId-> abruf xml datei auf fathername
	 */
	public String getFatherName(){
		return this.mbImpl.getFatherName();	
	}
	
	/*
	 *abrufen von den KindsServer Name
	 */
	public String[] getChildNames(){
		return this.mbImpl.getChildNames();
	}
	
	/*
	 * Array von alle Nachrichten 
	 */
	public ArrayList<MessageData> getMessage() {
		messageList.clear();
		MessageData[] tempArray = mbImpl.getMessages();
		if(!tempArray.equals(null)){
			for (int y = 0; y < tempArray.length; y++) {
			messageList.add(tempArray[y]);
			}
		}
		return messageList;
	}

	/*
	 * ersetzt die Nachricht 
	 */
	public boolean setMessage(String newmessage,String messageID, int uid, String uName) {

		return this.mbImpl.setMessage(message, messageID, uid,uName);

	}

	/*
	 * loescht die Nachricht
	 * @param uid
	 * @param messageID 
	 */
	public boolean deleteMessage(int uid, String messageID) {

		return this.mbImpl.deleteMessage(uid, messageID);
	}
	
	/*
	 * schreib eine neue Nachricht
	 */
	public boolean schreibeMessage(String message) {
		return mbImpl.createNewMessage(message, this.uid, this.uName);
	}
	
	/*
	 * gibt die direkt nächste Message
	 */
	public MessageData getnextMessage() {
		
		return this.mbImpl.getPreviousMessage();
	}
	
	/*
	 * gibt die vorhärige Message
	 */
	public MessageData getPreviousMessage() {
		return this.mbImpl.getPreviousMessage();
	}

	/*
	 * um mit dem Vater zu verbinden 
	 * Benutzte erst getFatherIp ud Port
	 * und dann start()
	 */
	public String getFatherIP(){
		return mbImpl.connectToFather().ip;
	}
	public int getFatherPort(){
		return mbImpl.connectToFather().port;
	}
	/*
	 * username schreiben 
	 */
	public void writeUser(String user) {
		this.uName = user;
	}
	
	public void writePassword(String pword) {
		this.pWord = pword;
	}

	public String getUser() {
		return this.uName;
	}

	public int getUserID() {
		return this.uid;
	}
	
	private void generateID(){
		
	}
	/*
	 * disconnect from server
	 */
	public void disconnectToServer(){
		
			orb.destroy();
		
	}
	
}
