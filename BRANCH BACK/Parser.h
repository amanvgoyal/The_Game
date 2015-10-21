#ifndef PARSER_H
#define PARSER_H

#include <stack>
#include <iostream>
#include <vector>

class Parser
{
 private:
  std::stack<Token> ordered;
 public:
  /*------------MAINTENANCE------------------------*/
  bool reverse_order(std::stack<Token>& theStack);
  bool par_line();
  bool par_empty();
  int  par_stacksize();
  /*------------PROGRAM----------------------------*/
  bool par_program(std::stack<Token>& theStack, int error_count);
  bool par_statment();
  /*------------Difficulty----------------------------*/
  void random();
  void mini_max();
  void alpha_beta();
};
#endif 