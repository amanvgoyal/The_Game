/*
 *********************************************************
**    Piece.h    ******************************************
**  Description: This class will represent the pieces    **
**  on the board and will contain information about the  **
**  piece                                                **
 *********************************************************
*/
/*
 *********************************************************
**    HEADER FILES    *************************************
 *********************************************************
*/
/*
 *********************************************************
**    ENUMERATIONS & STRUCTS    ***************************
 *********************************************************
*/
// Determines the color of the pieces
enum Color = { WHITE, BLACK };

// Determines the location of the board of the piece
struct Position
{	// 0 if not on board
	int col;
	int row;
};
/*
 *********************************************************
**    CLASS DECLARATION    ********************************
 *********************************************************
*/
class Piece
{
	int id;									// stores piece number
	Color team;								// stores color information
	Position pos;							// stores position information
	bool active;							// stores whether the piece is on the board or not
public:
	/*    CONSTRUCTOR     */
	Piece(int number, Color color, Position position, bool on_board) 
	: id(number), team(color), pos(position), active(on_board) { };
	/*    HELPER FUNCTIONS    */
	void position(Position space);			// set the position
	Position position();					// returns the position of the piece
	void on_board(bool on);					// set whether the piece is on the board or not
	bool on_board();						// returns the board status
	void number(int number);				// set the number of the piece
	int number();							// returns the number of the piece
	bool color(Color col);					// set the color of the piece
	Color color();							// returns the color of the piece
};