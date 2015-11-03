// Modified version of below
// http://www.tutorialspoint.com/swing/swing_springlayout.htm

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

public class Client {
    private JFrame mainFrame;
    private JLabel statusLabel;
    private JPanel controlPanel;
    private JLabel msglabel;

   private static String serverName;
    private static int port;
    
    private Socket clientSock;
    private OutputStreamWriter osw;


    private String AIdiff;

    public Client(){
	try {
	    System.out.println(serverName);
            //Client gets started Here                                             
            clientSock = new Socket(serverName, port);
            //osw is what it sends to the server                                 
	    osw = new OutputStreamWriter(clientSock.getOutputStream());
        } 
	catch (UnknownHostException e) {e.printStackTrace();}
	catch (IOException e) {e.printStackTrace();}

	prepareGUI();
    }

    public static void main(String[] args) throws IOException{
	serverName = args[0];// 
	port = Integer.parseInt(args[1]);//

	Client c = new Client();
	c.showWin();
    }
      
    private void prepareGUI(){
	mainFrame = new JFrame("b0ss Breakthrough Client");
	mainFrame.setSize(400,400);
	mainFrame.setLayout(new GridLayout(3, 1));

	statusLabel = new JLabel("",JLabel.CENTER);        

	statusLabel.setSize(350,100);
	mainFrame.addWindowListener(new WindowAdapter() {
		public void windowClosing(WindowEvent windowEvent){
		    System.exit(0);
		}        
	    });    
	controlPanel = new JPanel();
	controlPanel.setLayout(new FlowLayout());

	mainFrame.add(controlPanel);
	mainFrame.add(statusLabel);
	mainFrame.setVisible(true);  
    }
   
    private void showWin(){
	final JPanel panel = new JPanel();
	Color maroon = new Color(128, 0, 0);
	panel.setBackground(maroon);
	panel.setSize(640, 480);

	CardLayout layout = new CardLayout();
	layout.setHgap(10);
	layout.setVgap(10);
	panel.setLayout(layout);        


	// Screen for choosing game type
	JPanel buttonPanel = new JPanel(new FlowLayout());

	JButton gTypeBtn1 = new JButton("Human - AI");
        gTypeBtn1.addActionListener(new ActionListener() {
                public void actionPerformed(ActionEvent e) {
		    JOptionPane.showMessageDialog(mainFrame,"Human-AI Chosen");
		    CardLayout cardLayout = (CardLayout)(panel.getLayout());
		    cardLayout.show(panel, "Command");
		}
	    });
	    
	JButton gTypeBtn2 = new JButton("AI - AI");
        gTypeBtn2.addActionListener(new ActionListener() {
                public void actionPerformed(ActionEvent e) {
		    JOptionPane.showMessageDialog(mainFrame,"AI-AI Chosen");
		    CardLayout cardLayout = (CardLayout)(panel.getLayout());
		    cardLayout.show(panel, "AIGame");
		}
            });

	buttonPanel.add(gTypeBtn1);
	buttonPanel.add(gTypeBtn2);

	// Screen for entering password to log in 
	JPanel passBoxPanel = new JPanel(new FlowLayout());
	JLabel passLabel = new JLabel("Password: ");

	final JPasswordField passField = new JPasswordField(10);
	passBoxPanel.add(passLabel);
	passBoxPanel.add(passField);

	panel.add("Login", passBoxPanel);
	panel.add("GameType", buttonPanel);

	// Screen for entering commands in Human-AI game
	JPanel cmdBoxPanel = new JPanel(new FlowLayout());
	JLabel cmdLabel = new JLabel("Command: ");
	final JTextField cmdField = new JTextField(20);
	JButton cmdEnter = new JButton("Submit");
	
	cmdEnter.addActionListener(new ActionListener() {
		public void actionPerformed(ActionEvent e) {
		    String cmd = cmdField.getText();
		    JOptionPane.showMessageDialog(mainFrame, cmd);
		}
	    });

	cmdBoxPanel.add(cmdLabel);
	cmdBoxPanel.add(cmdField);
	cmdBoxPanel.add(cmdEnter);

	panel.add("Command", cmdBoxPanel);

	// Screen for choosing AI difficulty
	JPanel AIDiffPanel = new JPanel(new FlowLayout());
	JLabel diffLabel = new JLabel("Enter difficulty: ");
	final JTextField diffField = new JTextField(15);
	JButton diffEnter = new JButton("Submit");
 
        diffEnter.addActionListener(new ActionListener() {
                public void actionPerformed(ActionEvent e) {
		    String diff = diffField.getText();
		    
		    if (diff.equalsIgnoreCase("easy") ||
			diff.equalsIgnoreCase("medium") ||
			diff.equalsIgnoreCase("hard")) {

			AIdiff = diff;
			JOptionPane.showMessageDialog(mainFrame, diff);
			CardLayout cardLayout = (CardLayout)(panel.getLayout());
			cardLayout.show(panel, "GameType");
		    }
		    else {
			JOptionPane.showMessageDialog(mainFrame, "Invalid!");
		    }
		}
            });
	
	AIDiffPanel.add(diffLabel);
	AIDiffPanel.add(diffField);
	AIDiffPanel.add(diffEnter);
	
	panel.add("AIDiff", AIDiffPanel);


	// Screen for AI-AI game
	JPanel AIGamePanel = new JPanel(new FlowLayout());
	JLabel AIGameLabel = new JLabel("AI-AI Game");
	AIGamePanel.add(AIGameLabel);

	panel.add("AIGame", AIGamePanel);

	// Finish making control pannel by adding login button
	final JButton loginButton = new JButton("Login");
        loginButton.addActionListener(new ActionListener() {
                public void actionPerformed(ActionEvent e) {
		    // CAN SEND BELOW TO SERVER IF NEEDED
                    String password = new String(passField.getPassword());
                    if (password.equals("password")) {
			loginButton.setVisible(false);
			JOptionPane.showMessageDialog(mainFrame,"Welcome.");
			CardLayout cardLayout = (CardLayout)(panel.getLayout());
			cardLayout.show(panel, "AIDiff");
                    }

		    else {
			JOptionPane.showMessageDialog(mainFrame, "Try again.");
		    }
		}
            });

	controlPanel.add(loginButton);
	controlPanel.add(panel);

	mainFrame.setVisible(true);  
    }
}
