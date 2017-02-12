
import java.util.ArrayList;
import java.util.Scanner;
import VS2.*;

public class Dialog {

	public static void main(String args[]) {
		ArrayList<MessageData> messageListtest = new ArrayList<MessageData>();

		boolean shutdown = false;
		String messagea;
		String messageID;
		String bName;
		MessageData msgData;
		int loeschuid;
		StartClient test;
	//	 test = new StartClient("127.0.0.1",6000);
		test = new StartClient(args);
		 System.out.println("Benutzer name:");
		Scanner scan = new Scanner(System.in);
		String username = scan.nextLine();

		test.loginBenutzer(username, "12345");
		int i;
		boolean beenden = false;

		while (!beenden) {
			System.out.println("\n Was möchten Sie machen?" +
								"\nBeenden:0 " + 
								"\nNachricht schreiben :1"
								+ "\nNachricht löschen 2:" 
								+ "\nNachricht ersetzen: 3" 
								+ "\nNachricht Ausgabe: 4"
								+ "\nServer wechseln 5 (automatisch): "
								+ "\nGebe Vater und kinder Infos 6" + "\n -----> ");
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

				if (!test.deleteMessage(loeschuid, messageID)) {
					System.out.println("UID: " + loeschuid + " und/oder " + "ID: " + messageID + " sind falsch ");
				}
				break;

			case 3:

				System.out.println("Ersetzen : \n ");
				System.out.println("neue Message : ");
				Scanner scan11 = new Scanner(System.in);
				messagea = scan11.nextLine();
				System.out.println("UserName : \n ");
				scan = new Scanner(System.in);
				bName = scan.nextLine();
				System.out.println("UID : \n ");
				scan = new Scanner(System.in);
				loeschuid = scan.nextInt();
				System.out.println("MessageID : \n ");
				scan = new Scanner(System.in);
				String mId = scan.nextLine();

				if (!test.setMessage(messagea, mId ,loeschuid, bName)) {
					System.out.println("UID: " + loeschuid + " und/oder " + "Massage: " + messagea + " Bname: bName"
							+ " sind falsch ");
				}
				break;
			case 4:

				System.out.println("\n Ausgabe von alle Message auf server:\n");
				messageListtest = test.getMessage();
				for (int y = 0; y < messageListtest.size(); y++) {
					System.out.println("TEXT:" + messageListtest.get(y).text + " -BNAME:" + messageListtest.get(y).uName
							+ " -UID:" + messageListtest.get(y).uid + " -ID:" + messageListtest.get(y).id);
				}
				break;
			case 5:
				System.out.println("Bitte ORBD und Server neustarten mit der neue ip wenn gleich PC");
				String ip = test.getFatherIP();
				int port = test.getFatherPort();
				test.disconnectToServer();
				System.out.println(ip + port);
				System.out.println("Moechten sie jetzt verbindne (y eingbene)");
				scan = new Scanner(System.in);
				String eingabe = scan.nextLine();

				if (eingabe.equals("y")) {
					System.out.println(ip + port);
					test.loginBenutzer(username, "12345");
					test = new StartClient(ip, port);

				}
				break;
			case 6:
				String childname=test.getChildNames().get(0);
				System.out.println("Kindname: "+childname+" IP: "+test.getChildIP(childname)+" Port"+test.getChildPort(childname));
				
				childname=test.getChildNames().get(1);
				System.out.println("Kindname: "+childname+" IP: "+test.getChildIP(childname)+" Port"+test.getChildPort(childname));
				
				
				System.out.println(test.getFatherName());
				System.out.println(test.getFatherIP());
				System.out.println(test.getFatherPort());
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
