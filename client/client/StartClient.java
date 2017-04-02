package client;

/*
 *
 * @author Salvatore Simonte
 */

import java.util.ArrayList;
import org.omg.CosNaming.*;
import org.omg.CORBA.*;
import VS2.*;

import storageSystem.*;
import Datenbank.dbInfo.Fkt;
public class StartClient {
	// um die DB sagen welche funktion die nachricht nicht senden konnte
	
	
	private ArrayList<String> childsNames=new ArrayList<String>();
	private int uid = 12345;// TEST UID
	private String uName=null;//usaername
	private String pWord=null;//password
	private UserData userData=null;//Klasse um User Daten zu speichern
	
	private LoginInformation loginInfo=null; //Loginfo von Server und rechte
	private MessageboardServerInterface mbImpl=null;//Corba
	boolean shutdown=false;
	
	private ArrayList<MessageData> messageList=null;//Array die ganzen Messages um an den Client zu zeigen
	private ArrayList<String> childList=null;//Kinder Liste von dem Board an dem ich Angemeldet bin

	private int portDB=6050; // Bitte den richtigen port eingeben und der muss am besten immer gleich sein
	private String ipDB="192.168.2.1";
	private StorageMessages db;
	checkDB dbsend;
	
	private ConnectInformationData mYserver;//Server info IP und port
	ORB orb;
	private String[] url=null;// url um mit Corba serverzu verbinden
	private String METHOD = "DataServiceName1";//um mit den richtigen Service zu verbinden
	private boolean isAdmin=false;// admin rechte 

	
	/**
	 * Verbindet mit den uebergebenen Infos mit der DB
	 */
	private boolean connectToServer() {
		try {
			
			
			// Initialisiere ORB und beschaffe Zugang zum 'NameService'
			 // create and initialize the ORB
			this.orb = ORB.init(this.url, null);
			// get the root naming context
			org.omg.CORBA.Object objRef;
			objRef = orb.resolve_initial_references("NameService");
			// Use NamingContextExt instead of NamingContext. This is
			// part of the Interoperable naming Service.
			NamingContextExt ncRef = NamingContextExtHelper.narrow(objRef);
			mbImpl = MessageboardServerInterfaceHelper.narrow(ncRef.resolve_str(this.METHOD));
			mbImpl._non_existent();//testen ob Server erreichbar ist
			return true;
			
		} catch (Exception e) {
			System.out.println("ERROR Server nicht Erreichbar ");
			System.exit(0);
			return false;
		}
	}
		
	/**
	 * Starten der Klasse informationen Verarbeitet um mit Corba server zu verbinden
	 * @param loginInfo
	 * @param userData
	 */
	public StartClient(LoginInformation loginInfo,UserData userData) {
		this.db=new StorageMessages();
		
		this.messageList = new ArrayList<MessageData>();
		this.childList =new ArrayList<String>();
		
		this.loginInfo=loginInfo;
		this.userData = userData;
				
		this.url = new String[] { "-ORBInitialPort", Integer.toString(this.loginInfo.server.port), "-ORBInitialHost",this. loginInfo.server.ip };
		this.connectToServer();
		this.dbsend= new checkDB(this,this.db,loginInfo.server.ip);
		new Thread(dbsend).start();
		
	}
	/**
	 * port ersetzten
	 * @param ip
	 * @param port
	 */
	public void setDBipUport(String ip,int port){
		this.ipDB=ip;
		this.portDB=port;
	}

	/**
	 * abrufen von den KindsServer Name
	 * @return ArrayList<String>
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
	/**
	 * Gibt die einzelnen  IP des Kind
	 * @param childname
	 * @return
	 */
	public String getChildIP(String childname){
		return this.mbImpl.connectToChild(childname).ip;
	}
	
	/**
	 * GIbt die einzelnen Portdes Kind
	 * @param childname
	 * @return
	 */
	public int getChildPort(String childname){
		return this.mbImpl.connectToChild(childname).port;
	}
	
	/**
	 * Array von alle Nachrichten
	 * @return ArrayList<MessageData>
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
	

	/**
	 * ersetzt die Nachricht
	 * @param newmessage
	 * @param messageID
	 * @return
	 */
	public boolean setMessagefuerThread(String newmessage, String messageID) {	
		try{
			this.mbImpl.setMessage(newmessage, messageID, this.userData);
				return true;		
		}catch(Exception e){
			return false;
		}
	}
	public boolean setMessage(String newmessage, String messageID) {	
		try{
			if(this.mbImpl.setMessage(newmessage, messageID, this.userData)){
				return true;
		}else{
			this.db.writeEintrag(messageID,this.userData.userID,this.userData.userName,this.userData.password, this.loginInfo.server.ip, this.userData.isAdmin, false,newmessage ,Fkt.ERSETZTEN);
			
			return false;
		}
		}catch(Exception e){
			this.db.writeEintrag(messageID,this.userData.userID,this.userData.userName,this.userData.password, this.loginInfo.server.ip, this.userData.isAdmin, false, newmessage ,Fkt.ERSETZTEN);
			
			System.out.println("Server nicht Erreichbar ");
			System.exit(0);
			return false;
		}
	}
	
