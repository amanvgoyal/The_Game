1;2802;0c#include "AI.h"
#include <string>
#include <vector>
#include <iostream>

using namespace std;

string AI::move(string state, string diff) {
  update_state(state);

  if (diff == "EASY") {
    return random(state, diff);
  }
  
  else if (diff == "MEDIUM") {
    return minimax(state, diff);
  }

  else if (diff == "HARD") {
    return alpha_beta(state, deff);
  }

  else {
    cerr << "Difficulty string not well formed!" << endl;
  }
}

void AI::update_state(string state) {
  size_t pos = 0;
  string delim = ",";
  string tok;

  vector <string> toks;

  while ((pos = state.find(delim)) != string::npos) {
    tok = state.substr(0, pos);
    toks.push_back(tok);
    state.erase(0, pos + delim.length());
  }
      
  // black piece
  for (auto tok : toks) {
    if (tok[2] == "b") {
      cout << "black" << endl;
    }

    // white piece
    else if (tok[2] == "w") {
      cout << "white" << endl;
    }

    else {
      cerr << "Invalid piece type char!" << endl;
    }
  }
}

string AI::random(string state, string diff) {

}

string AI::minimax(string state, string diff) {

}

string AI::alpha_beta(string state, string diff) {

}
