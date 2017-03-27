package VS2;


/**
* VS2/LoginInformationHelper.java .
* Generated by the IDL-to-Java compiler (portable), version "3.2"
* from VS2.idl
* Montag, 27. M�rz 2017 11:16 Uhr MESZ
*/

abstract public class LoginInformationHelper
{
  private static String  _id = "IDL:VS2/LoginInformation:1.0";

  public static void insert (org.omg.CORBA.Any a, VS2.LoginInformation that)
  {
    org.omg.CORBA.portable.OutputStream out = a.create_output_stream ();
    a.type (type ());
    write (out, that);
    a.read_value (out.create_input_stream (), type ());
  }

  public static VS2.LoginInformation extract (org.omg.CORBA.Any a)
  {
    return read (a.create_input_stream ());
  }

  private static org.omg.CORBA.TypeCode __typeCode = null;
  private static boolean __active = false;
  synchronized public static org.omg.CORBA.TypeCode type ()
  {
    if (__typeCode == null)
    {
      synchronized (org.omg.CORBA.TypeCode.class)
      {
        if (__typeCode == null)
        {
          if (__active)
          {
            return org.omg.CORBA.ORB.init().create_recursive_tc ( _id );
          }
          __active = true;
          org.omg.CORBA.StructMember[] _members0 = new org.omg.CORBA.StructMember [2];
          org.omg.CORBA.TypeCode _tcOf_members0 = null;
          _tcOf_members0 = org.omg.CORBA.ORB.init ().get_primitive_tc (org.omg.CORBA.TCKind.tk_boolean);
          _members0[0] = new org.omg.CORBA.StructMember (
            "adminRights",
            _tcOf_members0,
            null);
          _tcOf_members0 = VS2.ConnectInformationDataHelper.type ();
          _members0[1] = new org.omg.CORBA.StructMember (
            "server",
            _tcOf_members0,
            null);
          __typeCode = org.omg.CORBA.ORB.init ().create_struct_tc (VS2.LoginInformationHelper.id (), "LoginInformation", _members0);
          __active = false;
        }
      }
    }
    return __typeCode;
  }

  public static String id ()
  {
    return _id;
  }

  public static VS2.LoginInformation read (org.omg.CORBA.portable.InputStream istream)
  {
    VS2.LoginInformation value = new VS2.LoginInformation ();
    value.adminRights = istream.read_boolean ();
    value.server = VS2.ConnectInformationDataHelper.read (istream);
    return value;
  }

  public static void write (org.omg.CORBA.portable.OutputStream ostream, VS2.LoginInformation value)
  {
    ostream.write_boolean (value.adminRights);
    VS2.ConnectInformationDataHelper.write (ostream, value.server);
  }

}
