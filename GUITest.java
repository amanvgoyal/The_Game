/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package boardgui;
import javax.swing.JFrame;
import javax.swing.SwingUtilities;

/**
 *
 * @author ovidio
 */
public class GUITest {
    private static final BoardGUI bgui = new BoardGUI();
    
    public static void main(String[] args) throws InterruptedException {
        //gui.main(null);
        //gui.openGUI();
        Runnable r = new Runnable() {
            @Override
            public void run() {
                JFrame f = new JFrame("Breakthrough");
                f.add(bgui.getGUI());
                f.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
                f.setLocationByPlatform(true);
                f.pack();           // sets the window to the minimum required size
                f.setMinimumSize(f.getSize());
                f.setVisible(true);
            }
        };

        SwingUtilities.invokeLater(r);
        bgui.sendInput("OK");
        // send a board configuration to see if it gets drawn
        String boardInit = 
                  "Current turn number: 1\t\tWhite player's turn\n\n\n"
                + "     A B C D E F G H\n"
                + "     _ _ _ _ _ _ _ _\n"
                + "  8 |X|X|X|X|X|X|X|X|\n"
                + "  7 |X|X|X|X|X|X|X|X|\n"
                + "  6 |_|_|_|_|_|_|_|_|\t\tYour total number of pieces:  16\n"
                + "  5 |_|_|_|_|_|_|_|_|\t\tEnemy total number of pieces: 16\n"
                + "  4 |_|_|_|_|_|_|_|_|\n"
                + "  3 |_|_|_|_|_|_|_|_|\n"
                + "  2 |O|O|O|O|O|O|O|O|\n"
                + "  1 |O|O|O|O|O|O|O|O|\n"
                + "\n";
        bgui.sendInput(boardInit);
        Thread TOut = new Thread(new Runnable() {
            public void run() {
                viewOutput();
            }
        });
        TOut.start();

        bgui.sendInput("ILLEGAL");
        //TOut.start();
        bgui.sendInput("RANDOM INPUT");
        String boardState2 = 
                  "Current turn number: 1\t\tWhite player's turn\n\n\n"
                + "     A B C D E F G H\n"
                + "     _ _ _ _ _ _ _ _\n"
                + "  8 |X|X|X|X|X|X|X|X|\n"
                + "  7 |X|X|X|X|X|X|X|X|\n"
                + "  6 |_|_|_|_|_|_|_|_|\t\tYour total number of pieces:  16\n"
                + "  5 |_|_|_|_|_|_|_|_|\t\tEnemy total number of pieces: 16\n"
                + "  4 |_|_|_|_|_|_|_|_|\n"
                + "  3 |_|O|_|_|_|_|_|_|\n"
                + "  2 |O|_|O|O|O|O|O|O|\n"
                + "  1 |O|O|O|O|O|O|O|O|\n"
                + "\n";
        bgui.sendInput(boardState2);
        TOut.join();
        Thread TOut2 = new Thread(new Runnable() {
            public void run() {
                viewOutput();
            }
        });
        TOut2.start();
    }
    
    public static void viewOutput() {
        String out = bgui.getOutput();
        while(out.equals("")) {
            System.out.println("Waiting for output");
            out = bgui.getOutput();
        }
        System.out.println("\"" + out + "\" command sent.");
    }
}
