package VS2;


/**
* VS2/array_of_StringHolder.java .
* Generated by the IDL-to-Java compiler (portable), version "3.2"
* from VS2.idl
* Monday, March 27, 2017 1:51:10 PM CEST
*/


//Definition string[], da IDL nicht kennt
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
    value = VS2.array_of_StringHelper.read (i);
  }

  public void _write (org.omg.CORBA.portable.OutputStream o)
  {
    VS2.array_of_StringHelper.write (o, value);
  }

  public org.omg.CORBA.TypeCode _type ()
  {
    return VS2.array_of_StringHelper.type ();
  }

}
