package VS2;


/**
* VS2/MessageData.java .
* Generated by the IDL-to-Java compiler (portable), version "3.2"
* from VS2.idl
* Monday, March 27, 2017 1:44:58 PM CEST
*/

public final class MessageData implements org.omg.CORBA.portable.IDLEntity
{
  public int uid = (int)0;
  public String id = null;
  public String uName = null;
  public String text = null;
  public boolean shared = false;

  public MessageData ()
  {
  } // ctor

  public MessageData (int _uid, String _id, String _uName, String _text, boolean _shared)
  {
    uid = _uid;
    id = _id;
    uName = _uName;
    text = _text;
    shared = _shared;
  } // ctor

} // class MessageData
