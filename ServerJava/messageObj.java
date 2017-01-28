package ServerJava;
import java.util.ArrayList;

import VS2idl.*;

public class messageObj extends ClientMessageboardInterfacePOA {
	ArrayList<MessageData> xmlArray;
	int i ;
	messageObj(){
		this.xmlArray=new  ArrayList<MessageData>();
		this.i =0;
	}
	@Override
	public boolean setMessage(String message, int uid, String uName) {
		// TODO Auto-generated method stub
		return false;
	}

	@Override
	public boolean deleteMessage(int uid) {
		
		for(int x =0;x<xmlArray.size();++x){
			if (xmlArray.get(x).uid==uid){
				xmlArray.remove(x);
				return true;
			}
		}
		
		return false;
	}

	@Override
	public boolean createNewMessage(String message, int uid, String uName) {
		
		MessageData messageData=new MessageData(uid, "test", uName, message);
		i++;
		return xmlArray.add(messageData);
	}

	@Override
	public MessageData getNextMessage() {
		if (!xmlArray.isEmpty()){
			return xmlArray.get(i-1) ;
		}
		return  new MessageData(0, "leer", "leer","leer");
		
	}

	@Override
	public MessageData getPreviousMessage() {
		// TODO Auto-generated method stub
		return null;
	}
	@Override
	public MessageData[] getMessage() {
		 MessageData[] messa = new  MessageData[xmlArray.size()]; 
		if(!xmlArray.isEmpty()){
		
		 for (int z=0;z<xmlArray.size();z++){
			 messa[z]=xmlArray.get(z);
		 }
		}
		return messa;
	}

}
