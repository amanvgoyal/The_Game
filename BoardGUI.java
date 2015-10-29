/*
 ************************************************************************
**    BoardGUI.java    ***************************************************
**  This class will draw the board inside a window and provide controls **
**  for controlling the flow of the game.                               **
 ************************************************************************
*/
/*
 ************************************************************************
**    Imports    *********************************************************
 ************************************************************************
*/
import java.awt.*;
import java.awt.event.*;
import java.awt.image.BufferedImage;
import javax.swing.*;
import javax.swing.border.*;
import javax.imageio.ImageIO;

/*
 ************************************************************************
**    BoardGUI    ********************************************************
 ************************************************************************
 ************************************************************************
**    Reference    *******************************************************
**  GUI code based on code from stackoverflow question:                 **
**  "Making a robust, resizable Swing Chess GUI [closed]                **
**  URL: http://stackoverflow.com/questions/21142686/making-a-robust-   **
**       resizable-swing-chess-gui                                      **
 ************************************************************************
*/
public class BoardGUI {
    private final JPanel gui = new JPanel(new BorderLayout(3, 3));
    private JButton[][] boardSquares = new JButton[8][8];
    private Image blackPiece;
    private Image whitePiece;
    private JPanel board;
    private JLabel currentPlayerTurn = new JLabel("No game has started.");
    private JLabel numWhitePieces = new JLabel("White pieces: 0");
    private JLabel numBlackPieces = new JLabel("Black pieces: 0");
    private String output = "";
    private String input = "";

    BoardGUI() {
        initializeGUI();
    }
    
    public final String outputString() {
        return output;
    }

    public final void initializeGUI()
    {   // render the window
        createPieces();
        gui.setBorder(new EmptyBorder(5, 5, 5, 5));
        JToolBar tools = new JToolBar();
        tools.setFloatable(false);
        gui.add(tools, BorderLayout.PAGE_START);
        Action newGameAction = new AbstractAction("New Game") {
            @Override
            public void actionPerformed(ActionEvent e) {
                output = "NEW GAME";            // TODO: change this to correct value
                setupGame();
            }
        };
        
        Action quitAction = new AbstractAction("Quit") {
            @Override
            public void actionPerformed(ActionEvent e) {
                System.exit(0);
            }
        };
        
        Action showMovesAction = new AbstractAction("Show moves") {
            @Override
            public void actionPerformed(ActionEvent e) {
                output = "SHOW";
            }
        };
        
        Action undoAction = new AbstractAction("Undo") {
            @Override
            public void actionPerformed(ActionEvent e) {
                output = "UNDO";
            }
        };

        // add the menu at the top part of the window
        tools.add(newGameAction);
        tools.add(quitAction);
        tools.addSeparator();
        tools.add(showMovesAction);
        tools.add(undoAction);
        tools.addSeparator();
        tools.add(currentPlayerTurn);
        tools.addSeparator();
        tools.add(numWhitePieces);
        tools.addSeparator();
        tools.add(numBlackPieces);

        gui.add(new JLabel("?"), BorderLayout.LINE_START);

        board = new JPanel(new GridLayout(0, 9)) {
            @Override
            public final Dimension getPreferredSize() {
                Dimension d = super.getPreferredSize();
                Dimension prefSize = null;
                Component c = getParent();
                if (c == null) {
                    prefSize = new Dimension((int)d.getWidth(), (int)d.getHeight());
                }
                else if (c != null && c.getWidth() > d.getWidth() && c.getHeight() > d.getHeight()) {
                    prefSize = c.getSize();
                }
                else {
                    prefSize = d;
                }
                int w = (int) prefSize.getWidth();
                int h = (int) prefSize.getHeight();
                int s = w > h ? h : w;
                return new Dimension(s, s);
            }
        };

        board.setBorder(new CompoundBorder(new EmptyBorder(8, 8, 8, 8), new LineBorder(Color.BLACK)));
        // set the background of the board to be maroon
        Color maroon = new Color(80, 0, 0);
        board.setBackground(maroon);
        JPanel boardConstrain = new JPanel(new GridBagLayout());
        boardConstrain.setBackground(maroon);
        boardConstrain.add(board);
        gui.add(boardConstrain);

        // create the board squares
        Insets buttonMargin = new Insets(0, 0, 0, 0);
        for (int i = 0; i < boardSquares.length; ++i) {
            for (int j = 0; j < boardSquares[i].length; ++ j) {
                JButton b = new JButton();
                b.setMargin(buttonMargin);
                // make space 64x64 large
                ImageIcon piece = new ImageIcon(new BufferedImage(64, 64, BufferedImage.TYPE_INT_ARGB));
                b.setIcon(piece);
                b.setBackground(Color.DARK_GRAY);
                boardSquares[i][j] = b;
            }
        }
        // fill the board with the spaces
        board.add(new JLabel(""));
        char columnLabel = 'A';
        int rowLabel = 1;
        for (int i = 0; i < 8; ++i) {
            JLabel cLabel = new JLabel("" + (char)(columnLabel + i), SwingConstants.CENTER);
            cLabel.setForeground(Color.WHITE);
            board.add(cLabel);
        }
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                switch (j) {
                    case 0:
                        JLabel rLabel = new JLabel("" + (8 - i), SwingConstants.CENTER);
                        rLabel.setForeground(Color.WHITE);
                        board.add(rLabel);
                    default:
                        board.add(boardSquares[i][j]);
                }
            }
        }
    }

    public final JComponent getGUI() {
        return gui;
    }

    private final void createPieces() {
        BufferedImage whiteCircle = new BufferedImage(64, 64, BufferedImage.TYPE_INT_ARGB);
        BufferedImage blackCircle = new BufferedImage(64, 64, BufferedImage.TYPE_INT_ARGB);
        Graphics2D gW = whiteCircle.createGraphics();
        Graphics2D gB = blackCircle.createGraphics();
        
        gW.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);
        gW.setRenderingHint(RenderingHints.KEY_RENDERING, RenderingHints.VALUE_RENDER_QUALITY);
        gW.setColor(Color.WHITE);
        gW.fillOval(0, 0, 64, 64);
        gW.drawImage(whiteCircle, 0, 0, null);
        gB.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);
        gB.setRenderingHint(RenderingHints.KEY_RENDERING, RenderingHints.VALUE_RENDER_QUALITY);
        gB.setColor(Color.BLACK);
        gB.fillOval(0, 0, 64, 64);
        gB.drawImage(blackCircle, 0, 0, null);

        blackPiece = blackCircle;
        whitePiece = whiteCircle;
    }
    
    private final void setupGame() {
        currentPlayerTurn.setText("White player's turn");
        numWhitePieces.setText("White pieces: 16");
        numBlackPieces.setText("Black pieces: 16");
        // set up the pieces
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                if (i == 0 || i == 1) {
                    // add the black pieces
                    boardSquares[i][j].setIcon(new ImageIcon(blackPiece));
                }
                else if (i == 6 || i == 7) {
                    // add the white pieces
                    boardSquares[i][j].setIcon(new ImageIcon(whitePiece));
                }
            }
        }
    }
    
    public static void main(String[] args) {
        Runnable r = new Runnable() {
            @Override
            public void run() {
                BoardGUI bgui = new BoardGUI();
                
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
    }
}
