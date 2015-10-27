#include <iostream>
#include "Token.h"
#include "Parser.h"
#include <cassert>
#include <string>
#include <sstream>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h> 
#include <netdb.h>     
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
#include <ctype.h>
#include "Board.h"

using namespace std;

/*string parse(string S);*/
int server(int port_num, string server_name);
Parser run;
int main(int argc,  char** argv) {
     if (argc < 2)
    {
        cerr << "Syntam : ./server <port>" << endl;
        return 0;
    }
    else server(atoi(argv[1]),"127.0.0.1");
  return 0;
}
int server(int port_num, string server_name)
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
         struct hostent *hostp; 
        server_addr.sin_family = AF_INET;         
        server_addr.sin_port = htons(port_num);  
         if((server_addr.sin_addr.s_addr = inet_addr(server_name.c_str())) == (unsigned long)INADDR_NONE){

            hostp = gethostbyname(server_name.c_str());
             if(hostp == (struct hostent *)NULL){
              printf("HOST NOT FOUND --> ");
              printf("h_errno = %d\n",h_errno);
              exit(-1);
              }
            memcpy(&server_addr.sin_addr, hostp->h_addr, sizeof(server_addr.sin_addr));

          }
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
        
          cout<<"\nTCPServer Waiting for client on port "<<port_num;
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
                if(run.check_pass(temp)){
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
                  if(run.check_pass(temp)){
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
              string temp;
              string check_pass = recv_data;
               for (std::string::size_type i=0; i<check_pass.length(); ++i)
                  {
                    if (iswprint(check_pass[i]))
                            temp+=check_pass[i];
                  }
              cout<<"Parsing this:"<<temp<<endl;
              if(temp.length()>0){
                  string value = run.parse(temp);
                  if(value=="FALSE"){
                    send_data.clear();
                    send_data = "ILLEGAL \n";
                    send(connected, send_data.c_str(),send_data.length(), 0);
                  }
                  else if(value == "EXIT"){
                        send_data.clear();
                        send_data = "BYE\n";
                        send(connected, send_data.c_str(),send_data.length(), 0);
                        close(connected);
                        break;
                  }
                  else if(value=="TRUE")
                  {

                  }
                  else{
                    send_data.clear();
                    send_data = value+"\n";
                    send(connected, send_data.c_str(),send_data.length(), 0);
                    if(Game.game_ended()){
                        close(connected);
                        Game.clear();
                        Game.init();
                        Game.end_turn();
                        Game.reset_turn();
                        run.reset();
                        break;
                    }
                  }
              }
              cout<<"\n RECIEVED DATA = " <<temp;
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


