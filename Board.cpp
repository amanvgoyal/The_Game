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
#include <iostream>
#include <exception>
#include <vector>
#include <string>
#include "Board.h"
#include "Piece.h"

using namespace std;
/*
 *********************************************************
**    CLASS DEFINITIONS    ********************************
 *********************************************************
*/
/*    CONSTRUCTOR    */
Board::Board()
{// initialize the board
	// open log file for output and set to clear previous run
	string function = "Board";

	// initialize private members
	turn = Color::WHITE;
	winner = Color::WHITE;
	row = 8;
	col = 8;
	num_white_pieces = 0;
	num_white_pieces = 0;
	game_end = false;
	game_aborted = false;
	game_log.open("board_log.txt", fstream::out | fstream::trunc);
	if (!game_log.is_open())
	{	// do not output to log if file cannot be opened
		// this must be checked in each section that outputs to this file
		cerr << "Error creating board_log.txt. Game activity will not be recorded.\n";
	}
	else
	{
		game_log.print(INFORMATION, function, string("Log file created successfully."));
	}
	init();
}
Board::Board(unsigned int rows, unsigned int columns)
{	// initialize the board
	// open log file for output and set to clear previous run
	string function = "Board";

	/* These variables should be reset to this state when clearing the board */
	turn = Color::WHITE;
	winner = Color::WHITE;
	row = rows;
	col = columns;
	num_white_pieces = 0;
	num_white_pieces = 0;
	game_end = false;
	game_aborted = false;
	/* The top variables should be set to this when clearing the board */
	game_log.open("board_log.txt", fstream::out | fstream::trunc);
	
	if(!game_log.is_open())
	{	// do not output to log if file cannot be opened
		// this must be checked in each section that outputs to this file
		cerr << "Error creating board_log.txt. Game activity will not be recorded.\n";
	}
	else
	{
		game_log.print(INFORMATION, function, string("Log file created successfully."));
	}
	init();
}

/*    PRIVATE MEMBER FUNCTIONS    */
bool Board::check_move(Move move)
{	// returns true if the move is valid or
	// false if a move is invalid
	string function = "check_move";

	bool check_up = (turn == Color::WHITE) ? true : false;
	int r = check_up ? move.piece->position().row + 1 : move.piece->position().row - 1;
	game_log.print(INFORMATION, function, string("Checking move. . ."));
	if (move.piece->color() == turn)
	{	// the player is not trying to move a piece that is not theirs
		switch(move.direction)
		{
			case FORWARD:
			{
				if (board_spaces[r][move.piece->position().col] != nullptr)
				{
					game_log.print(WARNING, function, string("Forward move is invalid; piece in the way."));
					return false;
				}
				else
				{
					game_log.print(INFORMATION, function, string("Forward move is valid."));
					return true;
				}
				break;
			}
			case RIGHT:
			{
				int c = move.piece->position().col + 1;
				if (board_spaces[r][c] != nullptr)
				{
					if (board_spaces[r][c]->color == turn)
					{
						game_log.print(WARNING, function, string("Diagonally right move is invalid; friendly piece in the way."));
						return false;
					}
					else
					{
						game_log.print(INFORMATION, function, string("Diagonally right move is valid; enemy piece will be captured."));
						return true;
					}
				}
				else
				{
					game_log.print(INFORMATION, function, string("Diagonally right move is valid."));
					return true;
				}
				break;
			}
			case LEFT:
			{
				int c = move.piece->position().col - 1;
				if (board_spaces[r][c] != nullptr)
				{
					if (board_spaces[r][c]->color == turn)
					{
						game_log.print(WARNING, function, string("Diagonally left move is invalid; friendly piece in the way."));
						return false;
					}
					else
					{
						game_log.print(INFORMATION, function, string("Diagonally left move is valid. enemy piece will be captured."));
						return true;
					}
				}
				else
				{
					game_log.print(INFORMATION, function, string("Diagonally left move is valid."));
					return true;
				}
				break;
			}
			default:		// the code should not reach this point
			{
				game_log.print(ERROR, function, string("The default case was reached when checking move direction.\tmove.direction = " + move.direction));
				return false;
				break;
			}
		}
	}
	else
	{
		game_log.print(WARNING, function, string("The player attempted to move a piece that is not theirs."));
		return false;
	}
}

bool Board::check_game()
{	// check for victory conditions
	// returns true if victory conditions are met
	string function = "check_game";

	game_log.print(INFORMATION, function, string("Checking victory conditions . . ."));
	if (num_white_pieces == 0 && num_black_pieces == 0)
	{	// this condition should never be hit
		game_log.print(ERROR, function, string("Victory condition hit; both players have no more pieces on board."));
		return true;
	}
	else if (num_white_pieces == 0)
	{
		game_log.print(INFORMATION, function, string("Victory condition hit; white player has no more pieces on board."));
		winner = Color::BLACK;
		return true;
	}
	else if (num_black_pieces == 0)
	{
		game_log.print(INFORMATION, function, string("Victory condition hit; black player has no more pieces on board."));
		winner = Color::WHITE;
		return true;
	}
	else
	{	// check if either player has reached the last row for them
		for (int i = 0; i < col; ++i)
		{	// both players should not have pieces on the enemy home row at the same time
			// since this function is called at the end of each player's turn
			// iterate through the white home row
			if (board_spaces[0][i]->color == Color::BLACK)
			{
				game_log.print(INFORMATION, function, string("Victory condition hit; black player has reached the white home row."));
				winner = Color::BLACK;
				return true;
			}
			// iterate through the black home row
			if (board_spaces[row - 1][i]->color == Color::WHITE)
			{
				game_log.print(INFORMATION, function, string("Victory condition hit; white player has reached the black home row."));
				winner = Color::WHITE;
				return true;
			}
		}
		game_log.print(INFORMATION, function, string("No victory conditions were met."));
		return false;
	}
}

