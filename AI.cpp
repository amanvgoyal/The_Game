#include "AI.h"
#include "Piece.h"
#include <string>
#include <vector>
#include <stdlib.h>
#include <iostream>
#include <algorithm>
#include <random>
#include <time.h>

using namespace std;
 
const int rows = 8;
const int cols = 8;

const int MAX_DEPTH = 3;

// AI evaluation parameters
const int ADJ_ENEMY_VAL = 2; // Perhaps make this higher
const int ADJ_ALLY_VAL = 1; // Bonus if protected
const int MOVE_FWD_VAL = 1; // Bonus if mobile
const int BLOCKED_VAL = 1; // Penalty if blocked
const int HOLE_VAL = 1; // Bonus if can travel through to endgame
const int HOLE_CREATE_VAL = 1; // Penalty if you made a hole
const int EAT_BONUS = 600; // Major incentive to kill
const int HOME_ROW_VAL = 1; // Penalty for each open space in home row
const int INVADER_VAL = 2; // Penalty for each enemy you let near endgame

const int INF = 999999;

auto eng = default_random_engine();

// In case need to check runtime
clock_t t1, t2;

void AI::set_difficulty(string s){
  if(s=="EASY") level = Easy;
  if(s=="MEDIUM") level = Medium;
  if(s=="HARD") level = Hard;

}

string AI::move(vector<vector<Piece*> > board_state, string diff, string color) {
  update_state(board_state);
  state s;
  s.change = brd;
  s.move = "";

  string ret_move;

  t1 = clock();
  cout<<"Difficulty Level:";
  if(level == Hard){
    ret_move = alpha_beta(s, 4, -INF, INF, Color::BLACK, Color::BLACK).move;
    cout<<"Alpha Beta"<<endl;
  }
  if(level == Medium){
    ret_move = minimax(s,3,Color::BLACK, Color::BLACK).move;
    cout<<"MINIMAX"<<endl;
  }
  if(level == Easy){
    ret_move = random(color);
    cout<<"Random"<<endl;
  }
  if (ret_move == "") {ret_move = random(color);}
  t2 = clock();
  cout << "TIME: " << ((double)t2 - (double)t1) / CLOCKS_PER_SEC << endl;
  cout << "THE MOVE: " << ret_move << endl;
  return ret_move;
}

void AI::update_state(vector<vector<Piece*>> state) {
  Position pos;
  for (int i = 0; i < 8; ++i) {
    for (int j = 0; j < 8; ++j) {
      brd[i][j] = Color::NONE;
    }
  }

  // Fill board structure with colors corresponding to pieces
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
  for (int i = 0; i < cols; ++i) {
    if (b[0][i] == Color::WHITE) {
      return Color::WHITE; // White has won
    }
    
    if (b[7][i] == Color::BLACK) {
      return Color::BLACK; // Black has won
    }
  }

  // Check if someone lost all of their pieces
  int b_ct = 0;
  int w_ct = 0;
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

  eng = default_random_engine{};
  shuffle(begin(ret), end(ret), eng);
 
  return ret;
} 

