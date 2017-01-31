package View_GUI;

import Controller_eingaben.LoginController;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

/**
 * Created by Fuse on 25.01.2017.
 */
public class Login extends javax.swing.JFrame
{
    JFrame m_viewFrame = new JFrame("Bitte Daten eingeben");
    JMenuBar m_menuBar;
    JTextField userTextFeld;
    JPasswordField pwTextFeld;
    JButton m_setButton;
    JLabel m_errorLabel;

    public String user;

    // Create the class for the Controller
    private LoginController controller = new LoginController();

    public Login ()
    {
        erstellen();
    }

    public void erstellen()
    {
        //m_viewFrame = new JFrame("Bitte Daten eingeben");
        m_viewFrame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        m_menuBar = new JMenuBar();
        m_viewFrame.setJMenuBar(m_menuBar);

        JPanel northPanel = new JPanel(new BorderLayout());
        m_viewFrame.getContentPane().add(northPanel,BorderLayout.NORTH);

        Box b1 = Box.createVerticalBox();
        Box b2 = Box.createVerticalBox();

        b1.add(new Label("htw", Label.CENTER));
        b2.add(new Label("Anzeige-Tafel",Label.CENTER));

        b1.add(new Label("Benutzer: ", Label.RIGHT));
        userTextFeld = new JTextField();
        userTextFeld.setHorizontalAlignment(JTextField.CENTER);
        b2.add(userTextFeld);

        b1.add(new Label("Password: ", Label.RIGHT));
        pwTextFeld = new JPasswordField();
        pwTextFeld.setHorizontalAlignment(JTextField.CENTER);
        b2.add(pwTextFeld);

        northPanel.add(b1,BorderLayout.WEST);
        northPanel.add(b2,BorderLayout.CENTER);
        m_errorLabel = new JLabel("",JLabel.CENTER);
        northPanel.add(m_errorLabel, BorderLayout.SOUTH);


        m_setButton = new JButton ("Login");
        m_setButton.addActionListener (new ActionListener(){
            public void actionPerformed (ActionEvent e)
            {
                user = userTextFeld.getText();
                System.out.println(user);
                //Controller benachrichtigen, noch nicht umgesetzt
                controller.setUser(user);

                //Sobald eingeloggt schließt das Fesnter
                m_viewFrame.setVisible(false);

                Tafel b = new Tafel(user);
                b.sichtbar(true);
            }
        });

        JPanel buttonPanel = new JPanel();
        m_viewFrame.getContentPane().add(buttonPanel,BorderLayout.SOUTH);
        buttonPanel.add(m_setButton);

        // Position setzen
        Dimension d = Toolkit.getDefaultToolkit().getScreenSize();
        m_viewFrame.setLocation((d.width - m_viewFrame.getSize().width) / 2,
                (d.height - m_viewFrame.getSize().height) / 2);


        m_viewFrame.setSize(400, 150);

        // JFrame anzeigen
        //m_viewFrame.setVisible(true);
    }

    public void sichtbar(boolean a)
    {
        if (a = true)
        {
            m_viewFrame.setVisible(true);
        }
    }


}
