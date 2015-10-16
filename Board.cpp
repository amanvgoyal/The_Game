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
#include <iomanip>
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
/*    History    */
/*    MEMBER FUNCTIONS    */
void History::move(Move move)
{
	move_history.push_back(move);
}

Move History::move(int turn)
{
	return move_history[turn - 1];
}

void History::capture(Piece* piece)
{
	capture_history.push_back(piece);
}

Piece* History::capture(int turn)
{
	return capture_history[turn - 1];
}

void History::board_state(vector<vector<Piece*>> board)
{
	board_state_history.push_back(board);
}

vector<vector<Piece*>> History::board_state(int turn)
{
	return board_state_history[turn - 1];
}

void History::clear_history()
{
	move_history.clear();
	capture_history.clear();
	board_state_history.clear();
}
/*    Board    */
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
	turn_num = 1;
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
	turn_num = 1;
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
	string function = "clear";
}

bool Board::set_size(unsigned int rows, unsigned int cols)
{	// set the size of the board before starting a new game
	string function = "set_size";
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
	string function = "show_moves";
}

bool Board::undo_move()
{	// undoes the previous two turns
	string function = "undo_move";
	
	game_log.print(INFORMATION, function, string("Undoing the last two moves. . ."));
	if (turn_num < 3)
	{
		game_log.print(WARNING, function, string("Player attempted to undo on the first round."));
		return false;
	}
	board_spaces = history.board_state(turn_num - 2);
	turn_num -= 2;
	return true;
}

void Board::show_results()
{	// shows the results of the game
	string function = "show_results";
}

void Board::display_board()
{	// output the board on the command line and in a file called recent_game.txt
	// Expected output:
	// Current turn number: 1		White player's turn
	//
	//
	//      A B C D E F G H
	//      _ _ _ _ _ _ _ _
	//   8 |X|X|X|X|X|X|X|X|
	//   7 |X|X|X|X|X|X|X|X|
	//   6 |_|_|_|_|_|_|_|_|		Your total number of pieces:  16
	//   5 |_|_|_|_|_|_|_|_|		Enemy total number of pieces: 16
	//   4 |_|_|_|_|_|_|_|_|
	//   3 |_|_|_|_|_|_|_|_|
	//   2 |O|O|O|O|O|O|O|O|
	//   1 |O|O|O|O|O|O|O|O|
	//
	string function = "display_board";
	string cur_turn = turn == Color::WHITE ? "White" : "Black";
	int cur_player_pieces = turn == Color::WHITE ? num_white_pieces : num_black_pieces;
	int en_player_pieces = turn == Color::WHITE ? num_black_pieces : num_white_pieces;
	char col_label = 'A';
	int row_label = 8;

	game_log.print(INFORMATION, function, string("Displaying board. . ."));
	cout << "Current turn number: " << turn_num << '\t\t' << cur_turn << " player's turn\n\n\n";
	for (int i = -2; i < row; ++i)
	{
		cout << setw(4) << right;
		if (i > -1)
		{	// add the row numbers
			cout << row_label << ' ' << left;
			--row_label;
		}
		for (int j = 0; j < col; ++j)
		{	// draw the board
			if (i == -2)
			{
				cout << ' ' << col_label;
				++col_label;
			}
			else if (i == -1)
			{
				cout << " _";
			}
			else
			{
				Piece* cur_space = board_spaces[i][j];
				cout << '|';
				if (cur_space == nullptr)
				{	// empty space
					cout << '_';
				}
				else if (cur_space->color == Color::WHITE)
				{	// white piece (indicated by O)
					cout << 'O';
				}
				else if (cur_space->color == Color::BLACK)
				{	// black piece (indicated by X)
					cout << 'X';
				}
				if (j == col - 1)
				{
					cout << '|';
				}
			}

		}
		if (i == 2)
		{
			cout << "\t\tYour total number of pieces:  " << cur_player_pieces;
		}
		else if (i == 3)
		{
			cout << "\t\tEnemy total number of pieces: " << en_player_pieces;
		}
		cout << '\n';
	}
	cout << '\n';
}

string Board::output_history()
{	// outputs the history of the game to the specified medium
	string function = "output_history";
}

string Board::output_board()
{
	output_board(board_spaces);
}

string Board::output_board(vector<vector<Piece*>> game_board)
{
	// Expected output:
	// Current turn number: 1		White player's turn
	//
	//
	//      A B C D E F G H
	//      _ _ _ _ _ _ _ _
	//   8 |X|X|X|X|X|X|X|X|
	//   7 |X|X|X|X|X|X|X|X|
	//   6 |_|_|_|_|_|_|_|_|		Your total number of pieces:  16
	//   5 |_|_|_|_|_|_|_|_|		Enemy total number of pieces: 16
	//   4 |_|_|_|_|_|_|_|_|
	//   3 |_|_|_|_|_|_|_|_|
	//   2 |O|O|O|O|O|O|O|O|
	//   1 |O|O|O|O|O|O|O|O|
	//
	string function = "output_board";
	string cur_turn = turn == Color::WHITE ? "White" : "Black";
	string output;
	int cur_player_pieces = turn == Color::WHITE ? num_white_pieces : num_black_pieces;
	int en_player_pieces = turn == Color::WHITE ? num_black_pieces : num_white_pieces;
	char col_label = 'A';
	int row_label = 8;

	game_log.print(INFORMATION, function, string("Outputting board. . ."));
	output = "Current turn number: " + turn_num + '\t\t' + cur_turn + " player's turn\n\n\n";
	for (int i = -2; i < row; ++i)
	{
		output += "  ";
		if (i > -1)
		{	// add the row numbers
			output += row_label + ' ';
			--row_label;
		}
		else
		{
			output += "  ";
		}
		for (int j = 0; j < col; ++j)
		{	// draw the board
			if (i == -2)
			{
				output += ' ' + col_label;
				++col_label;
			}
			else if (i == -1)
			{
				output += " _";
			}
			else
			{
				Piece* cur_space = board_spaces[i][j];
				output += '|';
				if (cur_space == nullptr)
				{	// empty space
					output += '_';
				}
				else if (cur_space->color == Color::WHITE)
				{	// white piece (indicated by O)
					output += 'O';
				}
				else if (cur_space->color == Color::BLACK)
				{	// black piece (indicated by X)
					output += 'X';
				}
				if (j == col - 1)
				{
					output += '|';
				}
			}

		}
		if (i == 2)
		{
			output += "\t\tYour total number of pieces:  " + cur_player_pieces;
		}
		else if (i == 3)
		{
			output += "\t\tEnemy total number of pieces: " + en_player_pieces;
		}
		output += '\n';
	}
	output += '\n';
	return output;
}

string Board::game_state()
{	// outputs the current game_state in preparation to be sent over the network
	string function = "game_state";
}