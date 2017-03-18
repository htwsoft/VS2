import java.util.Scanner;
import VS2.*;

/*
* Klasse zum Testen des Soap-Clients
*/

import java.util.Scanner;
import VS2.*;

public class SOAPClientDialog
{
    private SOAPClient soapClient = null;
    
    public SOAPClientDialog(String ip, int port)
    {
        //Klasse SOAP-Client erzeugen 
        this.soapClient = new SOAPClient(ip, port);
        //Verbindung zum Server ausfbauen
        this.soapClient.connectToServer();
        //Pruefen ob Verbindung zum Corba-Server funktioniert hat
        if(soapClient.isServerConnected())
        {
            //Verbindung konnte aufgebaut werden
            this.zeigeMenue();
            //Verbindung zum Server trennen
            this.soapClient.disconnectFromServer();
        }
    }

    /* Methode zeigt ein Steuerungsmenue fuer den Test */
    private void zeigeMenue()
    {
        int benutzerWahl = -1;
        Scanner eingabe = new Scanner(System.in);
        while(benutzerWahl != 0)
        {           
            System.out.println("Was möchten Sie tun?:");
            System.out.println("1: Nachrichten erstellen / senden");
            System.out.println("0: Test beenden");
            benutzerWahl = eingabe.nextInt();
            switch (benutzerWahl) 
            {
                case 1:
                    schreibeMessage();
                    break;
                case 0:
                    System.out.println("Test wird beendet");
                    break;
                default:
                    System.out.println("Falsche Eingabe");
                    break;
            }
            System.out.println("");
        }        
    }

    /* Senden einer CreateMessage Nachricht an den Corba-Server */
    private void schreibeMessage()
    {
        Scanner eingabe = new Scanner(System.in);
        String message = "";
        boolean ok = false;
        System.out.println("Bitte einen Text eingeben:");
        message = eingabe.nextLine();
        //Aufrufen der CreateMessage-Methode auf dem Server
        ok = this.soapClient.writeMessage(message);
        //Pruefen ob das anlegen der message funktioniert hat
        if(ok)
        {
            System.out.println("Nachricht erfolgreich gesendet");
        }
        else
        {   
            System.out.println("Fehler beim senden der Nachricht");
        }
    }
}