int AI::threat_level(board b, int x, int y) {
  int val = 0;
  int openings = 0;
  
  // Case White
  if (b[x][y] == Color::WHITE) {
    // Check if protected
    if (x > 0 && y > 0) {
      if (b[x+1][y-1] == Color::WHITE) {
  val += ADJ_ALLY_VAL;
      }
    }
    
    if (x > 0 && y < 7) {
      if (b[x+1][y+1] == Color::WHITE) {
  val += ADJ_ALLY_VAL;
      }
    }
    
    // Check for Attackers
    if (x > 0 && y > 0) {
      if (b[x-1][y-1] == Color::BLACK) {
  val -= ADJ_ENEMY_VAL;
      }
    }
    if (x > 0 && y < 7) {
      if (b[x-1][y+1] == Color::BLACK) {
  val -= ADJ_ENEMY_VAL;
      }
    }
  
    for (int i = 0; i < cols; ++i) {
      if (b[7][i] != Color::WHITE) {++openings;}
    }
    val -= openings*HOME_ROW_VAL;

    // check for invaders
    for (int i = 5; i < 8; ++i) {
      for (int j = 0; j < 8; ++j) {
  if (b[i][j] == Color::BLACK) {val -= INVADER_VAL;}
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
    if (x < 7 && y > 0) {
      if (b[x+1][y-1] == Color::WHITE) {
  val -= ADJ_ENEMY_VAL;
      }
    }
    if (x < 7 && y < 7) {
      if (b[x+1][y+1] == Color::WHITE) {
  val -= ADJ_ENEMY_VAL;
      }
    }
    
    // check if made openings
    for (int i = 0; i < cols; ++i) {
      if (b[0][i] != Color::BLACK) {++openings;}
    }
    val -= openings*HOME_ROW_VAL;
  
    // check for invaders
    for (int i = 0; i < 3; ++i) {
      for (int j = 0; j < 8; ++j) {
  if (b[i][j] == Color::WHITE) {val -= INVADER_VAL;}
      } 
    }
  }

  else {cerr << "no piece there!" << endl;}

  return val;
}

// MAKE A FILL HOLE BONUS
vector<int> AI::hole_check(board b) {
  bool b_hole = true;
  bool w_hole = true;
  int w_hole_ct = 0;
  int b_hole_ct = 0;
  vector<int> num_holes;
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      // check black hole
      if (i > 0 && i < 3) {
  if (b[i][j] != Color::NONE) {b_hole = false;}
      }

      // check white hole
      if (i < 8 && i > 3) {
  if (b[i][j] != Color::NONE) {w_hole = false;}
      }

      if (b_hole) {
  ++b_hole_ct;
      }

      if (w_hole) {++w_hole_ct;}
      b_hole = true;
      w_hole = true;
    }
  }

  num_holes = {b_hole_ct, w_hole_ct};
  return num_holes;
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

// Pieces score higher if they are mobile and protected
// low score if immobile and threatened
int AI::piece_val(board b, int x, int y) {
  int piece_val = 0;
  piece_val += threat_level(b, x, y);
  piece_val += mobility_level(b, x, y);

  return piece_val;
}

int AI::board_val(board b, bool ate, Color player_color) {
  int board_val = 0;
  Color enemy;
  vector<int> hole_vals;

  (player_color == Color::BLACK) ? enemy = Color::WHITE : enemy = Color::BLACK;

  // First check for wins
  Color winner = win(b);
  if (winner == player_color) {return INF;}
  else if (winner == enemy) {return -INF;}

  // Bonus if a piece at another
  if (ate) {
    board_val += EAT_BONUS;
  } 

  // Board gets points if enemy has holes
  // loses points if you have holes
  hole_vals = hole_check(b);
  if (player_color == Color::BLACK) {
    board_val -= hole_vals[0]*HOLE_CREATE_VAL;
    board_val += hole_vals[1]*HOLE_CREATE_VAL;
  }
  else {
    board_val += hole_vals[0]*HOLE_CREATE_VAL;
    board_val -= hole_vals[1]*HOLE_CREATE_VAL;
  }

  // Now check features
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      if (b[i][j] == Color::NONE) {
  continue; // No Piece on this square
      }

      else if (b[i][j] == player_color) {
  board_val += piece_val(b, i, j); // benefit from your pieces
      }

      else if (b[i][j] == enemy) {
  board_val -= piece_val(b, i, j); // lose advantage from your opponents 
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
    eat_moves.push_back(move_str(i,j,i+1,j-1));
        }
        else {possible_moves.push_back(move_str(i,j,i+1,j-1));}
      }
    }

    // Can go diag right
    if (i < 7 && j < 7) {
      if (brd[i+1][j+1] != player_color) {
        if (brd[i+1][j+1] == enemy_color) {
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

  // moves = generate_moves(s.change, cur_player);

  // if (depth == 0 || moves.size() == 0) {
  if (depth == 0 || win(s.change) != Color::NONE) {
    m.move = s.move;
    m.score = board_val(s.change, s.ate, cur_player);
    return m;
  }

  if (cur_player == max_player) {
    cur_score = -INF;
    moves = generate_moves(s.change, cur_player);

    if (moves.size() == 0) {
      m.move = s.move;
      m.score = board_val(s.change, s.ate, cur_player);
      return m;
    }

    for (auto mov : moves) {
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
    cur_score = INF;
    moves = generate_moves(s.change, cur_player);

    if (moves.size() == 0) {
      m.move = s.move;
      m.score = board_val(s.change, s.ate, cur_player);
      return m;
    }

    for (auto mov : moves) {
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

  moves = generate_moves(s.change, cur_player);

  if (depth == 0 || win(s.change) != Color::NONE || moves.size() == 0) {
  //if (depth == 0 || win(s.change) != Color::NONE) {
    m.move = s.move;
    m.score = board_val(s.change, s.ate, cur_player);
    return m;
  }

  if (cur_player == max_player) { 
    cur_score = -INF;
    for (auto mov : moves) {
      temp = alpha_beta(mov, depth - 1, alpha, beta, enemy, max_player);
      if (temp.score > cur_score) {
  cur_score = temp.score;
  move = mov.move;
      }
      if (temp.score > alpha) {alpha = temp.score;}
      if (beta <= alpha) {break;} // cut off to save time
    }
    m.score = cur_score;
    m.move = move;
    
    return m;
  }

  else {
    cur_score = INF;
    for (auto mov : moves) {
      temp = alpha_beta(mov, depth - 1, alpha, beta, max_player, max_player);
      if (temp.score < cur_score) {
  cur_score = temp.score;
  move = mov.move;
      }
      if (temp.score < beta) {beta = temp.score;}
      if (beta <= alpha) {break;} // cut off to save time
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
