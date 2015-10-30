import java.awt.FlowLayout;
import javax.swing.*;
import java.awt.event.*;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;
import javax.imageio.ImageIO;

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