void Board::end_turn()
{	// checks victory conditions and displays the results if they are met
	// or switches to the other player's turn
	string function = "end_turn";
	// add board state to history and increase turn number
	history.board_state(board_spaces);
	++turn_num;
	if (check_game())
	{	// victory conditions were found
		game_end = true;
		show_results();
	}
	else
	{	// switch turns
		turn = turn == Color::WHITE ? Color::BLACK : Color::WHITE;
		string cur_player = turn == Color::WHITE ? "white" : "black";
		game_log.print(INFORMATION, function, string("Switching turns; it is the " + cur_player + " player's turn now."));
	}
}

int Board::column_inx(char index)
{	// converts the letter index of the column to an integer
	// for the vector
	index = toupper(index);
	if (index < 'A' || index > 'Z') return -1;
	else return index - 65;
}

char Board::column_inx(int index)
{	// converts the integer index of the column to a character
	if (index < 0 || index > 26) return '\0';
	else return index + 65;
}

/*    MEMBER FUNCTIONS    */
bool Board::init()
{	// initialize the board for a new game
	// returns true if no errors were found
	// set the size of the board
	string function = "init";
	int piece_id = 1;
	Position cur_space;

	game_log.print(INFORMATION, function, string("Adding the pieces to the board."));
	vector<vector<Piece*>> new_board(row, vector<Piece*>(col, nullptr));
	board_spaces = new_board;
	// add the black pieces to the board
	for (int i = row - 3; i < row; ++i)
	{	// iterate through the top two rows of the board
		for (int j = 0; j < col; ++j)
		{	// iterate through the columns
			// add pieces to the board
			cur_space.row = i;
			cur_space.col = j;
			board_spaces[i][j] = new Piece(piece_id, Color::BLACK, cur_space, true);
			++piece_id;
			++num_black_pieces;
		}
	}
	// add the white pieces to the board
	for (int i = 0; i < 2; ++i)
	{	// iterate through the bottom two rows of the board
		for (int j = 0; j < col; ++j)
		{	// iterate through the columns
			// add pieces to the board
			cur_space.row = i;
			cur_space.col = j;
			board_spaces[i][j] = new Piece(piece_id, Color::WHITE, cur_space, true);
			++piece_id;
			++num_white_pieces;
		}
	}
}

bool Board::clear()
{	// clear the board in preparation for exit or a new game
	// reset variables for a new game
	// returns true if no errors were found
	
	// set all the spaces to point to nullptr

	// set all the variables that were modified during the game to the default value
	// check Board::Board() for the variables
}

bool set_size(unsigned int rows, unsigned int cols)
{	// set the size of the board before starting a new game

}

bool Board::move_piece(Move move)
{	// moves the specified piece after checking the validity of the move
	string function = "move_piece";

	game_log.print(INFORMATION, function, string("Moving piece. . ."));
	if (check_move(move))
	{
		Piece* piece_to_move = move.piece;
		bool check_up = (turn == Color::WHITE) ? true : false;
		int r = check_up ? move.piece->position().row + 1 : move.piece->position().row - 1;
		int c = 0;
		int orig_r = piece_to_move->position().row;
		int orig_c = piece_to_move->position().col;
		// add the move to the move history
		history.move(move);
		switch (move.direction)
		{
		case FORWARD:
		{
			c = orig_c;
			break;
		}
		case LEFT:
		{
			c = orig_c - 1;
			break;
		}
		case RIGHT:
		{
			c = orig_c + 1;
			break;
		}
		default:
		{
			game_log.print(ERROR, function, string("The default case was reached when checking move direction.\tmove.direction = " + move.direction));
			return false;
			break;
		}
		}
		// remove the piece from its original spot
		board_spaces[orig_r][orig_c] = nullptr;
		// modify piece position
		piece_to_move->position(r, c);
		if (board_spaces[r][c] != nullptr)
		{	// enemy piece to be captured; store in history
			history.capture(board_spaces[r][c]);
		}
		else
		{	// enemy piece is not captured; store nullptr in history
			history.capture(nullptr);
		}
		board_spaces[r][c] = piece_to_move;
	}
}

bool Board::show_moves(Piece* piece)
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

string Board::output_game_state(Output output_type)
{	// outputs the game state to the specified output medium
	// returns and empty string if FILE is not selected
	
}

string Board::output_history(Output output_type)
{	// outputs the history of the game to the specified medium
	
}

string Board::game_state()
{	// outputs the current game_state in preparation to be sent over the network
	
}