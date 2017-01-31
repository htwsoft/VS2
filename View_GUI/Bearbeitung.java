package View_GUI;

import Model_daten.*;

import javax.swing.*;
import java.awt.event.*;

/**
 * Created by Amel on 24.01.2017.
 */
public class Bearbeitung extends JDialog
{

    private JComboBox comboBox1;
    private JButton ändernButton;
    private JButton löschenButton;
    private JButton abbrechenButton;
    private JPanel bearbeitungPanel;
    private JTextArea nachrichtenArea;

    JFrame frame = new JFrame("Bearbeitung");

    public Bearbeitung()
    {
        erstellen();

        abbrechenButton.addActionListener(new ActionListener()
        {
            public void actionPerformed(ActionEvent e)
            {
                onAbbrechen();
            }
        });

    }


    public void erstellen()
    {
        frame.setContentPane(bearbeitungPanel);
        frame.setLocation(800, 0);
        frame.pack();
        frame.setSize(700, 500);
        frame.setVisible(true);
    }

    private void onAbbrechen()
    {
        frame.dispose();
    }

}