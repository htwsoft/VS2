package VS2;

/**
* VS2/UserDataHolder.java .
* Generated by the IDL-to-Java compiler (portable), version "3.2"
* from VS2.idl
* Tuesday, March 21, 2017 10:56:29 AM CET
*/

public final class UserDataHolder implements org.omg.CORBA.portable.Streamable
{
  public VS2.UserData value = null;

  public UserDataHolder ()
  {
  }

  public UserDataHolder (VS2.UserData initialValue)
  {
    value = initialValue;
  }

  public void _read (org.omg.CORBA.portable.InputStream i)
  {
    value = VS2.UserDataHelper.read (i);
  }

  public void _write (org.omg.CORBA.portable.OutputStream o)
  {
    VS2.UserDataHelper.write (o, value);
  }

  public org.omg.CORBA.TypeCode _type ()
  {
    return VS2.UserDataHelper.type ();
  }

}