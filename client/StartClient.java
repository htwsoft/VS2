
/**
 *
 * @author imed
 */

import java.util.ArrayList;
import org.omg.CosNaming.*;
import org.omg.CORBA.*;
import VS2.*;

public class StartClient {
	UserData userData;
	LoginInformation loginInfo;

	private int uid = 12345;
	private String message;
	private String fatherName;
	
	
	private MessageboardServerInterface mbImpl;
	private LoginServerInterface dbImpl;
	boolean shutdown;
	boolean angemeldet = true;//wenn db da ist auf false setzten
	private ArrayList<MessageData> messageList;
	private ArrayList<String> childList;

	ORB orb;
	private String[] url=null;
	private String METHOD = "DataServiceName1";

	private void connectToServer() {
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
			mbImpl = MessageboardServerInterfaceHelper.narrow(ncRef.resolve_str(this.METHOD));
//			dbImpl = LoginServerInterfaceHelper.narrow(ncRef.resolve_str(this.METHOD));

		} catch (Exception e) {
			System.out.println("ERROR : " + e);
			System.exit(0);
		}
	}
	public StartClient(String uName, String pWord){
		if(loginBenutzer(uName,pWord)){
			this.messageList = new ArrayList<MessageData>();
			this.childList =new ArrayList<String>();
			this.url = new String[] { "-ORBInitialPort", Integer.toString(this.loginInfo.server.port), "-ORBInitialHost", this.loginInfo.server.ip };
			this.connectToServer();
		}
		
	}
	/*
	 * 
	 * TODO warte auf DB dann loeschen
	 */
	public StartClient(String ip, int port) {
		
			this.messageList = new ArrayList<MessageData>();
			this.childList =new ArrayList<String>();
			this.url = new String[] { "-ORBInitialPort", Integer.toString(port), "-ORBInitialHost", ip };
			//this.url = new String[] { "-ORBInitialPort", Integer.toString(this.loginInfo.server.port), "-ORBInitialHost", this.loginInfo.server.ip };
			this.connectToServer();
		 

	}
	/*
	 * 
	 */
	public  StartClient(String[] url) {
	
			this.messageList = new ArrayList<MessageData>();
			// this.url = new String[] { "-ORBInitialPort",
			// Integer.toString(port),
			// "-ORBInitialHost", ip };
			this.url = url;
			this.connectToServer();
		
	}

	/*
	 * login wenn werte leer sind kommt false
	 */

	public boolean loginBenutzer(String uName, String pWord) {
		if (uName.isEmpty() || pWord.isEmpty()) {
			angemeldet = false;
			return false;
		} else {
			this.userData =new UserData(uName,pWord);
			loginDB();
			angemeldet = true;
			return true;
		}
	}

	/*
	 * TODO Datenbank implimentieren
	 */
	private void loginDB() {
//		this.loginInfo =new LoginInformation(this.dbImpl.login(userData).adminRights,this.dbImpl.login(userData).server);
		
	}

	/*
	 * abrufen von den KindsServer Name
	 */
	public ArrayList<String> getChildNames() {
		childList.clear();
		String[] tempArrayChilds = mbImpl.getChildNames();
		if (!tempArrayChilds .equals(null)) {
			for (int y = 0; y < tempArrayChilds .length; y++) {
				childList.add(tempArrayChilds [y]);
			}
		}
		return childList;	
	}
	
	public String getChildIP(String childname){
		return this.mbImpl.connectToChild(childname).ip;
	}
	
	public int getChildPort(String childname){
		return this.mbImpl.connectToChild(childname).port;
	}
	/*
	 * Array von alle Nachrichten
	 */
	public ArrayList<MessageData> getMessage() {
		messageList.clear();
		MessageData[] tempArray = mbImpl.getMessages();
		if (!tempArray.equals(null)) {
			for (int y = 0; y < tempArray.length; y++) {
				messageList.add(tempArray[y]);
			}
		}
		return messageList;
	}

	/*
	 * ersetzt die Nachricht
	 */
	public boolean setMessage(String newmessage, String messageID, int uid, String uName) {
		
		return this.mbImpl.setMessage(message, messageID, uid, uName);
	}

	/*
	 * loescht die Nachricht
	 * 
	 * @param uid
	 * 
	 * @param messageID
	 */
	public boolean deleteMessage(int uid, String messageID) {

		return this.mbImpl.deleteMessage(uid, messageID);
	}

	/*
	 * schreib eine neue Nachricht
	 * TODO
	 */
	public boolean schreibeMessage(String message) {
		return mbImpl.createNewMessage(message, this.uid, this.userData.userName);
	}

	/*
	 * gibt die direkt nächste Message
	 * TODO
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
	 * um mit dem Vater zu verbinden Benutzte erst getFatherIp ud Port und dann
	 * start()
	 */
	public String getFatherIP() {
		return mbImpl.connectToFather().ip;
	}

	public int getFatherPort() {
		return mbImpl.connectToFather().port;
	}
	
	/*
	 * MessageBoard hat fatherId-> abruf xml datei auf fathername
	 */
	public String getFatherName() {
		return this.mbImpl.getFatherName();
	}

	/*
	 *@ Para MessageData
	 *Sendet Nachircht an alle Kinder
	 *Return boolean
	 */
	public boolean iterateChilds(MessageData tempMData){
		return this.mbImpl.iterateChilds(tempMData.text,tempMData.id,tempMData.uid,tempMData.uName,this.loginInfo.adminRights);
	}
	
	/*
	 *@ Para MessageData
	 *Sendet Nachircht an Vater
	 *Return boolean 
	 */
	public boolean  publishOnFather(MessageData tempMData){
		return this.mbImpl.publishOnFather(tempMData.text, tempMData.id, tempMData.uid, tempMData.uName);
	}
	/*
	 * username abfragen
	 */
	public String getUser() {
		return this.userData.userName;
	}

	public int getUserID() {
		return generateID();
	}

	private int generateID() {
		return this.uid;

	}

	/*
	 * disconnect from server
	 */
	public void disconnectToServer() {
		orb.destroy();
	}

}
