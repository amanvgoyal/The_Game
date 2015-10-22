flex scanner.l Main.cpp Parser.cpp
g++ -g -o Game -std=c++11 lex.yy.c Board.cpp Piece.cpp Log.cpp AI.cpp -lfl
exit 0
