/*
 *********************************************************
**    Board.cpp    ****************************************
**  Description: This class will represent the state of  **
**  the board. It will store the the pieces of each      **
**  player in a vector of pointers to Pieces.            **
 *********************************************************
*/
/*
 *********************************************************
**    HEADER FILES    *************************************
 *********************************************************
*/
#include <vector>
#include <string>
#include "Piece.h"

using namespace std;
/*
 *********************************************************
**    CLASS DEFINITIONS    ********************************
 *********************************************************
*/
/*    CONSTRUCTOR    */
Board::Board(unsigned int rows, unsigned int columns)
{	// initialize the board
	// open log file for output and set to clear previous run
	game_log.open("board_log.txt", fstream::out | fstream::trunc);
	if(!log.is_open())
	{	// do not output to log if file cannot be opened
		// this must be checked in each section that outputs to this file
		cerr << "Error creating board_log.txt. Game activity will not be recorded.\n";
	}
	init(rows, columns);
}

/*    PRIVATE MEMBER FUNCTIONS    */
bool Board::add_piece(Piece piece)
{	// adds pieces to the board
	
}

bool Board::remove_piece(Piece piece)
{
	
}

bool Board::check_move(Move move)
{
	// returns true if the move is valid or
	// false if a move is invalid
	if (move.piece.color() == turn)
	{	// the player is not trying to move a piece that is not theirs
		switch(move.direction)
		{
			case FORWARD:
				break;
			case RIGHT:
				break;
			case LEFT:
				break;
			default:		// the code should not reach this pointer
				return false;
				break;
		}
	}
	else
	{
		
	}
}

bool Board::check_game();
{
	
}

bool end_turn()
{
	
}

int column_inx(char index)
{	// converts the letter index of the column to an integer
	// for the vector
	index = toupper(index);
	if (index < 'A' || index > 'Z') return -1;
	else return index - 65;
}

char column_inx(int index)
{	// converts the integer index of the column to a character
	if (index < 0 || index > 26) return '\0';
	else return index + 65;
}

/*    MEMBER FUNCTIONS    */
bool Board::init(unsigned int rows, unsigned int columns)
{	// initialize the board for a new game
	// returns true if no errors were found
	// set the size of the board
	pieces = vector<vector<Piece*> >(rows, vector<string>(columns, null_ptr));
	// add the pieces to the board

}

bool Board::clear()
{	// clear the board in preparation for exit or a new game
	// returns true if no errors were found
	
}

bool Board::move_piece(Color color, Move move)
{	// moves the specified piece 
	
}

bool Board::show_moves(Color color, Piece piece)
{	// show the valid moves for the selected piece
	
}

bool Board::undo_move()
{	// undoes the previous move
	
}

void Board::show_results()
{	// shows the results of the game
	
}

void Board::display_board()
{	// output the board on the command line and in a file called recent_game.txt
	
}

string Board::output_game_state(Output output_type);
{	// outputs the game state to the specified output medium
	// returns and empty string if FILE is not selected
	
}

string Board::output_history(Output output_type)
{	// outputs the history of the game to the specified medium
	
}

string Board::game_state()
{	// outputs the current game_state in preparation to be sent over the network
	
}