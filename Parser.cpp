#include <iostream>
#include <map>
#include <algorithm>
#include "Parser.h"

bool Parser::reverse_order(stack<Token>& theStack){
  size_t temp = theStack.size();
  while(!theStack.empty()){
    ordered.push(theStack.top());
    theStack.pop();
  }
  if(temp == ordered.size()) return true;
  return false;
}
bool Parser::check_pass(string s){
  if(s==password)return true;
  else return false;
}
void Parser::parse(string S){
    const char * c = S.c_str();
    YY_BUFFER_STATE bp = yy_scan_string(c);
    yy_switch_to_buffer(bp);
    yylex();

    par_program(tokens,errors);
    yy_delete_buffer(bp);
    errors =0;
    while(!tokens.empty()){
      tokens.pop();
    }
    par_empty();
}
void Parser::set_pass(string s){
  password = s;
}
bool Parser::par_program(stack<Token>& theStack, int error_count){
  reverse_order(theStack); // Swap stack from abc to cba
  if(error_count==0){ //If tokenizer caught errors it i 
    while(!ordered.empty()){ //Keep popping until nothing is left 
      if(!par_line()){ //call Par_line which calls query or commands
		par_empty();//empty the stack becase statement is invalid
      }
    else cout<<"Done"<<endl;
		par_empty();
    }
  }
  if(error_count>0){// if there were errors found ABORT
    par_empty();//empty the stack
  }
}
bool Parser::par_empty(){
  if(!ordered.empty()){
    while(!ordered.empty()){
      ordered.pop();
    }
    return true;
  }
  return false;
}
int Parser::par_stacksize(){
  return ordered.size();
}
string Parser::par_display(){
  
}
bool Parser::par_line(){
  Token temp = ordered.top();
  if(temp.get_type()==T_IDENTIFIER){
      return true;
  }
  if(temp.get_type()==T_EXIT){
      return true;
  }
  if(temp.get_type()==T_DISPLAY){
      ordered.pop();
      par_display();
      return true;
  }
  if(temp.get_type()==T_UNDO){
      return true;
  }
  if(temp.get_type()==T_HUMANAI){
      ordered.pop();
  		temp = ordered.top();
  		if(temp.get_type()==T_EASY||temp.get_type()==T_MEDIUM||temp.get_type()==T_HARD){
  			switch(temp.get_type()){
  				case T_EASY:{
  					ordered.pop();
  					random();
  					return true;
  					break;
  				}
  				case T_MEDIUM:{
  					ordered.pop();
  					mini_max();
  					return true;
  					break;
  				}
  				case T_HARD:{
  					ordered.pop();
  					alpha_beta();
  					return true;
  					break;
  				}
  				default : return false;
  			}
  		}
  		else return true;
  }
  temp =ordered.top();
   if(temp.get_type()==T_AIAI){
  		ordered.pop();
  		temp = ordered.top();
  		if(temp.get_type()==T_IP){
  			string  server = temp.get_string_value(); 
  			ordered.pop();
  			temp = ordered.top();
  			if(temp.get_type()==T_INTVALUE){
  				int port = temp.get_num();
  				ordered.pop();
  				temp = ordered.top();
  				if(temp.get_type()==T_IDENTIFIER){
  					string password = temp.get_string_value();
  					ordered.pop();
  					temp = ordered.top();
  					if(temp.get_type()==T_EASY||temp.get_type()==T_MEDIUM||temp.get_type()==T_HARD){
  						string my_difficulty;
  						switch(temp.get_type()){
			  				case T_EASY:{
			  					ordered.pop();
			  					my_difficulty = "EASY";
			  					break;
			  				}
			  				case T_MEDIUM:{
			  					ordered.pop();
			  					my_difficulty = "MEDIUM";
			  					break;
			  				}
			  				case T_HARD:{
			  					ordered.pop();
			  					my_difficulty = "Hard";
			  					break;
			  				}
			  				default : return false;
			  			}
  						temp = ordered.top();
  						string opp_difficulty;
  						if(temp.get_type()==T_EASY||temp.get_type()==T_MEDIUM||temp.get_type()==T_HARD){
	  								switch(temp.get_type()){
				  				case T_EASY:{
				  					ordered.pop();
				  					opp_difficulty = "EASY";
				  					break;
				  				}
				  				case T_MEDIUM:{
				  					ordered.pop();
				  					opp_difficulty = "MEDIUM";
				  					break;
				  				}
				  				case T_HARD:{
				  					ordered.pop();
				  					opp_difficulty = "Hard";
				  					break;
				  				}
				  				default : return false;
				  			}
				  			//server(server name, port number, password, my_difficulty, opponenet difficulty)
				  			return true;
  						}
  					}
  				}

  			}
  		}
  }

  return false; //if none of the above conditions match its not part of our language
}
void Parser::random(){

}
void Parser::mini_max(){
	
}
void Parser::alpha_beta(){
	
}