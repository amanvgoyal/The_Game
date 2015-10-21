#include "AI.h"
#include <vector>
#include "Piece.h"
#include "Board.h"
#include "Game_State.h"
#include "Log.h"

using namespace std;

int main() {
  AI a;
  vector<vector<Piece*>> v = {};
  string s = a.move(v, "HARD");
  return 0;
}
