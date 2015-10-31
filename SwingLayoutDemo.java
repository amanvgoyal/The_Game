import java.awt.*;
import javax.swing.*;
import java.awt.event.*;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;
import javax.imageio.ImageIO;
import java.awt.BorderLayout;
import java.awt.EventQueue;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.border.EmptyBorder;
import javax.swing.JTextField;
import javax.swing.JButton;
import javax.swing.JTextArea;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import java.io.BufferedOutputStream;
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.io.OutputStreamWriter;
import java.net.Socket;
import java.io.InputStreamReader;
import java.net.UnknownHostException;

public class SwingLayoutDemo {
    private JFrame mainFrame;
    //private JLabel headerLabel;
    private JLabel statusLabel;
    private JPanel controlPanel;
    private JLabel msglabel;

    public SwingLayoutDemo(){
	prepareGUI();
    }

    public static void main(String[] args) throws IOException{
	SwingLayoutDemo swingLayoutDemo = new SwingLayoutDemo();  
	swingLayoutDemo.showCardLayoutDemo();       
    }
      
    private void prepareGUI(){
	mainFrame = new JFrame("b0ss Breakthrough Client");
	mainFrame.setSize(400,400);
	mainFrame.setLayout(new GridLayout(3, 1));

	//headerLabel = new JLabel("",JLabel.CENTER );
	statusLabel = new JLabel("",JLabel.CENTER);        

	statusLabel.setSize(350,100);
	mainFrame.addWindowListener(new WindowAdapter() {
		public void windowClosing(WindowEvent windowEvent){
		    System.exit(0);
		}        
	    });    
	controlPanel = new JPanel();
	controlPanel.setLayout(new FlowLayout());

	//	mainFrame.add(headerLabel);
	mainFrame.add(controlPanel);
	mainFrame.add(statusLabel);
	mainFrame.setVisible(true);  
    }
   
    private void showCardLayoutDemo(){
	//headerLabel.setText("Layout in action: CardLayout");      

	final JPanel panel = new JPanel();
	panel.setBackground(Color.CYAN);
	panel.setSize(640, 480);

	CardLayout layout = new CardLayout();
	layout.setHgap(10);
	layout.setVgap(10);
	panel.setLayout(layout);        

	JPanel buttonPanel = new JPanel(new FlowLayout());

	//buttonPanel.add(new JButton("OK"));
	//buttonPanel.add(new JButton("Cancel"));    
	JButton gTypeBtn1 = new JButton("Human - AI");
        gTypeBtn1.addActionListener(new ActionListener() {
                public void actionPerformed(ActionEvent e) {
		    JOptionPane.showMessageDialog(mainFrame,"Human-AI Chosen");
		}
            });
	    
	JButton gTypeBtn2 = new JButton("AI - AI");
        gTypeBtn2.addActionListener(new ActionListener() {
                public void actionPerformed(ActionEvent e) {
		    JOptionPane.showMessageDialog(mainFrame,"AI-AI Chosen");
		}
            });

	buttonPanel.add(gTypeBtn1);
	buttonPanel.add(gTypeBtn2);

	JPanel textBoxPanel = new JPanel(new FlowLayout());

	//textBoxPanel.add(new JLabel("Password: "));
	//textBoxPanel.add(new JTextField(20));
	JLabel passLabel = new JLabel("Password: ");
	final JPasswordField passField = new JPasswordField(10);
	textBoxPanel.add(passLabel);
	textBoxPanel.add(passField);

	//	panel.add("Button", buttonPanel);
	panel.add("Text", textBoxPanel);
	panel.add("Button", buttonPanel);

	//final DefaultComboBoxModel panelName = new DefaultComboBoxModel();

	//panelName.addElement("Text");
	//panelName.addElement("Button");
      
	//final JComboBox listCombo = new JComboBox(panelName);    
	//listCombo.setSelectedIndex(0);

	//JScrollPane listComboScrollPane = new JScrollPane(listCombo);    

	JButton loginButton = new JButton("Login");
        loginButton.addActionListener(new ActionListener() {
                public void actionPerformed(ActionEvent e) {
                    String password = new String(passField.getPassword());
                    if (password.equals("password")) {
			JOptionPane.showMessageDialog(mainFrame,"Welcome.");
			CardLayout cardLayout = (CardLayout)(panel.getLayout());
			cardLayout.show(panel, "Button");
                    }

		    else {
			JOptionPane.showMessageDialog(mainFrame, "Try again.");
		    }
		}
            });

	/*JButton showButton = new JButton("Show");

	showButton.addActionListener(new ActionListener() {
		public void actionPerformed(ActionEvent e) { 
		    String data = "";
		    if (listCombo.getSelectedIndex() != -1) {  
			CardLayout cardLayout = (CardLayout)(panel.getLayout());
			cardLayout.show(panel, 
					(String)listCombo.getItemAt(listCombo.getSelectedIndex()));               
		    }              
		    statusLabel.setText(data);
		}
	    }); 
	*/
	//controlPanel.add(listComboScrollPane);
	controlPanel.add(loginButton);
	//	controlPanel.add(showButton);
	controlPanel.add(panel);

	mainFrame.setVisible(true);  
    }
}
