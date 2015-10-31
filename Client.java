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
    public static void main(String s[]) throws IOException{
	// Resources
	File f = new File("logo.png");
	BufferedImage img = ImageIO.read(f);
	JLabel dispImg = new JLabel(new ImageIcon(img));
	
	final JFrame frame = new JFrame("b0ss Breakthrough client");

	JPanel panel = new JPanel();
	panel.setLayout(new FlowLayout());

	JLabel passLabel = new JLabel("Password: ");
	final JPasswordField passField = new JPasswordField(10);
	passLabel.setLabelFor(passField);

	JButton login = new JButton("Login");
        login.addActionListener(new ActionListener() {
		public void actionPerformed(ActionEvent e) {
		    String password = new String(passField.getPassword());
		    if (password.equals("password")) {
			    JOptionPane.showMessageDialog(frame,"Welcome.");
			    // Further logic...
			    
		    }
		
			else {
			    JOptionPane.showMessageDialog(frame, "Try again.");
			}
		}
	    });


	panel.add(passLabel);
	panel.add(passField);
	panel.add(login);
	panel.add(dispImg);

	frame.add(panel);
	frame.setSize(640, 480);
	frame.setLocationRelativeTo(null);
	frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
	frame.setVisible(true);

    }

}
