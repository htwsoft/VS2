package VS2;


/**
* VS2/LoginInformation.java .
* Generated by the IDL-to-Java compiler (portable), version "3.2"
* from VS2.idl
* Monday, March 27, 2017 11:08:53 AM CEST
*/

public final class LoginInformation implements org.omg.CORBA.portable.IDLEntity
{
  public boolean adminRights = false;
  public VS2.ConnectInformationData server = null;

  public LoginInformation ()
  {
  } // ctor

  public LoginInformation (boolean _adminRights, VS2.ConnectInformationData _server)
  {
    adminRights = _adminRights;
    server = _server;
  } // ctor

} // class LoginInformation
