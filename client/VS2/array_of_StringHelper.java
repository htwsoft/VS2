package VS2;


/**
* VS2/array_of_StringHelper.java .
* Generated by the IDL-to-Java compiler (portable), version "3.2"
* from VS2.idl
* Tuesday, March 21, 2017 10:56:29 AM CET
*/


//Definition string[], da IDL nicht kennt
abstract public class array_of_StringHelper
{
  private static String  _id = "IDL:VS2/array_of_String:1.0";

  public static void insert (org.omg.CORBA.Any a, String[] that)
  {
    org.omg.CORBA.portable.OutputStream out = a.create_output_stream ();
    a.type (type ());
    write (out, that);
    a.read_value (out.create_input_stream (), type ());
  }

  public static String[] extract (org.omg.CORBA.Any a)
  {
    return read (a.create_input_stream ());
  }

  private static org.omg.CORBA.TypeCode __typeCode = null;
  synchronized public static org.omg.CORBA.TypeCode type ()
  {
    if (__typeCode == null)
    {
      __typeCode = org.omg.CORBA.ORB.init ().create_string_tc (0);
      __typeCode = org.omg.CORBA.ORB.init ().create_sequence_tc (0, __typeCode);
      __typeCode = org.omg.CORBA.ORB.init ().create_alias_tc (VS2.array_of_StringHelper.id (), "array_of_String", __typeCode);
    }
    return __typeCode;
  }

  public static String id ()
  {
    return _id;
  }

  public static String[] read (org.omg.CORBA.portable.InputStream istream)
  {
    String value[] = null;
    int _len0 = istream.read_long ();
    value = new String[_len0];
    for (int _o1 = 0;_o1 < value.length; ++_o1)
      value[_o1] = istream.read_string ();
    return value;
  }

  public static void write (org.omg.CORBA.portable.OutputStream ostream, String[] value)
  {
    ostream.write_long (value.length);
    for (int _i0 = 0;_i0 < value.length; ++_i0)
      ostream.write_string (value[_i0]);
  }

}
