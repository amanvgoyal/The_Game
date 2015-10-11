flex scanner.l Main.cpp Parser.cpp
g++ -o server2 -std=c++11 server2.c
g++ -o client -std=c++11 client.c
g++ -o Game -std=c++11 lex.yy.c -lfl
exit 0
