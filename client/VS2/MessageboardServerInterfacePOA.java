package VS2;


/**
* VS2/MessageboardServerInterfacePOA.java .
* Generated by the IDL-to-Java compiler (portable), version "3.2"
* from VS2.idl
* Tuesday, January 31, 2017 6:35:56 PM CET
*/

public abstract class MessageboardServerInterfacePOA extends org.omg.PortableServer.Servant
 implements VS2.MessageboardServerInterfaceOperations, org.omg.CORBA.portable.InvokeHandler
{

  // Constructors

  private static java.util.Hashtable _methods = new java.util.Hashtable ();
  static
  {
    _methods.put ("getFatherName", new java.lang.Integer (0));
    _methods.put ("getChildNames", new java.lang.Integer (1));
    _methods.put ("getMessages", new java.lang.Integer (2));
    _methods.put ("setHighlightedMessage", new java.lang.Integer (3));
    _methods.put ("getHighlightedMessage", new java.lang.Integer (4));
    _methods.put ("getMessageWithId", new java.lang.Integer (5));
    _methods.put ("setMessage", new java.lang.Integer (6));
    _methods.put ("deleteMessage", new java.lang.Integer (7));
    _methods.put ("createNewMessage", new java.lang.Integer (8));
    _methods.put ("getNextMessage", new java.lang.Integer (9));
    _methods.put ("getPreviousMessage", new java.lang.Integer (10));
    _methods.put ("connectToFather", new java.lang.Integer (11));
    _methods.put ("connectToChild", new java.lang.Integer (12));
    _methods.put ("iterateChilds", new java.lang.Integer (13));
    _methods.put ("publishOnFather", new java.lang.Integer (14));
    _methods.put ("publishChild", new java.lang.Integer (15));
    _methods.put ("publishFather", new java.lang.Integer (16));
    _methods.put ("notifyFather", new java.lang.Integer (17));
    _methods.put ("saveFatherInformation", new java.lang.Integer (18));
    _methods.put ("notifyChildren", new java.lang.Integer (19));
    _methods.put ("saveChildInformation", new java.lang.Integer (20));
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
       case 0:  // VS2/MessageboardServerInterface/getFatherName
       {
         String $result = null;
         $result = this.getFatherName ();
         out = $rh.createReply();
         out.write_string ($result);
         break;
       }


  //MessageBoard hat fatherId-> abruf xml datei auf fathername
       case 1:  // VS2/MessageboardServerInterface/getChildNames
       {
         String $result[] = null;
         $result = this.getChildNames ();
         out = $rh.createReply();
         VS2.array_of_StringHelper.write (out, $result);
         break;
       }

       case 2:  // VS2/MessageboardServerInterface/getMessages
       {
         VS2.MessageData $result[] = null;
         $result = this.getMessages ();
         out = $rh.createReply();
         VS2.array_of_MessageDataHelper.write (out, $result);
         break;
       }

       case 3:  // VS2/MessageboardServerInterface/setHighlightedMessage
       {
         String messageID = in.read_string ();
         VS2.MessageData $result = null;
         $result = this.setHighlightedMessage (messageID);
         out = $rh.createReply();
         VS2.MessageDataHelper.write (out, $result);
         break;
       }

       case 4:  // VS2/MessageboardServerInterface/getHighlightedMessage
       {
         VS2.MessageData $result = null;
         $result = this.getHighlightedMessage ();
         out = $rh.createReply();
         VS2.MessageDataHelper.write (out, $result);
         break;
       }

       case 5:  // VS2/MessageboardServerInterface/getMessageWithId
       {
         String messageID = in.read_string ();
         VS2.MessageData $result = null;
         $result = this.getMessageWithId (messageID);
         out = $rh.createReply();
         VS2.MessageDataHelper.write (out, $result);
         break;
       }

       case 6:  // VS2/MessageboardServerInterface/setMessage
       {
         String message = in.read_string ();
         String messageID = in.read_string ();
         int uid = in.read_long ();
         String uName = in.read_string ();
         boolean $result = false;
         $result = this.setMessage (message, messageID, uid, uName);
         out = $rh.createReply();
         out.write_boolean ($result);
         break;
       }

       case 7:  // VS2/MessageboardServerInterface/deleteMessage
       {
         int uid = in.read_long ();
         String messageID = in.read_string ();
         boolean $result = false;
         $result = this.deleteMessage (uid, messageID);
         out = $rh.createReply();
         out.write_boolean ($result);
         break;
       }

       case 8:  // VS2/MessageboardServerInterface/createNewMessage
       {
         String message = in.read_string ();
         int uid = in.read_long ();
         String uName = in.read_string ();
         boolean $result = false;
         $result = this.createNewMessage (message, uid, uName);
         out = $rh.createReply();
         out.write_boolean ($result);
         break;
       }

       case 9:  // VS2/MessageboardServerInterface/getNextMessage
       {
         VS2.MessageData $result = null;
         $result = this.getNextMessage ();
         out = $rh.createReply();
         VS2.MessageDataHelper.write (out, $result);
         break;
       }

       case 10:  // VS2/MessageboardServerInterface/getPreviousMessage
       {
         VS2.MessageData $result = null;
         $result = this.getPreviousMessage ();
         out = $rh.createReply();
         VS2.MessageDataHelper.write (out, $result);
         break;
       }

       case 11:  // VS2/MessageboardServerInterface/connectToFather
       {
         VS2.ConnectInformationData $result = null;
         $result = this.connectToFather ();
         out = $rh.createReply();
         VS2.ConnectInformationDataHelper.write (out, $result);
         break;
       }


  //Liefert die Connectinformationen des Fathers
       case 12:  // VS2/MessageboardServerInterface/connectToChild
       {
         String childName = in.read_string ();
         VS2.ConnectInformationData $result = null;
         $result = this.connectToChild (childName);
         out = $rh.createReply();
         VS2.ConnectInformationDataHelper.write (out, $result);
         break;
       }


  //Liefert die ConnectInformationen des Childs
       case 13:  // VS2/MessageboardServerInterface/iterateChilds
       {
         String message = in.read_string ();
         String messageID = in.read_string ();
         int uid = in.read_long ();
         String uName = in.read_string ();
         boolean schalter = in.read_boolean ();
         boolean $result = false;
         $result = this.iterateChilds (message, messageID, uid, uName, schalter);
         out = $rh.createReply();
         out.write_boolean ($result);
         break;
       }


  //Die Nachricht auf allen Kindern veröffentlichen, extra Schalter um auf allen Kindes Kindern zu veröffentlichen?
       case 14:  // VS2/MessageboardServerInterface/publishOnFather
       {
         String message = in.read_string ();
         String messageID = in.read_string ();
         int uid = in.read_long ();
         String uName = in.read_string ();
         boolean $result = false;
         $result = this.publishOnFather (message, messageID, uid, uName);
         out = $rh.createReply();
         out.write_boolean ($result);
         break;
       }


  //********** zur Kommunikation zwischen Servern(Spezialfälle, daher notwendig) muss nicht in den Client rein ************************
       case 15:  // VS2/MessageboardServerInterface/publishChild
       {
         String message = in.read_string ();
         int uid = in.read_long ();
         String uName = in.read_string ();
         boolean schalter = in.read_boolean ();
         boolean $result = false;
         $result = this.publishChild (message, uid, uName, schalter);
         out = $rh.createReply();
         out.write_boolean ($result);
         break;
       }


  //veröffentliche Nachricht auf Kinderboards
       case 16:  // VS2/MessageboardServerInterface/publishFather
       {
         String message = in.read_string ();
         int uid = in.read_long ();
         String uName = in.read_string ();
         boolean $result = false;
         $result = this.publishFather (message, uid, uName);
         out = $rh.createReply();
         out.write_boolean ($result);
         break;
       }


  //Veröffentlich Nachricht auf Vaterboard
       case 17:  // VS2/MessageboardServerInterface/notifyFather
       {
         this.notifyFather ();
         out = $rh.createReply();
         break;
       }


  //gebe dem Vater bescheid das du jetzt ein Kind von ihm bist
       case 18:  // VS2/MessageboardServerInterface/saveFatherInformation
       {
         int id = in.read_long ();
         String name = in.read_string ();
         VS2.ConnectInformationData ciData = VS2.ConnectInformationDataHelper.read (in);
         this.saveFatherInformation (id, name, ciData);
         out = $rh.createReply();
         break;
       }

       case 19:  // VS2/MessageboardServerInterface/notifyChildren
       {
         this.notifyChildren ();
         out = $rh.createReply();
         break;
       }


  //gebe den Kindern bescheid das du jetzt der Vater bist
       case 20:  // VS2/MessageboardServerInterface/saveChildInformation
       {
         int id = in.read_long ();
         String name = in.read_string ();
         VS2.ConnectInformationData ciData = VS2.ConnectInformationDataHelper.read (in);
         this.saveChildInformation (id, name, ciData);
         out = $rh.createReply();
         break;
       }

       default:
         throw new org.omg.CORBA.BAD_OPERATION (0, org.omg.CORBA.CompletionStatus.COMPLETED_MAYBE);
    }

    return out;
  } // _invoke

  // Type-specific CORBA::Object operations
  private static String[] __ids = {
    "IDL:VS2/MessageboardServerInterface:1.0"};

  public String[] _all_interfaces (org.omg.PortableServer.POA poa, byte[] objectId)
  {
    return (String[])__ids.clone ();
  }

  public MessageboardServerInterface _this() 
  {
    return MessageboardServerInterfaceHelper.narrow(
    super._this_object());
  }

  public MessageboardServerInterface _this(org.omg.CORBA.ORB orb) 
  {
    return MessageboardServerInterfaceHelper.narrow(
    super._this_object(orb));
  }


} // class MessageboardServerInterfacePOA
