package VS2;


/**
* VS2/MessageboardServerInterfaceHelper.java .
* Generated by the IDL-to-Java compiler (portable), version "3.2"
* from VS2.idl
* Monday, March 27, 2017 3:15:39 PM CEST
*/

abstract public class MessageboardServerInterfaceHelper
{
  private static String  _id = "IDL:VS2/MessageboardServerInterface:1.0";

  public static void insert (org.omg.CORBA.Any a, VS2.MessageboardServerInterface that)
  {
    org.omg.CORBA.portable.OutputStream out = a.create_output_stream ();
    a.type (type ());
    write (out, that);
    a.read_value (out.create_input_stream (), type ());
  }

  public static VS2.MessageboardServerInterface extract (org.omg.CORBA.Any a)
  {
    return read (a.create_input_stream ());
  }

  private static org.omg.CORBA.TypeCode __typeCode = null;
  synchronized public static org.omg.CORBA.TypeCode type ()
  {
    if (__typeCode == null)
    {
      __typeCode = org.omg.CORBA.ORB.init ().create_interface_tc (VS2.MessageboardServerInterfaceHelper.id (), "MessageboardServerInterface");
    }
    return __typeCode;
  }

  public static String id ()
  {
    return _id;
  }

  public static VS2.MessageboardServerInterface read (org.omg.CORBA.portable.InputStream istream)
  {
    return narrow (istream.read_Object (_MessageboardServerInterfaceStub.class));
  }

  public static void write (org.omg.CORBA.portable.OutputStream ostream, VS2.MessageboardServerInterface value)
  {
    ostream.write_Object ((org.omg.CORBA.Object) value);
  }

  public static VS2.MessageboardServerInterface narrow (org.omg.CORBA.Object obj)
  {
    if (obj == null)
      return null;
    else if (obj instanceof VS2.MessageboardServerInterface)
      return (VS2.MessageboardServerInterface)obj;
    else if (!obj._is_a (id ()))
      throw new org.omg.CORBA.BAD_PARAM ();
    else
    {
      org.omg.CORBA.portable.Delegate delegate = ((org.omg.CORBA.portable.ObjectImpl)obj)._get_delegate ();
      VS2._MessageboardServerInterfaceStub stub = new VS2._MessageboardServerInterfaceStub ();
      stub._set_delegate(delegate);
      return stub;
    }
  }

  public static VS2.MessageboardServerInterface unchecked_narrow (org.omg.CORBA.Object obj)
  {
    if (obj == null)
      return null;
    else if (obj instanceof VS2.MessageboardServerInterface)
      return (VS2.MessageboardServerInterface)obj;
    else
    {
      org.omg.CORBA.portable.Delegate delegate = ((org.omg.CORBA.portable.ObjectImpl)obj)._get_delegate ();
      VS2._MessageboardServerInterfaceStub stub = new VS2._MessageboardServerInterfaceStub ();
      stub._set_delegate(delegate);
      return stub;
    }
  }

}
