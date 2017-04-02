package Datenbank;
/*
* 
* Eine Klasse das den Inhalt einer SPalter der Db enthaelt
*  @author Salvatore Simonte
*/
public class dbInfo {
	public enum Fkt{ SCHREIBEN,LOESCHEN,ERSETZTEN}
	 public int userID = (int)0;
	  public String userName = null;
	  public String password = null;
	  public String server=null;
	  public String message=null;
	  public boolean isShared=false;
	  public boolean isAdmin = false;
	  public Fkt fkt=null;
	  public String idNachricht=null;
	  public dbInfo ()
	  {
	  } 

	  public dbInfo ( String idNachricht, int uid, String username,String password, String server,boolean isAdmin,boolean isShared,String message,Fkt fkt )
	  {
	   this.userID = uid;
	   this.userName = username;
	   this.password=password;
	   this.isAdmin=isAdmin;
	   this.isShared=isShared;
	   this.message=message;
	   this.fkt=fkt;
		this.idNachricht=idNachricht;
	  } 
}




