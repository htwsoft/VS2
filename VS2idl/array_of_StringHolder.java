package VS2idl;


/**
* VS2idl/array_of_StringHolder.java .
* Generated by the IDL-to-Java compiler (portable), version "3.2"
* from VS2_klein.idl
* Samstag, 28. Januar 2017 02:24 Uhr MEZ
*/

public final class array_of_StringHolder implements org.omg.CORBA.portable.Streamable
{
  public String value[] = null;

  public array_of_StringHolder ()
  {
  }

  public array_of_StringHolder (String[] initialValue)
  {
    value = initialValue;
  }

  public void _read (org.omg.CORBA.portable.InputStream i)
  {
    value = VS2idl.array_of_StringHelper.read (i);
  }

  public void _write (org.omg.CORBA.portable.OutputStream o)
  {
    VS2idl.array_of_StringHelper.write (o, value);
  }

  public org.omg.CORBA.TypeCode _type ()
  {
    return VS2idl.array_of_StringHelper.type ();
  }

}
