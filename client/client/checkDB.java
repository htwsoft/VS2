/*
 * Klasse die  versucht beim Start vom client die Daten von der DB ab zu arbeiten
 *  @author Salvatore Simonte
 */
package client;
import storageSystem.*;
import Datenbank.dbInfo.Fkt;

public class checkDB implements Runnable {
	StorageMessages testDb ;
	String serverName;
	StartClient client;

	 public void run() {

	        	if(!this.testDb.readEintrag(this.serverName).isEmpty()){
	        		for(int i =0;i<10;++i){
	        		
	        		send();
	        	}
	        }	       
	    }
	 
	 checkDB(StartClient client,StorageMessages testDb ,String serverName){
		 this.testDb=testDb;
		 this.serverName=serverName;
		 this.client=client;
	 }
	 
	 /*
	  * entscheidet welche FUnktion aufegrufen wurde und dann sendet dies an dem Server
	  */
	private void send(){
		
			for(int i =0 ;i<this.testDb.readEintrag(this.serverName).size();++i){
			
				switch(this.testDb.readEintrag(this.serverName).get(i).fkt){
				case SCHREIBEN :
					if(this.client.schreibeMessageFuerThread(this.testDb.readEintrag(this.serverName).get(i).message)){
						this.testDb.delete(i);
					}
					break;
				
				case LOESCHEN:
					if(this.client.deleteMessagefuerThread(this.testDb.readEintrag(this.serverName).get(i).idNachricht)){
						this.testDb.delete(i);
					}
					
					break;
				
				case ERSETZTEN:
						if(this.client.setMessagefuerThread(this.testDb.readEintrag(this.serverName).get(i).message,this.testDb.readEintrag(this.serverName).get(i).idNachricht)){
							this.testDb.delete(i);
						}
							break;
				}
			}
	}
	  
}
