#include "AI.h"
#include "Piece.h"
#include <string>
#include <vector>
#include <iostream>

using namespace std;

const int rows = 8;
const int cols = 8;

string AI::move(vector<vector<Piece*> > state, string diff, string color) {
  ai_color = color;
  update_state(state);
  /*
  if (diff == "EASY") {
    return random(color);
  }
  
  else if (diff == "MEDIUM") {
    return minimax(color);
  }

  else if (diff == "HARD") {
    return alpha_beta(color);
  }

  else {
    cerr << "Difficulty string not well formed!" << endl;
    }*/
  return "";
}

void AI::update_state(vector<vector<Piece*>> state) {
  /*Position pos;
  for (auto v : state) {
    for (auto p : v) {
      pos = p->position(); 
      board[pos.row][pos.col] = p->color();
    }
  }
  */

  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      if (i == 0 || i == 1) {
	brd[i][j] = Color::BLACK;
      }
      
      else if (i == 6 || i == 7) {
	brd[i][j] = Color::WHITE;
      }
      
      else {
	brd[i][j] = Color::NONE;
      }
    }
  }

  print_board(brd);
  cout << endl;
  vector<board> bs = generate_moves(brd, Color::BLACK);
  cout << bs.size() << endl;;
  /*for (auto v : bs) {
    print_board(v);
    cout << endl;
    }*/
} 

Color AI::win(board b) {
  for (int i = 0; i < rows; ++i) {
    if (b[0][i] == Color::WHITE) {
      return Color::WHITE; // White has won
    }
    
    if (b[7][i] == Color::BLACK) {
      return Color::BLACK; // Black has won
    }
  }

  return Color::NONE; // No one has won
}

vector<board> AI::generate_moves(board b, Color player_color) {
  //board b_copy = b;
  vector<board> ret;
  Color original;
  int ct = 0;
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      if (b[i][j] == player_color) {
	
	if (player_color == Color::WHITE) {
	  // Can go up
	  if (i > 0) {
	    if (b[i-1][j] == Color::NONE) {
	      b[i-1][j] = player_color;
	      b[i][j] = Color::NONE;
	      ret.push_back(b);
	      b[i-1][j] = Color::NONE;
	      b[i][j] = player_color;
	    }
	  }

	  // Can go diag left
	  if (i > 0 && j > 0) {
	    if (b[i-1][j-1] != player_color) {
	      original = b[i-1][j-1];
	      b[i-1][j-1] = player_color;
	      b[i][j] = Color::NONE;
	      ret.push_back(b);
	      b[i][j] = player_color;
	      b[i-1][j-1] = original;
	    }
	  }
      

	  // Can go diag right
	  if (i > 0 && j < 7) {
	    if (b[i-1][j+1] != player_color) {
	      original = b[i-1][j+1];
	      b[i-1][j+1] = player_color;
	      b[i][j] = Color::NONE;
	      ret.push_back(b);
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
	      ret.push_back(b);
	      b[i+1][j] = original;
	      b[i][j] = player_color;
	    }
	  }

	  // Can go diag left
	  if (i < 7 && j > 0) {
	    if (b[i+1][j-1] != player_color) {
	      original = b[i+1][j-1];
	      b[i+1][j-1] = player_color;
	      b[i][j] = Color::NONE;
	      ret.push_back(b);
	      b[i+1][j-1] = original;
	      b[i][j] = player_color;	    
	    }
	  }

	  // Can go diag right
	  if (i < 7 && j < 7) {
	    if (b[i+1][j+1] != player_color) {
	      original = b[i+1][j+1];
	      b[i+1][j+1] = player_color;
	      b[i][j] = Color::NONE;
	      ret.push_back(b);
	      b[i+1][j+1] = original;
	      b[i][j] = player_color;
	    }
	  }
	}
      }
    }
  }
  return ret;
} 

int AI::board_val(board b, Color player_color) {
  // First check for wins
  if (win(b) == player_color) return 99999999;

  // Now check features
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      if (b[i][j] == Color::NONE) {
	continue; // No Piece on this square
      }

      else if (b[i][j] == Color::WHITE) {

      }

      else if (b[i][j] == Color::BLACK) {

      }
    }
  }
}

void AI::print_board(board b) {
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      //      cout << '(' << i << ", " << j << "): ";                               
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

}

string AI::minimax(string color) {

}

string AI::alpha_beta(string color) {

}

