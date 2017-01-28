package ServerJava;

public class XML {
	String message;
	int uid;
	String uName;
	
	public XML(){
		this.message=null;
		this.uid=0;
		this.uName=null;	
	}
	
	XML(String message,  int uid, String uName){
		this.message=message;
		this.uid=uid;
		this.uName=uName;
	}
	
	public String getMessage(){
		return this.message;
	}
	
	public int getUid(){
		return this.uid;
	}
	
	public String getuName(){
		return this.uName;
	}
	public static void main(String[] args) {
		// TODO Auto-generated method stub

	}

}
