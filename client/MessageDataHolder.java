
/**
* MessageDataHolder.java .
* Generated by the IDL-to-Java compiler (portable), version "3.2"
* from VS2_klein.idl
* Monday, January 30, 2017 9:47:00 AM CET
*/

public final class MessageDataHolder implements org.omg.CORBA.portable.Streamable
{
  public MessageData value = null;

  public MessageDataHolder ()
  {
  }

  public MessageDataHolder (MessageData initialValue)
  {
    value = initialValue;
  }

  public void _read (org.omg.CORBA.portable.InputStream i)
  {
    value = MessageDataHelper.read (i);
  }

  public void _write (org.omg.CORBA.portable.OutputStream o)
  {
    MessageDataHelper.write (o, value);
  }

  public org.omg.CORBA.TypeCode _type ()
  {
    return MessageDataHelper.type ();
  }

}
