package VS2;


/**
* VS2/MessageData.java .
* Generated by the IDL-to-Java compiler (portable), version "3.2"
* from VS2.idl
* Saturday, March 25, 2017 2:41:42 PM CET
*/

public final class MessageData implements org.omg.CORBA.portable.IDLEntity
{
  public int uid = (int)0;
  public String id = null;
  public String uName = null;
  public String text = null;

  public MessageData ()
  {
  } // ctor

  public MessageData (int _uid, String _id, String _uName, String _text)
  {
    uid = _uid;
    id = _id;
    uName = _uName;
    text = _text;
  } // ctor

} // class MessageData
