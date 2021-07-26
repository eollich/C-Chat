#include <msock.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/select.h>

int main(int argc, char **argv){
  const char *port_number = "9898";
  const int backlog = 10;

  int server_socket = setup_server(port_number, backlog);

  fd_set current_sockets, ready_sockets;

  //initialize my current set
  FD_ZERO(&current_sockets);
  FD_SET(server_socket, &current_sockets);

  while(1){
    
    printf("Waiting for connections...\n");

    //because select is destructive 
    ready_sockets = current_sockets;

    if( select(FD_SETSIZE, &ready_sockets, NULL, NULL, NULL) <0){
      perror("select error");
      exit(EXIT_FAILURE);
    }

    for(int i=0; i< FD_SETSIZE; i++){
      if(FD_ISSET(i, &ready_sockets)){
        if(i == server_socket){
          //this is a new connection to be accepted
          int client_socket = accept_new_connection(server_socket);
          FD_SET(client_socket, &current_sockets);
        }else{
          //the socket is already in the set
          //do whatever with the connection
          handle_connection(i);
          FD_CLR(i, &current_sockets);
        }
      }
    }

    ////wait for and eventually accept an incoming connection
    //int client_socket = accept_new_connection(server_socket);

    ////do whatever we do with the connections.
    //handle_connection(client_socket);
  }
  return 0;
}
