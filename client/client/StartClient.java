package client;

/**
 *
 * @author imed
 */

import java.util.ArrayList;
import org.omg.CosNaming.*;
import org.omg.CORBA.*;
import VS2.*;

public class StartClient {
	
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
	
	private ConnectInformationData mYserver;//Server info IP und port
	ORB orb;
	private String[] url=null;// url um mit Corba serverzu verbinden
	private String METHOD = "DataServiceName1";//um mit den richtigen Service zu verbinden
	private boolean isAdmin=false;// admin rechte 

	

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
			
			return true;
			
		} catch (Exception e) {
			System.out.println("ERROR (falsche Daten): " +e);
//			System.exit(0);
			return false;
		}
	}
	
	
	
	
	/*
	 * 
	 * TODO warte auf DB dann loeschen
	 */
	public StartClient(String ip, int port,String uName, String pWord) {
			
			this.uName=uName;
			this.pWord=pWord;
		
			this.userData = new UserData(this.uid, this.uName, this.pWord,this.isAdmin);
			
			this.messageList = new ArrayList<MessageData>();
			this.childList =new ArrayList<String>();
			
			this.mYserver=new ConnectInformationData(ip,port);
			this.loginInfo=new LoginInformation(this.isAdmin,this.mYserver);
			this.url = new String[] { "-ORBInitialPort", Integer.toString(port), "-ORBInitialHost", ip };
			//this.url = new String[] { "-ORBInitialPort", Integer.toString(this.loginInfo.server.port), "-ORBInitialHost", this.loginInfo.server.ip };
			if(!this.connectToServer()){
			 System.out.println("Vllt falsche daten eingegeben");
			 System.exit(0);	
			}
	}

	public StartClient(LoginInformation loginInfo,UserData userData) {
		// TODO Auto-generated constructor stub
		this.messageList = new ArrayList<MessageData>();
		this.childList =new ArrayList<String>();
		
		this.loginInfo=loginInfo;
		this.userData = userData;
				
		this.url = new String[] { "-ORBInitialPort", Integer.toString(this.loginInfo.server.port), "-ORBInitialHost",this. loginInfo.server.ip };
		this.connectToServer();
	}

	public void setDBipUport(String ip,int port){
		this.ipDB=ip;
		this.portDB=port;
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
	/*
	 * GIbt die einzelnen  IP des Kind
	 */
	public String getChildIP(String childname){
		return this.mbImpl.connectToChild(childname).ip;
	}
	
	public int getChildPort(String childname){
		return this.mbImpl.connectToChild(childname).port;
	}
	
	/*
	 * Array von alle Nachrichten
	 * 
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
	public boolean setMessage(String newmessage, String messageID) {
		
		return this.mbImpl.setMessage(newmessage, messageID, this.userData);
	}
	
		
	

	/*
	 * loescht die Nachricht
	 * 
	 * @param uid
	 * 
	 * @param messageID
	 */
	public boolean deleteMessage( String messageID) {

		return this.mbImpl.deleteMessage(messageID, this.userData);
	}

	/*
	 * schreib eine neue Nachricht
	 * @param message
	 */
	public boolean schreibeMessage(String message) {
		return mbImpl.createNewMessage(message, this.userData);
	}

	/*
	 * gibt die direkt naechste Message
	 * 
	 */
	public MessageData getnextMessage() {
		return this.mbImpl.getPreviousMessage();
	}

	/*
	 * gibt die vorh�rige Message
	 */
	public MessageData getPreviousMessage() {
		return this.mbImpl.getPreviousMessage();
	}

	/*
	 * fragt den Server die FatherIP
	 */
	public String getFatherIP() {
		return mbImpl.connectToFather(this.userData).ip;
	}

	public int getFatherPort() {
		return mbImpl.connectToFather(this.userData).port;
	}
	
	/*
	 * MessageBoard hat fatherId-> abruf xml datei auf fathername
	 * 
	 */
	public String getFatherName() {
		return this.mbImpl.getFatherName();
	}

	/*
	 * Sendet Nachircht an alle Kinder
	 *@ param MessageData
	 *
	 *@param return boolean
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
	
	/*
	 * Sendet Nachircht an Vater
	 *@ param MessageData
	 *
	 *@param return boolean 
	 */
	public boolean  publishOnFather(MessageData tempMData) {
	
		if(this.sendChildsorFATHER("share",this.getFatherIP(), this.getFatherPort(), tempMData)){
			return true;
		}
		
		return false;
		
		
	}
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
		
		
	/*
	 * Funktion um die Nachrichten an Kinder zu senden
	 * @param MessageData tempData
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
	/*
	 * username abfragen
	 */
	public String getUser() {
		return this.userData.userName;
	}

	/*
	 * userID abfragen
	 */
	public int getUserID() {
		return this.uid;
	}

	/*
	 * disconnect from server
	 */
	public void disconnectToServer() {
		orb.destroy();
	}

}
