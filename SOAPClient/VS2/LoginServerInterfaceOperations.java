package VS2;


/**
* VS2/LoginServerInterfaceOperations.java .
* Generated by the IDL-to-Java compiler (portable), version "3.2"
* from VS2.idl
* Saturday, March 18, 2017 5:22:38 PM CET
*/

public interface LoginServerInterfaceOperations 
{
  VS2.LoginInformation login (VS2.UserData uData);
  boolean reg (VS2.UserData uData, String regData);
} // interface LoginServerInterfaceOperations