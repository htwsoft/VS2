package VS2;


/**
* VS2/UserData.java .
* Generated by the IDL-to-Java compiler (portable), version "3.2"
* from VS2.idl
* Monday, March 27, 2017 1:51:10 PM CEST
*/

public final class UserData implements org.omg.CORBA.portable.IDLEntity
{
  public int userID = (int)0;
  public String userName = null;
  public String password = null;
  public boolean isAdmin = false;

  public UserData ()
  {
  } // ctor

  public UserData (int _userID, String _userName, String _password, boolean _isAdmin)
  {
    userID = _userID;
    userName = _userName;
    password = _password;
    isAdmin = _isAdmin;
  } // ctor

} // class UserData
