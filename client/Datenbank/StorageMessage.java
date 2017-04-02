package Datenbank;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.sql.Timestamp;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Iterator;

import Datenbank.dbInfo.Fkt;

public class StorageMessage {
	// Datenbank daten
	final static String DBNAME = "MessageDB.db";
	final static String JDBC = "jdbc:sqlite:";
	final static String URLDB = JDBC + DBNAME;
	final static String TABELNAME = "message";
	// Spalten Name
	final static int anzahlSpalte=9;
	final static String SPALTEID = "ID";
	final static String SPALTEUUID = "UID";
	final static String SPALTEIDNACHRICHT= "IDNachricht";
	final static String SPALTEUSERNAME = "Username";
	final static String SPALTEPASSWORD = "Password";
	final static String SPALTESERVER = "Server";
	final static String SPALTESISADMIN = "IstAdmin";
	final static String SPALTESISSHARED = "IsShared";
	final static String SPALTEMESSAGE = "Message";
	final static String SPALTEFKT="Funktion";
	final static String SPALTEDATUM = "Datum";

	static Connection connDB;
	static Statement state;
	static int id;
	static ResultSet rs;

	// ARRAY fuer komplette auslesen der DB
	ArrayList<String[]> array = new ArrayList<String[]>();

	public StorageMessage(){
		startStorage();
	}
	// Starten von der DB und verbinden
	private boolean startStorage() {
		try {
			// Diver registrieren
			String sDriverName = "org.sqlite.JDBC";
			Class.forName(sDriverName);
			// DB verbinden
			connDB = DriverManager.getConnection(URLDB);
			erstellenVonTabelle();
			state.executeQuery("SELECT * FROM " + TABELNAME + " ORDER BY " + SPALTEID + " ASC");

			return true;
		} catch (ClassNotFoundException e) {
			// e.printStackTrace();
			return false;

		} catch (SQLException e) {
			// e.printStackTrace();
			return false;
		}

	}

	// Erstellen von Tabelle wenn nicht Vorhanden
	private static void erstellenVonTabelle() {
		try {
			state = connDB.createStatement();
			// Tabelle mit name "Message"
			state.executeUpdate("CREATE TABLE " + TABELNAME + " (" + SPALTEID + " numeric," +SPALTEIDNACHRICHT+ " text," +SPALTEUUID + " numeric,"
					+ SPALTEUSERNAME + " text,"+ SPALTEPASSWORD + " text," +SPALTESERVER  + " text," +SPALTESISADMIN+" numeric," +SPALTESISSHARED+" numeric,"+
					SPALTEMESSAGE + " text," + SPALTEDATUM + " date,"+ SPALTEFKT +" text"+")");
		} catch (SQLException e) {
			// e.printStackTrace();
		}
	}

	public boolean deleteEintrag( int deletid) {
		try {
			// SCHAUEN OB DB LEER IST
			if (checkDBisLeer()) {
				if ((state.executeUpdate("DELETE FROM " + TABELNAME + " WHERE " + SPALTEID + "=" + deletid)) == 1) {
					// SOTIERT DIE ID nach LOSCHEN
					sortieren(deletid);
					return true;
				} else {
					// System.out.println("Loeschen ist schief gelaufen!");
					return false;
				}
			}
			return false;
		} catch (SQLException e) {
			// e.printStackTrace();
			return false;

		}
	}

	public void sortieren(int geloeschteID) throws SQLException {
		int iidalt = geloeschteID + 1;
		int iidneu = geloeschteID;

	
		int idmax = getMAX(SPALTEID);
		if (geloeschteID <= idmax) {

			do {

				state.executeUpdate("UPDATE " + TABELNAME + " SET " + SPALTEID + " =" + iidneu + " WHERE " + SPALTEID
						+ " =" + iidalt);

				iidalt++;
				iidneu++;
			} while (iidalt <= idmax);

		}

	}

	public  synchronized ArrayList<String> readEintrag (int stelle){
		try {
//			int iter=0;
			ArrayList<String> eintrag=new ArrayList<String>();
			
		
			rs= state.executeQuery("SELECT * FROM "+TABELNAME+ " WHERE "+SPALTEID+" >="+stelle);
			System.out.println("SELECT * FROM "+TABELNAME+ " WHERE "+SPALTEID+" >="+stelle);
			for(int i =0;i<anzahlSpalte;++i){
				eintrag.add(rs.getString(i));
			}
				
			return eintrag;
		} catch (SQLException e) {
			// TODO Auto-generated catch block
//			e.printStackTrace();
			return null;
		}
//		return null;
	}
	
	private static int getMAX(String spaltename) {

		String idstring;

		try {
			rs = state.executeQuery("SELECT MAX(" + spaltename + ") AS " + spaltename + " FROM " + TABELNAME);
			if ((idstring = rs.getString(spaltename)) == null) {
				return -1;
			}
			return (Integer.valueOf(idstring));

		} catch (SQLException e) {
			// TODO Auto-generated catch block
			//e.printStackTrace();
			return -1;
		}

	}
	
