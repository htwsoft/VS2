package Controller_eingaben;

import Model_daten.ModelDaten;

/**
 * Created by Fuse on 25.01.2017.
 */
public class LoginController
{
    public void setUser(String user)
    {
        try
        {
            ModelDaten model = new ModelDaten();
            model.writeUser(user);
            //return model.writeUser(user);
        } catch (Exception er) {
            //return false;
        }
    }

    public String getUser()
    {
        try
        {
            ModelDaten model = new ModelDaten();
            return model.getUser();
        } catch (Exception er) {
            return "Fehler aufgetreten.";
        }
    }

}
