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
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <string.h>
#include <vector>

using namespace std;

void parse(string S);
int server();

int main(int argc,  char** argv) {
    server();
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
int server()
{     
        int sock, connected, bytes_recieved , truea = 1;  
        string send_data;
        char recv_data[1024];       

        struct sockaddr_in server_addr,client_addr;    
        socklen_t sin_size;
        
        if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
            perror("Socket");
            exit(1);
        }

        if (setsockopt(sock,SOL_SOCKET,SO_REUSEADDR,&truea,sizeof(int)) == -1) {
            perror("Setsockopt");
            exit(1);
        }
        
        server_addr.sin_family = AF_INET;         
        server_addr.sin_port = htons(5000);     
        server_addr.sin_addr.s_addr = INADDR_ANY; 
        bzero(&(server_addr.sin_zero),8); 

        if (bind(sock, (struct sockaddr *)&server_addr, sizeof(struct sockaddr))
                                                                       == -1) {
            perror("Unable to bind");
            exit(1);
        }

        if (listen(sock, 5) == -1) {
            perror("Listen");
            exit(1);
        }
        
          printf("\nTCPServer Waiting for client on port 5000");
        fflush(stdout);


        while(1)
        {  

            sin_size = sizeof(struct sockaddr_in);

            connected = accept(sock, (struct sockaddr *)&client_addr,&sin_size);

            printf("\n Connection from (%s , %d)",
                   inet_ntoa(client_addr.sin_addr),ntohs(client_addr.sin_port));
            cout<<"\n";
            int count =-1;
            while (1)
            {
              bool done = false;
              if(count ==-1){
                do{
                send_data = "Password:";
                send(connected, send_data.c_str(),send_data.length(), 0);
                memset(recv_data, 0, sizeof recv_data);
                bytes_recieved = recv(connected,recv_data,1024,0);
                recv_data[bytes_recieved] = '\0';
                string temp = recv_data;
                temp.erase(temp.begin()+8,temp.end());
                if(temp=="password"){
                      done = true;
                      count++;
                }
                else{
                  send_data = "\nPassword Incorrect, Try Again:";
                  send(connected, send_data.c_str(),send_data.length(), 0);
                  memset(recv_data, 0, sizeof recv_data);
                  bytes_recieved = recv(connected,recv_data,1024,0);
                  recv_data[bytes_recieved] = '\0';
                  string temp = recv_data;
                  temp.erase(temp.begin()+8,temp.end());
                  if(temp=="password"){
                        done = true;
                        count++;
                  }

                }
                  
              }while(!done);
                send_data.clear();
                send_data = "WELCOME:";
                send(connected, send_data.c_str(),send_data.length(), 0);
              }
              memset(recv_data, 0, sizeof recv_data);
              bytes_recieved = recv(connected,recv_data,1024,0);
              recv_data[bytes_recieved] = '\0';
              string temp = recv_data;
              temp.erase(temp.begin()+temp.length()-2,temp.end());
              cout<<"Parsing this:"<<temp<<endl;
              parse(temp);
              cout<<"\n RECIEVED DATA = " <<recv_data;
              if(recv_data!=" "||recv_data!="\0"){
              send_data.clear();
              send_data ="OK\n";
              cout<<"\n SENDING: "<<send_data;
              send(connected, send_data.c_str(),send_data.length(), 0); 
            }
              fflush(stdout);
            }
        }       

      close(sock);
      return 0;
} 


