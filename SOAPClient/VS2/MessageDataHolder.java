package VS2;

/**
* VS2/MessageDataHolder.java .
* Generated by the IDL-to-Java compiler (portable), version "3.2"
* from VS2.idl
* Monday, March 27, 2017 11:04:03 AM CEST
*/

public final class MessageDataHolder implements org.omg.CORBA.portable.Streamable
{
  public VS2.MessageData value = null;

  public MessageDataHolder ()
  {
  }

  public MessageDataHolder (VS2.MessageData initialValue)
  {
    value = initialValue;
  }

  public void _read (org.omg.CORBA.portable.InputStream i)
  {
    value = VS2.MessageDataHelper.read (i);
  }

  public void _write (org.omg.CORBA.portable.OutputStream o)
  {
    VS2.MessageDataHelper.write (o, value);
  }

  public org.omg.CORBA.TypeCode _type ()
  {
    return VS2.MessageDataHelper.type ();
  }

}
