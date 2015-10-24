#include "AI.h"
#include "Piece.h"
#include <string>
#include <vector>
#include <stdlib.h>
#include <iostream>
#include <algorithm>
#include <random>

using namespace std;

const int rows = 8;
const int cols = 8;

const int MAX_DEPTH = 3;
const int ADJ_ENEMY_VAL = 3;
const int ADJ_ALLY_VAL = 2;
const int MOVE_FWD_VAL = 2;
const int BLOCKED_VAL = 2;
const int HOLE_VAL = 3;
const int EAT_BONUS = 99;//10; 

auto eng = default_random_engine();

string AI::move(vector<vector<Piece*> > board_state, string diff, string color) {
  update_state(board_state);
  state s;
  s.change = brd;
  s.move = "";

  /*
  Color p1, p2;
  if (color == "BLACK") {
    p1 = Color::BLACK;
    p2 = Color::WHITE;
  }

  else {
    p1 = Color::WHITE;
    p2 = Color::BLACK;
  }

  if (diff == "EASY") {
    return random(color);
  }
   
  else if (diff == "MEDIUM") {
    return minimax(s,3,p1,p2).move;
  }

  else if (diff == "HARD") {
    return alpha_beta(s,7,-999999,999999,p1,p2).move;
  }
  else {
    cerr << "Difficulty string not well formed!" << endl;
    return "";
  }
*/    

  //cout << "MINIMAX: " << minimax(s, 3, Color::BLACK, Color::BLACK).move << endl;
  //return minimax(s, 3, Color::BLACK, Color::WHITE).move; // wrong? always eats?
  //return minimax(s, 3, Color::BLACK, Color::BLACK).move; // eats for depth 1

  //cout << "AB: " << alpha_beta(s, 3, -999999, 999999, Color::BLACK, Color::BLACK).move<< endl;
  return alpha_beta(s, 5, -999999, 999999, Color::BLACK, Color::WHITE).move;
  //return random("BLACK");
}

void AI::update_state(vector<vector<Piece*>> state) {
  Position pos;
  for (int i = 0; i < 8; ++i) {
    for (int j = 0; j < 8; ++j) {
      brd[i][j] = Color::NONE;
    }
  }

  for (auto v : state) {
    for (auto p : v) {
      if (p != nullptr) {
	pos = p->position(); 
	brd[7-pos.row][pos.col] = p->color();
      }
    }
  }

  print_board(brd);
} 

Color AI::win(board b) {
  // Check if someone has reached the edge of the board
  for (int i = 0; i < rows; ++i) {
    if (b[0][i] == Color::WHITE) {
      return Color::WHITE; // White has won
    }
    
    if (b[7][i] == Color::BLACK) {
      return Color::BLACK; // Black has won
    }
  }

  // Check if someone lost all of their pieces
  int b_ct, w_ct;
  for (int i = 0; i < rows; ++i) {
    for (int j =0; j < cols; ++j) {
      if (b[i][j] == Color::WHITE) {++w_ct;}
      if (b[i][j] == Color::BLACK) {++b_ct;}
    }
  }

  if (b_ct == 0) {return Color::WHITE;}
  if (w_ct == 0) {return Color::BLACK;}

  return Color::NONE; // No one has won
}

