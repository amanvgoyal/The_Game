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
package boardgui;

import java.awt.*;
import java.awt.event.*;
import java.awt.image.BufferedImage;
import javax.swing.*;
import javax.swing.border.*;
import java.util.logging.Level;
import java.util.logging.Logger;

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
    private final JButton[][] boardSquares = new JButton[8][8];
    private Image blackPiece;
    private Image whitePiece;
    private JPanel board;
    private final JLabel currentPlayerTurn = new JLabel("No game has started.");
    private final JLabel currentTurn = new JLabel("");
    private final JLabel numWhitePieces = new JLabel("White pieces: 0");
    private final JLabel numBlackPieces = new JLabel("Black pieces: 0");
    private final JLabel playerMessage = new JLabel("Press the New Game button to start a new game.");
    private String firstSelectedPiece = "";
    private String output = "";
    //private boolean outputReady = false;
    private boolean gameStarted = false;
    private Object lock;
    private int whitePieces = 0;
    private int blackPieces = 0;

    BoardGUI() {
        initializeGUI();
    }

    public final void sendInput(String input) {
        // check what the input is and generate an output from that
        if ("OK".equals(input)) {
            // wait for move
            gameStarted = true;
            System.out.println("\"OK\" command received.");
        } else if (input.contains("Current turn number:")) {
            // redisplay board
            gameStarted = true;
            System.out.println("Board configuration received.");
            displayBoard(input);
        } else if ("ILLEGAL".equals(input)) {
            // illegal move, must request input again
            System.out.println("\"ILLEGAL\" command received.");
            playerMessage.setText("In move was invalid, please try again.");
        } else {
            System.out.println("Input \"" + input + "\" not recognized!");
        }
    }

    public final String getOutput() {
        String temp = output;
        output = "";
        return temp;
    }

    public final void initializeGUI() {   // render the window
        System.out.println("Initializing GUI.");
        createPieces();
        gui.setBorder(new EmptyBorder(5, 5, 5, 5));
        JToolBar tools = new JToolBar();
        tools.setFloatable(false);
        gui.add(tools, BorderLayout.PAGE_START);
        gui.add(playerMessage, BorderLayout.LINE_START);
        Action newGameAction = new AbstractAction("Reset Board") {
            @Override
            public void actionPerformed(ActionEvent e) {
                output = "NEW GAME";            // TODO: change this to correct value
                //outputReady = true;
                gameStarted = true;
                System.out.println("Setting up a new game.");
                //setupGame();
            }
        };

        Action quitAction = new AbstractAction("Quit") {
            @Override
            public void actionPerformed(ActionEvent e) {
                output = "EXIT";
                //outputReady = true;
                gameStarted = false;
                System.out.println("Quitting game.");
                // send output;
                //System.exit(0);
            }
        };

        Action clearSelectionAction = new AbstractAction("Clear selection") {
            @Override
            public void actionPerformed(ActionEvent e) {
                System.out.println("Clearing selection.");
                firstSelectedPiece = "";
            }
        };

        Action undoAction = new AbstractAction("Undo") {
            @Override
            public void actionPerformed(ActionEvent e) {
                output = "UNDO";
                //outputReady = true;
                System.out.println("Undoing last two turns.");
            }
        };

        // add the menu at the top part of the window
        tools.add(newGameAction);
        tools.add(quitAction);
        tools.addSeparator();
        tools.add(clearSelectionAction);
        tools.add(undoAction);
        tools.addSeparator();
        tools.add(currentTurn);
        tools.addSeparator();
        tools.add(currentPlayerTurn);
        tools.addSeparator();
        tools.add(numWhitePieces);
        tools.addSeparator();
        tools.add(numBlackPieces);

        board = new JPanel(new GridLayout(0, 9)) {
            @Override
            public final Dimension getPreferredSize() {
                Dimension d = super.getPreferredSize();
                Dimension prefSize = null;
                Component c = getParent();
                if (c == null) {
                    prefSize = new Dimension((int) d.getWidth(), (int) d.getHeight());
                } else if (c != null && c.getWidth() > d.getWidth() && c.getHeight() > d.getHeight()) {
                    prefSize = c.getSize();
                } else {
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
        gui.add(boardConstrain, BorderLayout.PAGE_END);

        // create the board squares
        Insets buttonMargin = new Insets(0, 0, 0, 0);
        for (int i = 0; i < boardSquares.length; ++i) {
            for (int j = 0; j < boardSquares[i].length; ++j) {
                JButton b = new JButton();
                final int ii = 7 - i;
                final int jj = j;
                Action selectSpace = new AbstractAction(Integer.toString(i) + Integer.toString(j)) {
                    @Override
                    public void actionPerformed(ActionEvent e) {
                        if (gameStarted) {
                            String space = Integer.toString(ii) + Integer.toString(jj);
                            moveCommand(space);
                        } else {
                            playerMessage.setText("Please start a new game before selecting a piece.");
                        }
                    }
                };
                b.addActionListener(selectSpace);
                b.setActionCommand("Piece " + Integer.toString(i) + Integer.toString(j));
                b.setMargin(buttonMargin);
                // make space 64x64 large
                ImageIcon piece = new ImageIcon(new BufferedImage(64, 64, BufferedImage.TYPE_INT_ARGB));
                b.setIcon(piece);
                b.setBackground(Color.LIGHT_GRAY);
                boardSquares[i][j] = b;
            }
        }
        // fill the board with the spaces
        board.add(new JLabel(""));
        char columnLabel = 'A';
        for (int i = 0; i < 8; ++i) {
            JLabel cLabel = new JLabel("" + (char) (columnLabel + i), SwingConstants.CENTER);
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
                        // boardSquares[i][j].addActionListener(this);
                        // create action command that identifies the space
                        //boardSquares[i][j]
                        board.add(boardSquares[i][j]);
                }
            }
        }
    }

    private void moveCommand(String space) {
        char r = (char) (Character.getNumericValue(space.charAt(0)) + Character.valueOf('1'));
        char c = (char) (Character.getNumericValue(space.charAt(1)) + Character.valueOf('A'));
        System.out.println("Space " + c + r + " selected.");
        if ("".equals(firstSelectedPiece)) {
            // No first piece has been selected, add to this string

            playerMessage.setText("Space " + c + r + " selected.");
            firstSelectedPiece = space;
        } else {
            // First piece has been selected, calculate move direction
            String direction = "";
            int orig_r = Character.getNumericValue(firstSelectedPiece.charAt(0));
            int orig_c = Character.getNumericValue(firstSelectedPiece.charAt(1));
            int move_r = Character.getNumericValue(space.charAt(0));
            int move_c = Character.getNumericValue(space.charAt(1));
            playerMessage.setText("Space " + c + r + " selected.");
            if (orig_r + 1 == move_r) {
                // check if moving forward one row
                if (orig_c == move_c) {
                    direction = "FWD";
                } else if (orig_c + 1 == move_c) {
                    direction = "RIGHT";
                } else if (orig_c - 1 == move_c) {
                    direction = "LEFT";
                } else {
                    // inform user that move is invalid
                    System.out.println("Invalid move!");
                    firstSelectedPiece = "";
                }
            } else {
                // inform user that move is invalid
                System.out.println("Invalid move!");
                firstSelectedPiece = "";
            }
            if (!"".equals(direction)) {
                // valid move was made
                char rr = (char) (Character.getNumericValue(firstSelectedPiece.charAt(0)) + Character.valueOf('1'));
                char cc = (char) (Character.getNumericValue(firstSelectedPiece.charAt(1)) + Character.valueOf('A'));
                output = Character.toString(cc) + Character.toString(rr) + " " + direction;
                //outputReady = true;
                System.out.println("Performing move: " + output);
            }
            firstSelectedPiece = "";
        }
    }

    public final JComponent getGUI() {
        return gui;
    }

    private void createPieces() {
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

    // change this to just display the board resulting from the string received
    // from the server
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
                } else if (i == 6 || i == 7) {
                    // add the white pieces
                    boardSquares[i][j].setIcon(new ImageIcon(whitePiece));
                }
            }
        }
    }

    private void addPiece(int row, int col, char type) {
        if (row >= 0
                && row < boardSquares.length
                && col >= 0
                && col < boardSquares[row].length) {
            switch (type) {
                case 'X': {
                    boardSquares[row][col].setIcon(new ImageIcon(blackPiece));
                    break;
                }
                case 'O': {
                    boardSquares[row][col].setIcon(new ImageIcon(whitePiece));
                    break;
                }
                case '_': {
                    boardSquares[row][col].setIcon(new ImageIcon(new BufferedImage(64, 64, BufferedImage.TYPE_INT_ARGB)));
                    break;
                }
                default: {
                    break;
                }
            }
        }
    }

    private final void displayBoard(String board) {
        // decode string
        /*
         1  Current turn number: 1		White player's turn
         2
         3
         4       A B C D E F G H
         5       _ _ _ _ _ _ _ _
         6    8 |X|X|X|X|X|X|X|X|
         7    7 |X|X|X|X|X|X|X|X|
         8    6 |_|_|_|_|_|_|_|_|		Your total number of pieces:  16
         9    5 |_|_|_|_|_|_|_|_|		Enemy total number of pieces: 16
         10   4 |_|_|_|_|_|_|_|_|
         11   3 |_|_|_|_|_|_|_|_|
         12   2 |O|O|O|O|O|O|O|O|
         13   1 |O|O|O|O|O|O|O|O|
         14
         15
         */
        // get turn number and current player turn from line 1
        int searchInx = 0;
        int searchInx2 = 0;
        String temp;
        String[] lines = board.split(System.getProperty("line.separator"));
        searchInx = lines[0].indexOf(':');
        searchInx2 = lines[0].indexOf('\t', searchInx);
        searchInx += 2;
        temp = lines[0].substring(searchInx, searchInx2);
        currentTurn.setText("Turn: " + temp);
        searchInx = lines[0].lastIndexOf('\t');
        searchInx2 = lines[0].lastIndexOf('n') + 1;
        temp = lines[0].substring(searchInx, searchInx2);
        currentPlayerTurn.setText(temp);
        // start getting board info from lines 6 to 13
        int bp = 0;
        int wp = 0;
        for (int i = 5; i < 13; ++i) {
            int r = (i - 5);
            int c = 0;
            searchInx2 = 0;
            temp = lines[i];
            while (temp.lastIndexOf('|') - 2 != searchInx2) {
                searchInx = temp.indexOf('|', searchInx2 + 1);
                char space = temp.charAt(searchInx + 1);
                addPiece(r, c, space);
                searchInx2 = searchInx;
                if (space == 'X') {
                    ++bp;
                } else if (space == 'O') {
                    ++wp;
                }
                ++c;
            }
        }
        whitePieces = wp;
        blackPieces = bp;
        numWhitePieces.setText("White pieces: " + Integer.toString(whitePieces));
        numBlackPieces.setText("Black pieces: " + Integer.toString(blackPieces));
    }

    /*public void openGUI() {
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
    }*/

    /*public static void main(String[] args) {
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
     }*/
}
