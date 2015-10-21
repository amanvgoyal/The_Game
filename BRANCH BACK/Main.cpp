#include <iostream>
#include "Token.h"
#include "Parser.h"
#include "AI.h"
#include "Piece.h"
#include <cassert>
#include <string>
#include <sstream>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>      
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/time.h>
using namespace std;
void parse(string S);
int main(int argc,  char** argv) { 
  AI a;
  int row = 8;
  int col = 8;
  vector<vector<Piece*> > v(row, vector<Piece*>(col, NULL));;
  /*
  int piece_id = 1;
  Position cur_space;// = NULL;
  for (int i = 5; i < 8; ++i) {   // iterate through the top two rows of the board 
    for (int j = 0; j < 8; ++j) {       
      // iterate through the columns                     
      // add pieces to the board   
      cur_space.row = i;
      cur_space.col = j;
      v[i][j] = new Piece(piece_id, Color::BLACK, cur_space, true);
      ++piece_id;
    }
  }
  // add the white pieces to the board                                             
  for (int i = 0; i < 2; ++i) {
    // iterate through the bottom two rows of the board     
    for (int j = 0; j < 8; ++j) {
      // iterate through the columns                                
      // add pieces to the board                                                
      cur_space.row = i;
      cur_space.col = j;
      v[i][j] = new Piece(piece_id, Color::WHITE, cur_space, true);
      ++piece_id;
    }
  }
*/
  string s = a.move(v, "HARD", "BLACK");
  
  //  system("./server2 5010");
  /*++argv, --argc;
    if ( argc > 0 )
    yyin = fopen( argv[0], "r" );
    else{
    yyin = stdin;
    }
    yylex();
    cout<<"Token Stack Size:"<<tokens.size()<<endl;
  Parser dp;
  dp.par_program(tokens,errors);
  while(!tokens.empty()){
  tokens.pop();
  }
  dp.par_empty();*/
return 0;
}
/*
void parse(string S){
  Parser dp;
  const char * c = S.c_str();
  YY_BUFFER_STATE bp = yy_scan_string(c);
  yy_switch_to_buffer(bp);
  yylex();

  dp.par_program(tokens,errors);
  yy_delete_buffer(bp);
  errors =0;
  while(!tokens.empty()){

    tokens.pop();
  }
  dp.par_empty();

}

*/
