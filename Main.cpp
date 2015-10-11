#include <iostream>
#include "Token.h"
#include "Parser.h"
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
      system("./server2 5010");
/*
    ++argv, --argc;
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