	/**
	 * loescht die Nachricht
	 * @param messageID
	 * @return boolean
	 */
	public boolean deleteMessagefuerThread( String messageID){
		try{
			this.mbImpl.deleteMessage(messageID, this.userData);
				return true;
		
		}catch(Exception e){
			return false;
		}
	}
	public boolean deleteMessage( String messageID) {
		try{
			if(this.mbImpl.deleteMessage(messageID, this.userData)){
				return true;
		}else{
			this.db.writeEintrag(messageID,this.userData.userID,this.userData.userName,this.userData.password, this.loginInfo.server.ip, this.userData.isAdmin, false,"xxx" ,Fkt.LOESCHEN);
			
			return false;
		}
		}catch(Exception e){
			this.db.writeEintrag(messageID,this.userData.userID,this.userData.userName,this.userData.password, this.loginInfo.server.ip, this.userData.isAdmin, false, "xxx" ,Fkt.LOESCHEN);
			
			System.out.println("Server nicht Erreichbar ");
			System.exit(0);
			return false;
		}
	}
	/**
	 * schreib eine neue Nachricht
	 * @param message
	 * @return boolean
	 */
	public boolean schreibeMessageFuerThread(String message) {
			return mbImpl.createNewMessage(message, this.userData);	
	}

	public boolean schreibeMessage(String message) {
		try{
		if(mbImpl.createNewMessage(message, this.userData)){
			return true;
		}else{
			this.db.writeEintrag("xxx",this.userData.userID,this.userData.userName,this.userData.password, this.loginInfo.server.ip, this.userData.isAdmin, false, message,Fkt.SCHREIBEN);
			
			return false;
		}
		}catch(Exception e){
			this.db.writeEintrag("xxx",this.userData.userID,this.userData.userName,this.userData.password, this.loginInfo.server.ip, this.userData.isAdmin, false, message,Fkt.SCHREIBEN);
			
			System.out.println("ERROR Server nicht Erreichbar ");
			System.exit(0);
			return false;
		}
	}

	/**
	 * gibt die direkt naechste Message
	 * @return MessageData
	 */
	public MessageData getnextMessage() {
		return this.mbImpl.getPreviousMessage();
	}

	/**
	 * gibt die vorhaerige Message
	 * @return MessageData
	 */
	public MessageData getPreviousMessage() {
		return this.mbImpl.getPreviousMessage();
	}

	/**
	 * fragt den Server die FatherIP
	 * @return FahterIP
	 */
	public String getFatherIP() {
		return mbImpl.connectToFather(this.userData).ip;
	}
	/**
	 * fragt den Server den FatherPort
	 * @return FahterPort
	 */
	public int getFatherPort() {
		return mbImpl.connectToFather(this.userData).port;
	}
	
	/**
	 * MessageBoard hat fatherId-> abruf xml datei auf fathername
	 * @return name
	 */
	public String getFatherName() {
		return this.mbImpl.getFatherName();
	}

	/**
	 * Sendet Nachircht an alle Kinder
	 * @param tempMData
	 * @return boolean
	 */
	public boolean publishOnChilds(MessageData tempMData){
		this.childsNames=this.getChildNames();
		if(childsNames!=null){
			for(int i=0;i<this.childsNames.size();++i){
				if (!this.sendChildsorFATHER("share",this.mbImpl.connectToChild(this.childsNames.get(i)).ip, this.mbImpl.connectToChild(this.childsNames.get(i)).port, tempMData)){
					return false;
				}
			}
		}else{
			return false;
		}
		return true;
	}
	
	/**
	 * Sendet Nachircht an Vater
	 * @param tempMData
	 * @return boolean
	 */
	public boolean  publishOnFather(MessageData tempMData) {
	
		if(this.sendChildsorFATHER("share",this.getFatherIP(), this.getFatherPort(), tempMData)){
			return true;
		}
		
		return false;
		
		
	}
	/**
	 * Die Nachricht die geaendert wurde an alle childs Senden nur admin. wird vom server gepruft
	 */
	public boolean setMessageChild(MessageData tempMData) {
		this.childsNames=this.getChildNames();
		if(childsNames!=null){
			for(int i=0;i<this.childsNames.size();++i){
				if (!this.sendChildsorFATHER("set",this.mbImpl.connectToChild(this.childsNames.get(i)).ip, this.mbImpl.connectToChild(this.childsNames.get(i)).port, tempMData)){
					return false;
				}
			}
		}else{
			return false;
		}
		return true;	
	}
		
	/**
	 *  Funktion um die Nachrichten an Kinder zu senden
	 * @param welchefkt
	 * @param toIP
	 * @param toPort
	 * @param tempMData
	 * @return
	 */
	private boolean sendChildsorFATHER(String welchefkt,String toIP, int toPort, MessageData tempMData) {

		if (toPort != 0) {
			// Connect mit der neue IP port
			this.url = new String[] { "-ORBInitialPort", Integer.toString(toPort), "-ORBInitialHost", toIP };
			this.disconnectToServer();

			if (this.connectToServer()) {
				if(welchefkt.equals("share")){
					this.mbImpl.saveMessage(tempMData.text, tempMData.id, this.userData);
				}
				if(welchefkt.equals("set")){
					this.mbImpl.setMessage(tempMData.text, tempMData.id, this.userData);
				}

			} else {
				System.err.println("Irgenwas stimmt nicht");
				return false;
			}

			// connect mit den momentanen Verbundenen Server
			this.url = new String[] { "-ORBInitialPort", Integer.toString(this.loginInfo.server.port),
					"-ORBInitialHost", this.loginInfo.server.ip };

			this.disconnectToServer();
			if (this.connectToServer()) {
				return true;
			}
		}

		return false;

	}
	/**
	 * username abfragen
	 * @return
	 */
	public String getUser() {
		return this.userData.userName;
	}

	/**
	 * userID abfragen
	 * @return
	 */
	public int getUserID() {
		return this.uid;
	}

	/**
	 *  disconnect from server
	 */
	public void disconnectToServer() {
		orb.destroy();
	}

}
