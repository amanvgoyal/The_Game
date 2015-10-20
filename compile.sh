flex scanner.l Main.cpp Parser.cpp AI.cpp Piece.cpp
g++ -std=c++11 -o server2 -std=c++11 server2.c
g++ -std=c++11 -o client -std=c++11 client.c
g++ -std=c++11 -o Game -std=c++11 lex.yy.c -lfl
exit 0
