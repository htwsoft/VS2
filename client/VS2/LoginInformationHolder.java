package VS2;

/**
* VS2/LoginInformationHolder.java .
* Generated by the IDL-to-Java compiler (portable), version "3.2"
* from VS2.idl
* Monday, March 27, 2017 1:44:58 PM CEST
*/

public final class LoginInformationHolder implements org.omg.CORBA.portable.Streamable
{
  public VS2.LoginInformation value = null;

  public LoginInformationHolder ()
  {
  }

  public LoginInformationHolder (VS2.LoginInformation initialValue)
  {
    value = initialValue;
  }

  public void _read (org.omg.CORBA.portable.InputStream i)
  {
    value = VS2.LoginInformationHelper.read (i);
  }

  public void _write (org.omg.CORBA.portable.OutputStream o)
  {
    VS2.LoginInformationHelper.write (o, value);
  }

  public org.omg.CORBA.TypeCode _type ()
  {
    return VS2.LoginInformationHelper.type ();
  }

}