vector<state> AI::generate_moves(board b, Color player_color) {
  //board b_copy = b;
  srand(unsigned(time(0)));
  vector<state> ret;
  Color original;
  int ct = 0;
  state temp;
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      if (b[i][j] == player_color) {
	
	if (player_color == Color::WHITE) {
	  // Can go up
	  if (i > 0) {
	    if (b[i-1][j] == Color::NONE) {
	      b[i-1][j] = player_color;
	      b[i][j] = Color::NONE;
	      temp.change = b;
	      temp.move = move_str(i,j,i-1,j);
	      temp.ate = false;
	      ret.push_back(temp);
	      b[i-1][j] = Color::NONE;
	      b[i][j] = player_color;
	    }
	  }

	  // Can go diag left
	  if (i > 0 && j > 0) {
	    if (b[i-1][j-1] != player_color) {
	      (b[i-1][j-1] != Color::NONE) ? temp.ate = true : temp.ate = false;
	      original = b[i-1][j-1];
	      b[i-1][j-1] = player_color;
	      b[i][j] = Color::NONE;
	      temp.change = b;
	      temp.move = move_str(i,j,i-1,j-1);
	      ret.push_back(temp);
	      b[i][j] = player_color;
	      b[i-1][j-1] = original;
	    }
	  }
      
	  // Can go diag right
	  if (i > 0 && j < 7) {
	    if (b[i-1][j+1] != player_color) {
	      (b[i-1][j+1] != Color::NONE) ? temp.ate = true : temp.ate = false;
	      original = b[i-1][j+1];
	      b[i-1][j+1] = player_color;
	      b[i][j] = Color::NONE;
	      temp.change = b;
	      temp.move = move_str(i,j,i-1,j+1);
	      ret.push_back(temp);
	      b[i-1][j+1] = original;
	      b[i][j] = player_color;
	    }
	  }
	}

	if (player_color == Color::BLACK) {
	  // Can go down 
	  if (i < 7) {
	    if (b[i+1][j] == Color::NONE) {
	      original = b[i+1][j];
	      b[i+1][j] = player_color;
	      b[i][j] = Color::NONE;
	      temp.change = b;
	      temp.move = move_str(i,j,i+1,j);
	      temp.ate = false;
	      ret.push_back(temp);
	      b[i+1][j] = original;
	      b[i][j] = player_color;
	    }
	  }

	  // Can go diag left
	  if (i < 7 && j > 0) {
	    if (b[i+1][j-1] != player_color) {
	      (b[i+1][j-1] != Color::NONE) ? temp.ate = true : temp.ate = false;
	      original = b[i+1][j-1];
	      b[i+1][j-1] = player_color;
	      b[i][j] = Color::NONE;
	      temp.change = b;
	      temp.move = move_str(i,j,i+1,j-1);
	      ret.push_back(temp);
	      b[i+1][j-1] = original;
	      b[i][j] = player_color;	    
	    }
	  }

	  // Can go diag right
	  if (i < 7 && j < 7) {
	    if (b[i+1][j+1] != player_color) {
	      (b[i+1][j+1] != Color::NONE) ? temp.ate = true : temp.ate = false;
	      original = b[i+1][j+1];
	      b[i+1][j+1] = player_color;
	      b[i][j] = Color::NONE;
	      temp.change = b;
	      temp.move = move_str(i,j,i+1,j+1);
	      ret.push_back(temp);
	      b[i+1][j+1] = original;
	      b[i][j] = player_color;
	    }
	  }
	}
      }
    }
  }

  //  random_shuffle(ret.begin(), ret.end()); // MAYBE DONT DO THIS
  eng = default_random_engine{};
  shuffle(begin(ret), end(ret), eng);
  return ret;
} 

// IMPROVE THIS
int AI::threat_level(board b, int x, int y) {
  int val = 0;

  // Case White
  if (b[x][y] == Color::WHITE) {
    // Check if protected
    if (x < 7 && y > 0) {
      if (b[x+1][y-1] == Color::WHITE) {
	val += ADJ_ALLY_VAL;
      }
    }
    
    if (x < 7 && y < 7) {
      if (b[x+1][y+1] == Color::WHITE) {
	val += ADJ_ALLY_VAL;
      }
    }
    
    // Check for Attackers
    if (x < 7 && y > 0) {
      if (b[x+1][y-1] == Color::BLACK) {
	val -= ADJ_ENEMY_VAL;
      }
    }
    if (x < 7 && y < 7) {
      if (b[x+1][y+1] == Color::BLACK) {
	val -= ADJ_ENEMY_VAL;
      }
    }
  }

  // Case Black
  else if (b[x][y] == Color::BLACK) {
    // Check if protected
    if (x > 0 && y > 0) {
      if (b[x-1][y-1] == Color::BLACK) {
	val += ADJ_ALLY_VAL;
      }
    }
    if (x > 0 && y < 7) {
      if (b[x-1][y+1] == Color::BLACK) {
	val += ADJ_ALLY_VAL;
      }
    }
    
    // Check for Attackers
    if (x > 0 && y > 0) {
      if (b[x-1][y-1] == Color::WHITE) {
	val -= ADJ_ENEMY_VAL;
      }
    }
    if (x > 0 && y < 7) {
      if (b[x-1][y+1] == Color::WHITE) {
	val -= ADJ_ENEMY_VAL;
      }
    }
  }

  else {cerr << "no piece there!" << endl;}

  return val;
}

