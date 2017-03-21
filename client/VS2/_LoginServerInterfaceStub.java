package VS2;


/**
* VS2/_LoginServerInterfaceStub.java .
* Generated by the IDL-to-Java compiler (portable), version "3.2"
* from VS2.idl
* Tuesday, March 21, 2017 9:45:34 AM CET
*/

public class _LoginServerInterfaceStub extends org.omg.CORBA.portable.ObjectImpl implements VS2.LoginServerInterface
{

  public VS2.LoginInformation login (VS2.UserData uData)
  {
            org.omg.CORBA.portable.InputStream $in = null;
            try {
                org.omg.CORBA.portable.OutputStream $out = _request ("login", true);
                VS2.UserDataHelper.write ($out, uData);
                $in = _invoke ($out);
                VS2.LoginInformation $result = VS2.LoginInformationHelper.read ($in);
                return $result;
            } catch (org.omg.CORBA.portable.ApplicationException $ex) {
                $in = $ex.getInputStream ();
                String _id = $ex.getId ();
                throw new org.omg.CORBA.MARSHAL (_id);
            } catch (org.omg.CORBA.portable.RemarshalException $rm) {
                return login (uData        );
            } finally {
                _releaseReply ($in);
            }
  } // login

  public boolean reg (VS2.UserData uData, String regData)
  {
            org.omg.CORBA.portable.InputStream $in = null;
            try {
                org.omg.CORBA.portable.OutputStream $out = _request ("reg", true);
                VS2.UserDataHelper.write ($out, uData);
                $out.write_string (regData);
                $in = _invoke ($out);
                boolean $result = $in.read_boolean ();
                return $result;
            } catch (org.omg.CORBA.portable.ApplicationException $ex) {
                $in = $ex.getInputStream ();
                String _id = $ex.getId ();
                throw new org.omg.CORBA.MARSHAL (_id);
            } catch (org.omg.CORBA.portable.RemarshalException $rm) {
                return reg (uData, regData        );
            } finally {
                _releaseReply ($in);
            }
  } // reg

  // Type-specific CORBA::Object operations
  private static String[] __ids = {
    "IDL:VS2/LoginServerInterface:1.0"};

  public String[] _ids ()
  {
    return (String[])__ids.clone ();
  }

  private void readObject (java.io.ObjectInputStream s) throws java.io.IOException
  {
     String str = s.readUTF ();
     String[] args = null;
     java.util.Properties props = null;
     org.omg.CORBA.ORB orb = org.omg.CORBA.ORB.init (args, props);
   try {
     org.omg.CORBA.Object obj = orb.string_to_object (str);
     org.omg.CORBA.portable.Delegate delegate = ((org.omg.CORBA.portable.ObjectImpl) obj)._get_delegate ();
     _set_delegate (delegate);
   } finally {
     orb.destroy() ;
   }
  }

  private void writeObject (java.io.ObjectOutputStream s) throws java.io.IOException
  {
     String[] args = null;
     java.util.Properties props = null;
     org.omg.CORBA.ORB orb = org.omg.CORBA.ORB.init (args, props);
   try {
     String str = orb.object_to_string (this);
     s.writeUTF (str);
   } finally {
     orb.destroy() ;
   }
  }
} // class _LoginServerInterfaceStub