	public boolean writeEintrag(String idnachricht,int uid ,String username,String password,String server, boolean isAdmin, boolean isShared, String message,Fkt funktion) {
		
		if (!checkMessage(message)) {
			try {
				// GIBT mir den groessten wert von id aus und mit ASC den
				// kleinsten
				
				id = getMAX(SPALTEID);
				id++;
				
				state.executeUpdate("INSERT INTO " + TABELNAME + " VALUES(" + id + ",'"+idnachricht+ "','"+ uid + "','" + username+ "','"+password+"','"+
						server+ "','"+  isAdmin+ "','"+ isShared+"','" + message + "','" + curdate() +  "','"+funktion.toString()+"')");

				return true;
			} catch (SQLException e) {

				 //e.printStackTrace();
				try {
					state.executeUpdate("INSERT INTO " + TABELNAME + " VALUES(" + id + ",'" +idnachricht+ "','"+uid + "','" + username+ "','"+password+"','"+
							server+ "','"+  isAdmin+ "','"+ isShared+"','" + message + "','" + curdate() +"','"+funktion.toString()+ "')");
					
				} catch (SQLException e1) {

					// e1.printStackTrace();
				}

			}
		} else {
			return false;
		}
		return false;
	}

	private static boolean checkDBisLeer() {
		try {
			rs = state.executeQuery("SELECT * FROM " + TABELNAME + " ORDER BY " + SPALTEID + " DESC");
			rs.getString(SPALTEID);

			return true;

		} catch (SQLException e) {
			// TODO Auto-generated catch block
			 //e.printStackTrace();
			//System.out.println("DATENBANK IST LeeR");
			return false;
		}

	}

	// GUCKT ob es eine leerer string ist
	private static boolean checkMessage(String message) {
		if (message.isEmpty()) {
			return true;
		} else {
			return false;
		}
	}

	public static void printDBData() throws SQLException {
		rs = state.executeQuery("SELECT * FROM " + TABELNAME);
		int spalte = rs.getMetaData().getColumnCount();
		String test = "";
		while (rs.next()) {
			for (int i = 1; i <= 5; i++) {
				test += rs.getString(i) + " ";

			}

			System.out.println(test);
			test = "";
		}

	}

	public static int getID() {

		try {
			if (checkDBisLeer()) {
				rs = state.executeQuery("SELECT MAX(" + SPALTEID + ") AS " + SPALTEID + " FROM " + TABELNAME);

				return (Integer.valueOf(rs.getString(SPALTEID)));
			}
			return -1;
		} catch (SQLException e) {
			// TODO Auto-generated catch block

			// e.printStackTrace();
			return -1;
		}

	}

	public static String getEmpfaenger(int iD) {

		try {
			rs = state.executeQuery("SELECT " + SPALTESERVER + " FROM " + TABELNAME + " WHERE " + SPALTEID + "=" + iD);
			return rs.getString(SPALTESERVER);
		} catch (SQLException e) {
			// TODO Auto-generated catch block

			e.printStackTrace();
			return "false";
		}

	}

	public static String getMessage(int iD, String server) {
		try {
			rs = state.executeQuery("SELECT " + SPALTEMESSAGE + " FROM " + TABELNAME + " WHERE " + SPALTEID + "=" + iD
					+ " AND " + SPALTESERVER + "='" + server + "'");
			return rs.getString(SPALTEMESSAGE);
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			// e.printStackTrace();
			return "-1";
		}

	}
	
	public boolean checkDB(String server){
		
		if(checkDBisLeer()){
			try {
				rs = state.executeQuery("SELECT * FROM " + TABELNAME + " WHERE "+ SPALTESERVER + "='" + server + "'");
				
				
				return true;

			} catch (SQLException e) {
				// TODO Auto-generated catch block
				// e.printStackTrace();
				//System.out.println("DATENBANK IST LeeR");
				return false;
			}
		}
		return false;
		
	}

	private static String curdate() {
		SimpleDateFormat sdf = new SimpleDateFormat("dd.MM.yyyy-hh:mm");
		Timestamp time = new Timestamp(System.currentTimeMillis());
		String time1 = sdf.format(time);
		return time1;
	}
	public ArrayList<dbInfo> getMessage(String server) {
		
		ArrayList<dbInfo> tmp= new ArrayList<dbInfo>();
		try {
			
			rs = state.executeQuery("SELECT * FROM " + TABELNAME + " WHERE "+ SPALTESERVER + "='" + server + "'");
			while(rs.next()){
				tmp.add(new dbInfo(rs.getString(SPALTEIDNACHRICHT),rs.getInt(SPALTEUUID),rs.getString(SPALTEUSERNAME),rs.getString(SPALTEPASSWORD), rs.getString(SPALTESERVER), rs.getBoolean(SPALTESISADMIN),  
						rs.getBoolean(SPALTESISSHARED),  rs.getString(SPALTEMESSAGE),Fkt.valueOf(rs.getString(SPALTEFKT))));
			}
			return tmp;
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			//e.printStackTrace();
		}
		
		return null;
	}
}
