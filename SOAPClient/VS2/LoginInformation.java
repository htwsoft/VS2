package VS2;


/**
* VS2/LoginInformation.java .
* Generated by the IDL-to-Java compiler (portable), version "3.2"
* from VS2.idl
* Saturday, March 25, 2017 2:41:42 PM CET
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
