package VS2;


/**
* VS2/ConnectInformationData.java .
* Generated by the IDL-to-Java compiler (portable), version "3.2"
* from VS2.idl
* Monday, March 27, 2017 11:08:53 AM CEST
*/

public final class ConnectInformationData implements org.omg.CORBA.portable.IDLEntity
{
  public String ip = null;
  public int port = (int)0;

  public ConnectInformationData ()
  {
  } // ctor

  public ConnectInformationData (String _ip, int _port)
  {
    ip = _ip;
    port = _port;
  } // ctor

} // class ConnectInformationData
