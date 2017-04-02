import java.util.ArrayList;
import java.util.Scanner;
import VS2.*;
import client.*;

public class Dialog{

	String benutzterName = null;
	String passWord = null;
	String dbIP = null;
	int dbPORT = 0;

	boolean serverConnect = false;
	boolean shutdown = false;

	LoginInformation logininfo = null;
	UserData userDATA = null;
	RegisterLogin dbLogin;
	StartClient clientTest;

	Scanner scan;

	private boolean connDatenB() {
		// Login Daten eigben
		System.out.println("Datenb Daten eigben \n" + "IP: ");
		scan = new Scanner(System.in);
		dbIP = scan.nextLine();

		System.out.println("Port: ");
		scan = new Scanner(System.in);
		dbPORT = scan.nextInt();

		// Login klasse starten
		dbLogin = new RegisterLogin(dbPORT, dbIP);
		// login Datenbank verbinden
		if (!dbLogin.connectLoginServer()) {
			serverConnect = false;
			return false;
			
		}
		serverConnect = true;
		return true;

	}

	private boolean loginDB() {
		System.out.println("Bitte Login Daten eingben:\n" + "Benutzer: ");
		scan = new Scanner(System.in);
		benutzterName = scan.nextLine();

		System.out.println("Password: ");
		scan = new Scanner(System.in);
		passWord = scan.nextLine();
		userDATA = new UserData();
        userDATA.userID = 0;
        userDATA.userName = benutzterName;
        userDATA.password = passWord;
		this.logininfo = dbLogin.login(this.userDATA);

		if (!benutzterName.isEmpty() && !passWord.isEmpty()) {

			if (logininfo != null && this.serverConnect) {
				return true;
			} else {
				return false;
			}
		} else {
			return false;
		}

	}

	private boolean registerDB() {
		System.out.println("Bitte Login Daten eingben:\n" + "Benutzer: ");
		scan = new Scanner(System.in);
		benutzterName = scan.nextLine();

		System.out.println("Password: ");
		scan = new Scanner(System.in);
		passWord = scan.nextLine();
		userDATA = new UserData();
        userDATA.userID = 0;
        userDATA.userName = benutzterName;
        userDATA.password = passWord;
		// was macht regData
		String regData = "TEST";
		if (!benutzterName.isEmpty() && !passWord.isEmpty()) {
			if (dbLogin.register(this.userDATA, regData) && this.serverConnect) {
				this.logininfo = dbLogin.login(this.userDATA);
				return true;
			} else {
				return false;
			}
		} else {
			return false;
		}
	}

