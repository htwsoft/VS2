package VS2;


/**
* VS2/LoginServerInterfaceOperations.java .
* Generated by the IDL-to-Java compiler (portable), version "3.2"
* from VS2.idl
* Monday, March 27, 2017 11:04:03 AM CEST
*/

public interface LoginServerInterfaceOperations 
{
  VS2.LoginInformation login (VS2.UserData uData);
  boolean reg (VS2.UserData uData, String regData);
} // interface LoginServerInterfaceOperations
