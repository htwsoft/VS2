/**
 * Created by E.E on 25.01.2017.
 */


//import Controller_eingaben.*;
import View_GUI.*;

public class Start
{
    public String user;

    public static void main(String[] args)
    {
        boolean sichtbar = true;

        Login loginView = new Login();
        loginView.sichtbar(sichtbar);

       // Tafel a = new Tafel();
        //a.sichtbar(sichtbar);

    }
}