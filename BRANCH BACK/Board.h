/*
*********************************************************
**    Board.h    ******************************************
**  Description: This class will represent the state of  **
**  the board. It will store the the pieces of each      **
**  player in a vector of pointers to Pieces.            **

*********************************************************
=======
**  The board will be represented in the following way:  **
**     A B C D E F G H                                   **
**     _ _ _ _ _ _ _ _                                   **
**  8 |_|_|_|_|_|_|_|_|                                  **
**  7 |_|_|_|_|_|_|_|_|                                  **
**  6 |_|_|_|_|_|_|_|_|                                  **
**  5 |_|_|_|_|_|_|_|_|                                  **
**  4 |_|_|_|_|_|_|_|_|                                  **
**  3 |_|_|_|_|_|_|_|_|                                  **
**  2 |_|_|_|_|_|_|_|_|                                  **
**  1 |_|_|_|_|_|_|_|_|                                  **
*********************************************************
*/
#ifndef BOARD
#define BOARD
/*
*********************************************************
**    HEADER FILES    *************************************
*********************************************************
*/
#include <vector>
#include <string>
#include <fstream>
#include "Log.h"
#include "Piece.h"
/*
*********************************************************
**    ENUMERATIONS & STRUCTS    ***************************
*********************************************************
*/
// Movement directions, left and right move diagonally
enum Direction { FORWARD, LEFT, RIGHT };

// Specify the output format
enum Output { FILE, SHELL, STRING };

// Contains the piece and direction the piece will move
struct Move
{
  Piece piece;
  Direction direction;
  Piece *piece;
  Direction direction;
};
/*
*********************************************************
**    CLASS DECLARATION    ********************************
*********************************************************
*/
class History
{
  std::vector<Move> move_history;
  std::vector<Piece*> capture_history;
  std::vector<std::vector<std::vector<Piece*>>> board_state_history;
 public:
  void move(Move move);										// add the moves performed
  Move move(int turn);										// returns the move performed at the specified turn
  void capture(Piece* piece);									// add the captured pieces
  Piece* capture(int turn);									// returns the piece captured at the specified turn or NULL if it is empty
  void board_state(std::vector<std::vector<Piece*>> board);	// add the board state
  std::vector<std::vector<Piece*>> board_state(int turn);		// returns the board state at the specified turn
  void clear_history();										// clears all the vectors
};

class Board
{	
  Log game_log;								// keeps a log of the game's activity and errors
  std::vector<std::vector<Piece*> > pieces;	// keeps track of the pieces on the board
  std::vector<Move> history;					// will keep track of the move history
  Color turn;									// keeps track of who's turn it is
  Color winner;								// will be set to the player who wins
  unsigned int row;							// vertical size of board
  unsigned int col;							// horizontal size of board
  int num_white_pieces;						// keeps track of the white team's pieces
  int num_black_pieces;						// keeps track of the black team's pieces
  bool valid;									// keeps track of the validity of the game state
  bool game_end;								// will be set to true when the game ends
  bool game_aborted;							// will be set to true if the game did not finish
	
  /*    PRIVATE MEMBER FUNCTIONS    */
  bool add_piece(Piece piece);				// adds pieces to the board
  bool remove_piece(Piece piece);				// removes pieces from the board
  bool check_move(Move move);					// check if the move is valid
  bool check_game();							// check game conditions
  bool end_turn();							// end the current turn and switch to the other player
  int column_inx(char index);					// converts the letter index of the column to an int
  char column_inx(int index);					// converts the int index of the column to a letter
 public:
  /*    CONSTRUCTOR    */
  Board(unsigned int rows, unsigned int columns);
	
  /*    MEMBER FUNCTIONS    */
  bool init(unsigned int rows, unsigned int columns);	// initialize the board
  bool clear();										// clear the board
  bool move_piece(Move move);							// move the specified piece
  bool show_moves(Piece piece);						// show the valid moves for the specified piece
  bool undo_move();									// undo the previous move
  void show_results();								// show the results of the game
  void display_board();								// display the board in the command line window
  string output_game_state(Output output_type);		// output the game state
  string output_history(Output output_type);			// output the game history
  string game_state();								// output the current game state
};

  Log game_log;											// keeps a log of the game's activity and errors
std::vector<std::vector<Piece*>> board_spaces;			// keeps track of the pieces on the board
History history;										// will keep track of the move history
Color turn;												// keeps track of who's turn it is
Color winner;											// will be set to the player who wins
unsigned int row;										// vertical size of board
unsigned int col;										// horizontal size of board
unsigned int turn_num;									// keeps track of turn number; one turn is one player's move
int num_white_pieces;									// keeps track of the white team's pieces
int num_black_pieces;									// keeps track of the black team's pieces
bool game_end;											// will be set to true when the game ends
bool game_aborted;										// will be set to true if the game did not finish
	
/*    PRIVATE MEMBER FUNCTIONS    */
bool check_move(Move move);								// check if the move is valid
bool check_game();										// check game conditions
void end_turn();										// end the current turn and switch to the other player
int	 column_inx(char index);							// converts the letter index of the column to an int
char column_inx(int index);								// converts the int index of the column to a letter
public:
/*    CONSTRUCTOR    */
Board();
Board(unsigned int rows, unsigned int columns);
	
/*    MEMBER FUNCTIONS    */
bool init();											// initialize the board
bool clear();											// clear the board
bool set_size(unsigned int rows, unsigned int cols);	// set the size of the board
bool move_piece(Move move);								// move the specified piece
bool show_moves(Piece* piece);							// show the valid moves for the specified piece
bool undo_move();										// undo the previous move
void show_results();									// show the results of the game
void display_board();									// display the board in the command line window
string output_history();								// output the game history
string output_board();									// output the current board state
string output_board(std::vector<std::vector<Piece*>> game_board);	// output the specified board
string game_state();									// output the current game state
};
#endif

