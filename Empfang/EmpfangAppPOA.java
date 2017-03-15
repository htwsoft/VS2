package Empfang;


/**
* Empfang/EmpfangAppPOA.java .
* Generated by the IDL-to-Java compiler (portable), version "3.2"
* from Empfang.idl
* Dienstag, 6. Dezember 2016 15:41 Uhr MEZ
*/

public abstract class EmpfangAppPOA extends org.omg.PortableServer.Servant
 implements Empfang.EmpfangAppOperations, org.omg.CORBA.portable.InvokeHandler
{

  // Constructors

  private static java.util.Hashtable _methods = new java.util.Hashtable ();
  static
  {
    _methods.put ("send", new java.lang.Integer (0));
    _methods.put ("benutzername", new java.lang.Integer (1));
    _methods.put ("getstring", new java.lang.Integer (2));
    _methods.put ("getSTringArray", new java.lang.Integer (3));
  }

  public org.omg.CORBA.portable.OutputStream _invoke (String $method,
                                org.omg.CORBA.portable.InputStream in,
                                org.omg.CORBA.portable.ResponseHandler $rh)
  {
    org.omg.CORBA.portable.OutputStream out = null;
    java.lang.Integer __method = (java.lang.Integer)_methods.get ($method);
    if (__method == null)
      throw new org.omg.CORBA.BAD_OPERATION (0, org.omg.CORBA.CompletionStatus.COMPLETED_MAYBE);

    switch (__method.intValue ())
    {
       case 0:  // Empfang/EmpfangApp/send
       {
         String a = in.read_string ();
         this.send (a);
         out = $rh.createReply();
         break;
       }

       case 1:  // Empfang/EmpfangApp/benutzername
       {
         String name = in.read_string ();
         this.benutzername (name);
         out = $rh.createReply();
         break;
       }

       case 2:  // Empfang/EmpfangApp/getstring
       {
         String $result = null;
         $result = this.getstring ();
         out = $rh.createReply();
         out.write_string ($result);
         break;
       }

       case 3:  // Empfang/EmpfangApp/getSTringArray
       {
         String $result[] = null;
         $result = this.getSTringArray ();
         out = $rh.createReply();
         Empfang.listHelper.write (out, $result);
         break;
       }

       default:
         throw new org.omg.CORBA.BAD_OPERATION (0, org.omg.CORBA.CompletionStatus.COMPLETED_MAYBE);
    }

    return out;
  } // _invoke

  // Type-specific CORBA::Object operations
  private static String[] __ids = {
    "IDL:Empfang/EmpfangApp:1.0"};

  public String[] _all_interfaces (org.omg.PortableServer.POA poa, byte[] objectId)
  {
    return (String[])__ids.clone ();
  }

  public EmpfangApp _this() 
  {
    return EmpfangAppHelper.narrow(
    super._this_object());
  }

  public EmpfangApp _this(org.omg.CORBA.ORB orb) 
  {
    return EmpfangAppHelper.narrow(
    super._this_object(orb));
  }


} // class EmpfangAppPOA
