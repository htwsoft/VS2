package storageSystem;

import java.util.ArrayList;
import java.io.Serializable;
import Datenbank.*;
import Datenbank.dbInfo.Fkt;

/*
  * Class StorageMessages
  * Speichert Empfaenger (Dienstname), Sender (Dienstname) und dazugehoerige Message.
  * Speichern in dynamischem Array, fluechtig im Programm-Speicher.
  * Vorlaeufiges Test-System, bis Datenbank-Schnittstelle, diese Klasse austauscht.
  * Public Schnittstellen-Methoden sind final definiert und werden spaeter
  * mit Datenbank genauso genutzt werden.
  */
  

public class StorageMessages implements Serializable    
{
    private static final int EMPF_POS = 0;
    private static final int SEND_POS = 1;
    private static final int MESS_POS = 2;
    private static StorageMessage messg;
    private ArrayList<ArrayList<String>> storeStrings;
    private ArrayList<Integer> messageID;
    private int iterator;
    private int idCounter;
    
	int iter=0;
	int stelle=0;
	boolean delete=false;
	
    public  StorageMessages ()
    {
		starten();
        
        messageID = new ArrayList<Integer>();
        
        iterator = 0;
        idCounter = 0;
    }
    
    private synchronized void starten(){
		messg =new StorageMessage();
	}
    /* 
      * Returns element at position of iterator
      * Synchronized, thread safe!
      *
      * @return   returns Element an Iterator Position, oder NULL, wenn Liste leer
      */  
    public synchronized ArrayList<dbInfo> readEintrag (String server)
    {
       ArrayList<dbInfo> eintrag=new ArrayList<dbInfo>();
				
		eintrag= messg.getMessage(server);
		
		return eintrag;
    }
    
    /* 
      * Removes the entry for given messageID
      * Synchronized, thread safe!
      * 
      * @param  id  messageID assigns to the message, which should be deleted
      */
    public synchronized void delete ( int id )
    {
        messg.deleteEintrag( id);
    }
    
    /* 
      * Adds a new element at the end of the list
      * Synchronized, thread safe!
      * 
      * @param  e   Empfaenger String for new element
      * @param  s   Sender String for new element
      * @param  m   Message String for new element
      * @return     returns immer true, keine Fehlerabfrage und Fehlschlag nicht moeglich
      */
    public synchronized boolean writeEintrag ( String idNachricht,int uuid, String username,String password, String server,boolean isAdmin,boolean isShared,String message,Fkt schreiben )
    {        
    	
       return messg.writeEintrag(idNachricht,uuid, username, password,server, isAdmin, isShared, message,schreiben);
    }
}

