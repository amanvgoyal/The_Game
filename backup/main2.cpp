#include "AI.h"

using namespace std;

int main() {
  AI a;
  string s = "A8b,B8b,C8b,D8b,E8b,F8b,G8b,H8w";
  string diff = "EASY";

  a.move(s, diff);

  return 0;
}