	public static void main(String args[]) {
		
		ArrayList<MessageData> messageListtest = new ArrayList<MessageData>();
		//Daten fuer Loginserver zu ersetzten
		ArrayList<UserData> userArray=new ArrayList<UserData>();
		
		UserData user1=new UserData(1001,"Salva","pw",true);
		UserData user2=new UserData(1002,"Patzek","pw",false);
		UserData user3=new UserData(1005,"Marco","pw",true);
		UserData user4=new UserData(1002,"Sadri","pw",false);
		
		userArray.add(user1);
		userArray.add(user2);
		userArray.add(user3);
		userArray.add(user4);
		
		int userPos=-1;
		int auswahl=0;
		
		//server IP und Port
		ConnectInformationData serDaten1=new ConnectInformationData("192.168.178.52",6000);
		ConnectInformationData serDaten2=new ConnectInformationData("10.9.41.177",6000);
		
		LoginInformation loginInfo=null;
			
		String messagea;
		String messageID;
		String bName;
		MessageData msgData;
		int loeschuid;

		Dialog dialog = new Dialog();

		Scanner scanMain = new Scanner(System.in);
		/*
		if (dialog.connDatenB()) {
			int entsch = 0;
			boolean erfolg = true;
			do {
				System.out.println("Anmelden 0\n" + "Regist 1: ");

				entsch = scanMain.nextInt();
				switch (entsch) {
				case 0:
					if (!dialog.loginDB()) {
						erfolg = false;
					}
					break;
				case 1:
					if (!dialog.registerDB()) {
						erfolg = false;
					}
					break;
				default:
					System.out.println("Waehle was!\n");
					erfolg = false;

					break;
				}
			} while (erfolg);
		}

		if (dialog.logininfo != null) {
			dialog.clientTest = new StartClient(dialog.logininfo);
		}
	*/
		String bWord=null;
		String bbName =null;
		do{
			
			scanMain = new Scanner(System.in);
			System.out.println("UserName : \n ");
			bbName = scanMain.nextLine();
			
			scanMain = new Scanner(System.in);
			System.out.println("Password : \n ");		
			bWord = scanMain.nextLine();
			
			for(int j =0;j< userArray.size();++j){
				if((userArray.get(j).userName.equals(bbName))&&(userArray.get(j).password.equals(bWord))){
					userPos=j;				
				}
			}
			if(userPos==-1){
				System.out.println(bbName+" existiert nicht oder falsch eingegeben!");
			}
		}while(userPos==-1);
		
		
		do{
			
			System.out.println("Mit welchen Server moechten sie verbinden\n");
			System.out.println("IP "+serDaten1.ip+"  Port"+serDaten1.port+" - 0\n");
			System.out.println("IP "+serDaten2.ip+"  Port"+serDaten2.port+" - 1 ->");
			
			scanMain = new Scanner(System.in);
			auswahl = scanMain.nextInt();
			
			
		}while(auswahl<0||auswahl>1);
		
		if(auswahl==0){
			loginInfo=new LoginInformation (userArray.get(userPos).isAdmin,serDaten1);
		}else if(auswahl ==1){
			loginInfo=new LoginInformation (userArray.get(userPos).isAdmin,serDaten2);
		}
		
		System.out.println("Sie werden mit dem Server "+loginInfo.server.ip+" mit Port "+loginInfo.server.port+" verbunden!\n");
		
		dialog.clientTest=new StartClient(loginInfo,userArray.get(userPos));
		
		int i;
		boolean beenden = false;

		while (!beenden) {
			System.out.println("\n Was moechten Sie machen?" + "\nBeenden: 0 " + "\nNachricht schreiben: 1"
					+ "\nNachricht loeschen: 2" + "\nNachricht ersetzen: 3" + "\nNachricht Ausgabe: 4"
					+ "\nServer wechseln: 5 (automatisch): " + "\nGebe Vater und kinder Infos: 6" + 
					"\nNachricht wird zum Vater gesendet: 7"+" \nNachricht an Kinder senden: 8 "+"\nGeanderte Nachricht an alle Childs weiter senden 9  -----> ");
			scanMain = new Scanner(System.in);
			i = scanMain.nextInt();
			
			switch (i) {
			case 1:

				System.out.println("Gib deine Nachricht ein:");
				scanMain = new Scanner(System.in);
				messagea = scanMain.nextLine();

				System.out.println(dialog.clientTest.schreibeMessage(messagea));
				
				break;

			case 2:
				
				System.out.println("Loeschen einer Nachricht:");
				System.out.println("ID:");
				scanMain = new Scanner(System.in);
				messageID = scanMain.nextLine();

				if (!dialog.clientTest.deleteMessage( messageID)) {
					System.out.println("ID: " + messageID + " sind falsch ");
				}
				
				break;

			case 3:

				System.out.println("Ersetzen : \n ");
				System.out.println("neue Nachricht eingeben : ");
				
				Scanner scan11 = new Scanner(System.in);
				messagea = scan11.nextLine();
				
				System.out.println("MessageID : \n ");
				scanMain = new Scanner(System.in);
				String mId = scanMain.nextLine();

				if (!dialog.clientTest.setMessage(messagea, mId)) {
					System.out.println("UID: " + mId + " und/oder " + "Message: " + messagea + " Bname: bName"
							+ " ist falsch ");
				}
				break;
			case 4:

				System.out.println("\n Ausgabe von alle Message auf server:\n");
				messageListtest = dialog.clientTest.getMessage();
				for (int y = 0; y < messageListtest.size(); y++) {
					System.out.println("Nachricht: " + messageListtest.get(y).text + " -BNAME:" + messageListtest.get(y).uName
							+ " -UID:" + messageListtest.get(y).uid + " -ID:" + messageListtest.get(y).id);
				}
				break;
			case 5:
				System.out.println("Server wird gewechselt");
			
				do{
					
					System.out.println("Mit welchen Server moechten sie verbinden\n");
					System.out.println("IP "+serDaten1.ip+"  Port"+serDaten1.port+" - 0\n");
					System.out.println("IP "+serDaten2.ip+"  Port"+serDaten2.port+" - 1 "
							+ "\nAbbrechen 2 ->");
					
					scanMain = new Scanner(System.in);
					auswahl = scanMain.nextInt();
					System.out.println(auswahl);
					
				}while(auswahl<0||auswahl>2);
				
				
				if(auswahl==0){
					loginInfo=new LoginInformation (userArray.get(userPos).isAdmin,serDaten1);
				}else if(auswahl ==1){
					loginInfo=new LoginInformation (userArray.get(userPos).isAdmin,serDaten2);
				}else{
					System.out.println("Abbrechen");
					break;
				}
				
				dialog.clientTest.disconnectToServer();
				dialog.clientTest = new StartClient(loginInfo,userArray.get(userPos));
			
				break;
			case 6:
				for(int r=0;r<dialog.clientTest.getChildNames().size();r++){
				String childname = dialog.clientTest.getChildNames().get(r);
				System.out.println("Kindname: " + childname + " IP: " + dialog.clientTest.getChildIP(childname)
						+ " Port" + dialog.clientTest.getChildPort(childname));
				}

				System.out.println(dialog.clientTest.getFatherName());
				System.out.println(dialog.clientTest.getFatherIP());
				System.out.println(dialog.clientTest.getFatherPort());
				break;
			case 7:
				
				System.out.println(dialog.clientTest.getFatherName());
				System.out.println(dialog.clientTest.getFatherIP());
				System.out.println(dialog.clientTest.getFatherPort());
				
				messageListtest = dialog.clientTest.getMessage();
				System.out.println(messageListtest.get(messageListtest.size()-1).text+" wird zu vater geschickt");
				dialog.clientTest.publishOnFather(messageListtest.get(messageListtest.size()-1));
				break;
			case 8:
				
				messageListtest = dialog.clientTest.getMessage();
				System.out.println(messageListtest.get(0).text+" wird zu kinder geschickt");
				
				dialog.clientTest.publishOnChilds(messageListtest.get(messageListtest.size()-1));
				break;
			case 9:
				System.out.println("Erstezen an alles CHILDS: entwerder selbst andern und an alle childs senden oder das geanderte von andere Child an alle Senden  ");
				messageListtest = dialog.clientTest.getMessage();
				for(int y =0; y<messageListtest.size();++y){
					System.out.println("NR "+y+ " Nachricht "+messageListtest.get(y).text);
					
				}
				scanMain = new Scanner(System.in);
				auswahl = scanMain.nextInt();
				//System.out.println(auswahl);
				// wenn selbst text geandert dann bitte messageListtest.get(auswahl) und text andern und fkt aufrufen
				
				//messageListtest.get(auswahl).text="test";
				

				if (!dialog.clientTest.setMessageChild(messageListtest.get(auswahl))) {
					System.out.println("UID: " + messageListtest.get(auswahl).uid + " und/oder " + "Message: " + messageListtest.get(auswahl).text );
				}
			//	System.out.println(messageListtest.get(0).text+" wird zu kinder geschickt");
				
				break;
			case 0:
				System.out.println("Beendet");
				beenden = true;
				break;
			default:
				System.out.println("bitte gib eine richtige Eingabe!\n");
				break;

			}
		}
	}
}

