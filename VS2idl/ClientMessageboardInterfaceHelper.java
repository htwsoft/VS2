package VS2idl;


/**
* VS2idl/ClientMessageboardInterfaceHelper.java .
* Generated by the IDL-to-Java compiler (portable), version "3.2"
* from VS2_klein.idl
* Samstag, 28. Januar 2017 02:24 Uhr MEZ
*/

abstract public class ClientMessageboardInterfaceHelper
{
  private static String  _id = "IDL:VS2idl/ClientMessageboardInterface:1.0";

  public static void insert (org.omg.CORBA.Any a, VS2idl.ClientMessageboardInterface that)
  {
    org.omg.CORBA.portable.OutputStream out = a.create_output_stream ();
    a.type (type ());
    write (out, that);
    a.read_value (out.create_input_stream (), type ());
  }

  public static VS2idl.ClientMessageboardInterface extract (org.omg.CORBA.Any a)
  {
    return read (a.create_input_stream ());
  }

  private static org.omg.CORBA.TypeCode __typeCode = null;
  synchronized public static org.omg.CORBA.TypeCode type ()
  {
    if (__typeCode == null)
    {
      __typeCode = org.omg.CORBA.ORB.init ().create_interface_tc (VS2idl.ClientMessageboardInterfaceHelper.id (), "ClientMessageboardInterface");
    }
    return __typeCode;
  }

  public static String id ()
  {
    return _id;
  }

  public static VS2idl.ClientMessageboardInterface read (org.omg.CORBA.portable.InputStream istream)
  {
    return narrow (istream.read_Object (_ClientMessageboardInterfaceStub.class));
  }

  public static void write (org.omg.CORBA.portable.OutputStream ostream, VS2idl.ClientMessageboardInterface value)
  {
    ostream.write_Object ((org.omg.CORBA.Object) value);
  }

  public static VS2idl.ClientMessageboardInterface narrow (org.omg.CORBA.Object obj)
  {
    if (obj == null)
      return null;
    else if (obj instanceof VS2idl.ClientMessageboardInterface)
      return (VS2idl.ClientMessageboardInterface)obj;
    else if (!obj._is_a (id ()))
      throw new org.omg.CORBA.BAD_PARAM ();
    else
    {
      org.omg.CORBA.portable.Delegate delegate = ((org.omg.CORBA.portable.ObjectImpl)obj)._get_delegate ();
      VS2idl._ClientMessageboardInterfaceStub stub = new VS2idl._ClientMessageboardInterfaceStub ();
      stub._set_delegate(delegate);
      return stub;
    }
  }

  public static VS2idl.ClientMessageboardInterface unchecked_narrow (org.omg.CORBA.Object obj)
  {
    if (obj == null)
      return null;
    else if (obj instanceof VS2idl.ClientMessageboardInterface)
      return (VS2idl.ClientMessageboardInterface)obj;
    else
    {
      org.omg.CORBA.portable.Delegate delegate = ((org.omg.CORBA.portable.ObjectImpl)obj)._get_delegate ();
      VS2idl._ClientMessageboardInterfaceStub stub = new VS2idl._ClientMessageboardInterfaceStub ();
      stub._set_delegate(delegate);
      return stub;
    }
  }

}
