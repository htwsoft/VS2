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
		System.out.println("Bitte Ip und port eingeben ./StartClient.sh IP POrt");
		System.out.println("UserName : \n ");
				scanMain = new Scanner(System.in);
				 String bbName = scanMain.nextLine();
		System.out.println("Password : \n ");
				scanMain = new Scanner(System.in);
				 String bWord = scanMain.nextLine();
				
		dialog.clientTest=new StartClient(args[0],Integer.parseInt(args[1]),bbName,bWord);
		//dialog.clientTest=new StartClient("192.168.178.52",6000);
		int i;
		boolean beenden = false;

		while (!beenden) {
			System.out.println("\n Was möchten Sie machen?" + "\nBeenden:0 " + "\nNachricht schreiben :1"
					+ "\nNachricht löschen 2:" + "\nNachricht ersetzen: 3" + "\nNachricht Ausgabe: 4"
					+ "\nServer wechseln 5 (automatisch): " + "\nGebe Vater und kinder Infos 6" + "\n "+ "\n Nachricht wird zum Vater gesendet 7"+" \n Nachricht an die kinder gesendet8 "+" -----> ");
			scanMain = new Scanner(System.in);
			i = scanMain.nextInt();
			switch (i) {
			case 1:

				System.out.println("Message:");
				scanMain = new Scanner(System.in);
				messagea = scanMain.nextLine();

				System.out.println(dialog.clientTest.schreibeMessage(messagea));
				break;

			case 2:
				System.out.println("Loeschen (geht noch nicht muss noch angepasst werden ):");
				
				System.out.println("ID:");
				scanMain = new Scanner(System.in);
				messageID = scanMain.nextLine();

				if (!dialog.clientTest.deleteMessage( messageID)) {
					System.out.println("ID: " + messageID + " sind falsch ");
				}
				break;

			case 3:

				System.out.println("Ersetzen : \n ");
				System.out.println("neue Message : ");
				Scanner scan11 = new Scanner(System.in);
				messagea = scan11.nextLine();
				
				System.out.println("UID : \n ");
				scanMain = new Scanner(System.in);
				loeschuid = scanMain.nextInt();
				System.out.println("MessageID : \n ");
				scanMain = new Scanner(System.in);
				String mId = scanMain.nextLine();

				if (!dialog.clientTest.setMessage(messagea, mId, loeschuid)) {
					System.out.println("UID: " + loeschuid + " und/oder " + "Massage: " + messagea + " Bname: bName"
							+ " sind falsch ");
				}
				break;
			case 4:

				System.out.println("\n Ausgabe von alle Message auf server:\n");
				messageListtest = dialog.clientTest.getMessage();
				for (int y = 0; y < messageListtest.size(); y++) {
					System.out.println("TEXT:" + messageListtest.get(y).text + " -BNAME:" + messageListtest.get(y).uName
							+ " -UID:" + messageListtest.get(y).uid + " -ID:" + messageListtest.get(y).id);
				}
				break;
			case 5:
				System.out.println("Bitte ORBD und Server neustarten mit der neue ip wenn gleich PC");
				String ip = dialog.clientTest.getFatherIP();
				int port = dialog.clientTest.getFatherPort();
				dialog.clientTest.disconnectToServer();
				System.out.println(ip + port);
				System.out.println("Moechten sie jetzt verbindne (y eingbene)");
				scanMain = new Scanner(System.in);
				String eingabe = scanMain.nextLine();

				if (eingabe.equals("y")) {
					System.out.println(ip + port);
					// test.loginBenutzer(username, "12345");
					dialog.clientTest = new StartClient(ip, port,"salva","si");
				}
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
				System.out.println(dialog.clientTest.publishOnFather(messageListtest.get(messageListtest.size()-1)));
				break;
			case 8:
				
				messageListtest = dialog.clientTest.getMessage();
				System.out.println(messageListtest.get(messageListtest.size()-1).text+" wird zu kinder geschickt");
				
				System.out.println(dialog.clientTest.publishOnChilds(messageListtest.get(messageListtest.size()-1)));
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

