#ifndef AI_H
#define AI_H

#include <string>
#include <vector>
#include <array>
#include <map>
#include "Piece.h"

// Board is an 8x8 matrix
typedef std::array<std::array<Color, 8>, 8> board;

struct scored_move {
  int score;
  std::string move;
};

struct state {
  board change;
  bool ate = false;
  std::string move;
};
enum Difficulty{Easy, Medium, Hard};
class AI {
 private:
  std::vector<std::vector<Piece*>> game_state;
  Difficulty level;
  //Color board[8][8];
  board brd;
  std::string ai_color;

  Color win(board); // Taks a board, returns color of winner (maybe NONE)
  std::vector<state> generate_moves(board, Color); // all possible moves for player
  int board_val(board, bool, Color); // Evaluates a board for a player
  int threat_level(board, int, int); // How threatened a piece is 
  int mobility_level(board, int, int); // Movement options for a piece
  int piece_val(board, int, int); // Score for a piece based on above

  std::vector<int> hole_check(board); // 1st index #black holes, 2nd #white holse

  void print_board(board);

  std::string move_str(int, int, int, int); // Turns pos tuples into string

public:
  std::string move(std::vector<std::vector<Piece*> >, std::string diff, std::string color);

  std::string random(std::string diff);
  scored_move minimax(state, int, Color, Color);
  scored_move alpha_beta(state, int, int, int, Color, Color);
    
  void set_difficulty(std::string s);
  void update_state(std::vector<std::vector<Piece*>>); // Takes vec from Board
};

#endif
