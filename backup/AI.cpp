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
  }
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
  vector<board> bs = generate_moves(brd, Color::WHITE);
  //for (auto v : bs) {
  //print_board(v);
  //}
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
  board b_copy = b;
  vector<board> ret;
  Color original;
  int ct = 0;
  for (int i = 0; i < 8; ++i) {
    for (int j = 0; j < 8; ++i) {
      cout << i << ", " << j << endl;
      //if (b[i][j] == player_color) {
      /*
	if (player_color == Color::WHITE) {
	  // Can go up
	  if (i < 7) {
	    if (b_copy[i][j+1] == Color::NONE) {
	      b_copy[i][j+1] = player_color;
	      ret.push_back(b_copy);
	      b_copy[i][j+1] = Color::NONE;
	    }
	  }

	  // Can go diagonal left
	  if (i > 0 && j < 7) {
	    if (b_copy[i-1][j+1] != player_color) {
	      original = b_copy[i-1][j+1];
	      b_copy[i-1][j+1] = player_color;
	      ret.push_back(b_copy);
	      b_copy[i-1][i+1] = original; 
	    }
	  }

	  // Can go diagonal right
	  if (i < 7 && j < 7) {
	    if (b_copy[i+1][j+1] != player_color) {
	      original = b_copy[i+1][j+1];
	      b_copy[i+1][j+1] = player_color;
	      ret.push_back(b_copy);
	      b_copy[i+1][j+1] = original;
	    }
	  }
	}
				    
	if (player_color == Color::BLACK) {
	  // Can go down
	  if (j > 0) {
	    if (b_copy[i][j-1] == Color::NONE) {
	      b_copy[i][j-1] = player_color;
	      ret.push_back(b_copy);
	      b_copy[i][j-1] = Color::NONE;
	    }
	  }

	  // Can go diagonal left
	  if (i > 0 && j > 0) {
	    if (b_copy[i-1][j-1] != player_color) {
	      original = b_copy[i-1][j+1];
	      b_copy[i-1][j-1] = player_color;
	      ret.push_back(b_copy);
	      b_copy[i-1][j-1] = original; 
	    }
	  }

	  // Can go diagonal right
	  if (i < 7 && j > 0) {
	    if (b_copy[i+1][j-1] != player_color) {
	      original = b_copy[i+1][j+1];
	      b_copy[i+1][j-1] = player_color;
	      ret.push_back(b_copy);
	      b_copy[i+1][j-1] = original;
	    }
	  }	
	}
	}*/
    }
  }
}

int AI::board_val(board b, Color player_color) {
  // First check for wins
  if (win(b) == player_color) return 99999999;

  // Now check features
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < rows; ++j) {
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

