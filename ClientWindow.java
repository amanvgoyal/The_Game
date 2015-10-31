// Source :http://aden-tech.com/blog/?p=705
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

public class ClientWindow extends JFrame {

    private JPanel contentPane;
    private JTextField txtOutMsg;
    private Socket client;
    private JLabel statusLabel;
    private OutputStreamWriter osw;

    /**
     * Launch the application.
     */
    public static void main(String[] args) {
	final String serverName = args[0];
	final int port = Integer.parseInt(args[1]);
	EventQueue.invokeLater(new Runnable() {
		public void run() {
		    try {
			ClientWindow frame = new ClientWindow(serverName ,port);
			frame.setVisible(true);
		    } catch (Exception e) {
			e.printStackTrace();
		    }}});
    }

    public LoginWindow() {

    }

    /**
     * Create the frame.
     */
    public ClientWindow(String serverName, int port) {
	final String temp = serverName;
	final int num = port;
	setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
	setBounds(100, 100, 636, 160);
	contentPane = new JPanel();
	contentPane.setBorder(new EmptyBorder(5, 5, 5, 5));
	setContentPane(contentPane);
	contentPane.setLayout(null);
	txtOutMsg = new JTextField();
	txtOutMsg.setText("password");
	txtOutMsg.setBounds(10, 21, 480, 20);
	contentPane.add(txtOutMsg);
	txtOutMsg.setColumns(10);
	try {
	    //Client gets started Here
	    client = new Socket(temp, num);//Temp is ServerName, num is Port
	    //osw is what it sends to the server
	    osw = new OutputStreamWriter(client.getOutputStream());
	} catch (UnknownHostException e) {
	    e.printStackTrace();
	} catch (IOException e) {
	    e.printStackTrace();
	}
	try {
	    //Expecting inital Password Request from Server
	    BufferedReader in = new BufferedReader(new InputStreamReader(client.getInputStream()));
	    BufferedReader br = new BufferedReader(in);
	    char[] buffer = new char[300];
	    int count = br.read(buffer, 0, 300);
	    String reply = new String(buffer, 0, count);
	    System.out.println("Server:"+reply);
	} catch (IOException e1) {
	    e1.printStackTrace();
	}
	JButton btnSend = new JButton("Send");

	btnSend.addActionListener(new ActionListener() {

		public void actionPerformed(ActionEvent e) {
             
		    try {
			// sending output to server
			System.out.print("Client:"+txtOutMsg.getText().toString() + "\n");
			osw.write(txtOutMsg.getText().toString() + "\n");
			osw.flush();

			try {
			    //Sleep for 5 Seconds
			    Thread.sleep(5000);
			}
			catch(InterruptedException ex) {
			    Thread.currentThread().interrupt();
			}
p
			//Recieving Input from Server
			BufferedReader in = new BufferedReader(new InputStreamReader(client.getInputStream()));
			BufferedReader br = new BufferedReader(in);
			char[] buffer = new char[1000];
			int count = br.read(buffer, 0, 1000);
			String reply = new String(buffer, 0, count);
			System.out.println("Server:"+reply);
		    } catch (IOException e1) {
			e1.printStackTrace();
		    }}});

	btnSend.setBounds(10, 52, 131, 45);
	contentPane.add(btnSend);

    }
}
