package Model_daten;

/**
 * Created by Fuse on 25.01.2017.
 */
public class ModelDaten
{
    private String user;

//    public boolean writeUser(String user)
//    {
//        user = user;
//        return false;
//    }

    public void writeUser(String benutzer)
    {
        user = benutzer;
        //notifyObservers();
    }

    public String getUser()
    {
        return user;
    }
}
