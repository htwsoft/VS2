package VS2;

/**
* VS2/MessageboardServerInterfaceHolder.java .
* Generated by the IDL-to-Java compiler (portable), version "3.2"
* from VS2.idl
* Tuesday, March 21, 2017 11:10:23 AM CET
*/

public final class MessageboardServerInterfaceHolder implements org.omg.CORBA.portable.Streamable
{
  public VS2.MessageboardServerInterface value = null;

  public MessageboardServerInterfaceHolder ()
  {
  }

  public MessageboardServerInterfaceHolder (VS2.MessageboardServerInterface initialValue)
  {
    value = initialValue;
  }

  public void _read (org.omg.CORBA.portable.InputStream i)
  {
    value = VS2.MessageboardServerInterfaceHelper.read (i);
  }

  public void _write (org.omg.CORBA.portable.OutputStream o)
  {
    VS2.MessageboardServerInterfaceHelper.write (o, value);
  }

  public org.omg.CORBA.TypeCode _type ()
  {
    return VS2.MessageboardServerInterfaceHelper.type ();
  }

}
