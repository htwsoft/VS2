package Empfang;

/**
* Empfang/EmpfangAppHolder.java .
* Generated by the IDL-to-Java compiler (portable), version "3.2"
* from Empfang.idl
* Dienstag, 6. Dezember 2016 15:41 Uhr MEZ
*/

public final class EmpfangAppHolder implements org.omg.CORBA.portable.Streamable
{
  public Empfang.EmpfangApp value = null;

  public EmpfangAppHolder ()
  {
  }

  public EmpfangAppHolder (Empfang.EmpfangApp initialValue)
  {
    value = initialValue;
  }

  public void _read (org.omg.CORBA.portable.InputStream i)
  {
    value = Empfang.EmpfangAppHelper.read (i);
  }

  public void _write (org.omg.CORBA.portable.OutputStream o)
  {
    Empfang.EmpfangAppHelper.write (o, value);
  }

  public org.omg.CORBA.TypeCode _type ()
  {
    return Empfang.EmpfangAppHelper.type ();
  }

}
