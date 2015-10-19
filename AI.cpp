#include "AI.h"
#include <string>
#include <vector>
#include <iostream>

using namespace std;

string AI::move(vector<vector<Piece*> > state, string diff) {
  update_state(state);

  if (diff == "EASY") {
    return random(diff);
  }
  
  else if (diff == "MEDIUM") {
    return minimax(diff);
  }

  else if (diff == "HARD") {
    return alpha_beta(diff);
  }

  else {
    cerr << "Difficulty string not well formed!" << endl;
  }
}

void AI::update_state(vector<vector<Piece*>> state) {
  Position pos;
  for (auto v : state) {
    for (auto &p : v) {
      pos = p->position(); 
      board[pos.row][pos.col] = p->color();
    }
  }
}

string AI::random(string diff) {

}

string AI::minimax(string diff) {

}

string AI::alpha_beta(string diff) {

}

