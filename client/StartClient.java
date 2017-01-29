/**
 *
 * @author imed
 */
import java.util.ArrayList;
import org.omg.CosNaming.*;
import org.omg.CosNaming.NamingContextPackage.*;

import java.util.Scanner;

import org.omg.CORBA.*;
/*
class LesenThread implements Runnable
{
	private Thread t;
	private ClientMessageboardInterface mbImpl;
	MessageData msg;
	LesenThread(ClientMessageboardInterface mbImpl){
		this.mbImpl = mbImpl;
	}
	//FÜR DIE GUI????
	
	@Override
	public void run() {
		
		while(true)
		{
			System.out.println("Obtained a handle on server object: " );
			//Aufruf der entfernten Methode
			msg = mbImpl.getNextMessage();
			System.out.println(msg.text + ", " + msg.id + ", " + msg.uid);
			try {
				Thread.sleep(2000);
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
	}
	   public void start () {
	      System.out.println("Starting lesen ");
	      if (t == null) {
	         t = new Thread (this);
	         t.start ();
	      }
	   }
	
}*/

public class StartClient{
	
	private String uName;
	private  int uid =12345;
	private  String message;
	public  MessageData msg;
	private ClientMessageboardInterface mbImpl; 
	boolean shutdown;
	
	public StartClient(){
		String[] url = new String[]{"-ORBInitialPort","6000","-ORBInitialHost","127.0.0.1"};
		
	    String method = "DataServiceName1";  //registrierter Name der implementierten Methode

	    try {
	      // Initialisiere ORB und beschaffe Zugang zum 'NameService'
	      // create and initialize the ORB
	      ORB orb = ORB.init(url, null);

	      // get the root naming context
	      org.omg.CORBA.Object objRef = orb.resolve_initial_references("NameService");
	      // Use NamingContextExt instead of NamingContext. This is 
	      // part of the Interoperable naming Service.  
	      NamingContextExt ncRef = NamingContextExtHelper.narrow(objRef);
	      mbImpl = ClientMessageboardInterfaceHelper.narrow(ncRef.resolve_str(method));
	      
	      
	    } catch (Exception e) {
	        System.out.println("ERROR : " + e) ;
	        e.printStackTrace(System.out);
	      }
	}
	
	public boolean setMessage(String message, int uid, String uName){
		
		return this.mbImpl.setMessage(message, uid, uName);
		
	}
	
	public MessageData getPreviousMessage() {
		
		return this.mbImpl.getPreviousMessage();
	}
	
	public boolean deleteMessage(int uid) {
		
		return this.mbImpl.deleteMessage(uid);
	}
	
	public ArrayList<MessageData> getMessage(){
		ArrayList<MessageData> messageList=new ArrayList<MessageData>();
		
		
		 MessageData test= mbImpl.getNextMessage(); 
		 messageList.add(test);
		 if (!test.text.equals("leer")){
			do{
				 test= mbImpl.getNextMessage(); 
				messageList.add(test);
			}while(!test.text.equals("leer"));
		 
		
			return messageList;
		}else{
			return null;
		}
		 
		
		
	}
	
	public boolean schreibeMessage(String message){
		return mbImpl.createNewMessage(message, this.uid, this.uName);
	}
	
	public void writeUser(String user) {
		this.uName=user;
	}
	public String getUser() {
		// TODO Auto-generated method stub
		return this.uName;
	}

	public MessageData[] getMessageList() {
		return mbImpl.getMessages();
		
	}
  public static void main(String args[]){
    boolean shutdown = false;
     
    StartClient test=new StartClient();
    Scanner scan=new Scanner(System.in);
    System.out.println("Username:");
    String username=scan.nextLine();
    
    test.writeUser("username");
    
    while(true){System.out.println("\n \n\n ");
    	System.out.println("Message:");
        String messagea=scan.nextLine();
    	//test.schreibeMessage(messagea);
    	System.out.println("\n \n\n Ausgabe von alle Message auf server:");
    	for(int y=0;y<test.getMessageList().length;y++){
    	    System.out.println(test.getMessageList()[y].text +" "+ test.getMessageList()[y].uid+" "+ test.getMessageList()[y].uName);
    	    }
    }
    
      
  }
}