// MAYBE CHECK IF X, Y, IN RANGE
// SUPPOSED TO STOP GAME IF WE GET TO THE ENDS
int AI::mobility_level(board b, int x, int y) {
  int mobi_val = 0;
  bool hole = true;

  // can go fwd
  if (b[x][y] == Color::WHITE && b[x-1][y] == Color::NONE) {
    mobi_val += MOVE_FWD_VAL;

    // Check if there's a path to the end
    for (int i = 0; i < x; ++i) {
      if (b[i][y] != Color::NONE) {hole = false;}
    }
    if (hole) {mobi_val += HOLE_VAL;}
  }
  else {mobi_val -= BLOCKED_VAL;}
  
  // can go fwd
  if (b[x][y] == Color::BLACK && b[x+1][y] == Color::NONE) {
    mobi_val += MOVE_FWD_VAL;
    
    // Check if there's a path to the end
    for (int i = 7; i > x - 1; --i) {
      if (b[i][y] != Color::NONE) {hole = false;}
    }
    if (hole) {mobi_val += HOLE_VAL;}
}
  else {mobi_val -= -BLOCKED_VAL;}
}

int AI::piece_val(board b, int x, int y) {
  int piece_val = 0;
  piece_val += threat_level(b, x, y);
  piece_val += mobility_level(b, x, y);

  //cout << "PIECE @ (" << x << ", " << y << ") VAL: " << piece_val << endl;
  return piece_val;
}

int AI::board_val(board b, bool ate, Color player_color) {
  int board_val = 0;
  
  // Bonus if a piece at another
  if (ate) {
    board_val += EAT_BONUS;
  } // Too much?

  // First check for wins??
  if (win(b) == player_color) return 99999999;

  // Now check features
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      if (b[i][j] == Color::NONE) {
	continue; // No Piece on this square
      }

      else if (b[i][j] == player_color) {
	board_val += piece_val(b, i, j); //???
      }

      else if (b[i][j] != player_color) {
	board_val -= piece_val(b, i, j); //???
      }
    }
  }

  return board_val;
}

void AI::print_board(board b) {
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {

      if (b[i][j] == Color::WHITE) {
        cout << "w ";
      }

      else if (b[i][j] == Color::BLACK) {
        cout << "b ";
      }

      else {
        cout << "n ";
      }
    }
    cout << endl;
  }
}
 
string AI::random(string color) {
  srand(time(NULL));

  vector<string> possible_moves;
  vector<string> eat_moves;

  Color player_color;
  Color enemy_color;
  if (color == "BLACK") {
    player_color = Color::BLACK;
    enemy_color = Color::WHITE;
  }
  else {
    player_color = Color::WHITE;
    enemy_color = Color::BLACK;
  }

  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      if (brd[i][j] == player_color) {
	if (player_color == Color::WHITE) {

	  // Can go up
	  if (i > 0) {
	    if (brd[i-1][j] != Color::NONE) {
	      possible_moves.push_back(move_str(i,j,i-1,j));
	    }
	  }

	  // Can go diag left
	  if (i > 0 && j > 0) {
	    if (brd[i-1][j-1] != player_color) {
	      if (brd[i-1][j-1] == enemy_color) {
		eat_moves.push_back(move_str(i,j,i-1,j-1));
	      }
	      else {
		possible_moves.push_back(move_str(i,j,i-1,j-1));
	      }
	    }
	  }
      
	  // Can go diag right
	  if (i > 0 && j < 7) {
	    if (brd[i-1][j+1] != player_color) {
	      if (brd[i-1][j+1] == enemy_color) {
		eat_moves.push_back(move_str(i,j,i-1,j+1));
	      }
	      else {possible_moves.push_back(move_str(i,j,i-1,j+1));}
	    }
	  }
	}

	if (player_color == Color::BLACK) {
	  // Can go down 
	  if (i < 7) {
	    if (brd[i+1][j] == Color::NONE) {
	      possible_moves.push_back(move_str(i,j,i+1,j));
	    }
	  }

	  // Can go diag left
	  if (i < 7 && j > 0) {
	    if (brd[i+1][j-1] != player_color) {
	      if (brd[i+1][j-1] == enemy_color) {
		cout << "EATING!!!!!!!!!!!!!!!!!" << endl;
		eat_moves.push_back(move_str(i,j,i+1,j-1));
	      }
	      else {possible_moves.push_back(move_str(i,j,i+1,j-1));}
	    }
	  }

	  // Can go diag right
	  if (i < 7 && j < 7) {
	    if (brd[i+1][j+1] != player_color) {
	      if (brd[i+1][j+1] == enemy_color) {
		cout << "EATING!!!!!!!!!!!!!!!!!" << endl;
		eat_moves.push_back(move_str(i,j,i+1,j+1));
	      }
	      else {possible_moves.push_back(move_str(i,j,i+1,j+1));}
	    }
	  }
	}
      }
    }
  }
  
  int index = 0;
  if (eat_moves.size() > 0) {
    index = rand() % eat_moves.size();
    return eat_moves[index];
  }
  else {
    index = rand() % possible_moves.size();
    return possible_moves[index];
  }
}

scored_move AI::minimax(state s, int depth, Color cur_player, Color max_player) {
  scored_move m, temp;
  int cur_score;
  string move;
  vector<state> moves;
  Color enemy;

  if (max_player == Color::BLACK) {enemy = Color::WHITE;}
  else {enemy = Color::BLACK;}

  if (depth == 0 || win(s.change) != Color::NONE) {
    m.move = s.move;
    m.score = board_val(s.change, s.ate, cur_player);
    return m;
  }

  if (cur_player == max_player) {
    cur_score = -99999;
    moves = generate_moves(s.change, cur_player);
    for (auto mov : moves) {
      //cout << mov.move << endl;
      temp = minimax(mov, depth - 1, enemy, max_player);
      if (temp.score > cur_score) {
	cur_score = temp.score;
	move = mov.move;
      }
    }
    m.move = move;
    m.score = cur_score;
    return m;
  }

  else if (cur_player != max_player) {
    cur_score = 99999;
    moves = generate_moves(s.change, cur_player);
    for (auto mov : moves) {
      //cout << mov.move << endl;
      temp = minimax(mov, depth - 1, max_player, max_player);
      if (temp.score < cur_score) {
	cur_score = temp.score;
	move = mov.move;
      }
    }
    m.move = move;
    m.score = cur_score;
    return m;
  }
}

scored_move AI::alpha_beta(state s, int depth, int alpha, int beta, Color cur_player, Color max_player) {
  scored_move m, temp;
  int cur_score;
  string move;
  vector<state> moves;
  Color enemy;

  if (max_player == Color::BLACK) {enemy = Color::WHITE;}
  else {enemy = Color::BLACK;}

  if (depth == 0 || win(s.change) != Color::NONE) {
    m.move = s.move;
    m.score = board_val(s.change, s.ate, cur_player);
    return m;
  }

  if (cur_player == max_player) { 
    cur_score = -999999;
    moves = generate_moves(s.change, cur_player);
    for (auto mov : moves) {
      temp = alpha_beta(mov, depth - 1, alpha, beta, enemy, max_player);
      if (temp.score > cur_score) {
	cur_score = temp.score;
	move = mov.move;
      }
      if (temp.score > alpha) {alpha = temp.score;}
      if (beta <= alpha) {break;}
    }
    m.score = cur_score;
    m.move = move;
    
    return m;
  }

  else {
    cur_score = 99999;
    moves = generate_moves(s.change, cur_player);
    for (auto mov : moves) {
      temp = alpha_beta(mov, depth - 1, alpha, beta, max_player, max_player);
      if (temp.score < cur_score) {
	cur_score = temp.score;
	move = mov.move;
      }
      if (temp.score < beta) {beta = temp.score;}
      if (beta <= alpha) {break;}
    }
    m.score = cur_score;
    m.move = move;
    
    return m;
  }
}

string AI::move_str(int x1, int y1, int x2, int y2) {
  string mov = "("+to_string(y1)+", "+to_string(x1)+")*("+to_string(y2)+", "+
    to_string(x2)+")";
  return mov;
}
