#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <arpa/inet.h>

//get connectors info
void *get_in_addr(struct sockaddr *sa){
  if(sa -> sa_family == AF_INET){
    return &(((struct sockaddr_in*)sa)->sin_addr);
  }
  return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

//handle errors
//TODO
int check(int exp, const char *msg){
  return 0;
}

/*----------SERVER FUNCTIONS----------*/

//setup server
int setup_server(const char* port_number, int backlog){
  int server_socket;
  int enable = 1;

  struct addrinfo hints, *res, *rec;
  memset(&hints, 0, sizeof(hints));

  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_PASSIVE;

  //translate socket
  if( (getaddrinfo(NULL, port_number, &hints, &res)) !=0 ){
    perror("Failed to translate the server socket.");
    exit(EXIT_FAILURE);
  }

  for(rec = res; rec!=NULL; rec = rec->ai_next){
    server_socket = socket(rec->ai_family, rec->ai_socktype, rec->ai_protocol);
    if(server_socket == -1){
      continue;
    }

    setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(enable));

    //bind socket
    if( bind(server_socket, rec->ai_addr, rec->ai_addrlen) ==0 ){
      break;
    }
    close(server_socket);
  }

  if(rec==NULL){
    perror("Failed to create or connect client socket.");
    exit(EXIT_FAILURE);
  }

  //free the linked list with results
  freeaddrinfo(res);

  printf("Server socket created and bound\n");

  //listen
  if(listen(server_socket, backlog) == -1 ){
    perror("Failed to start server socket listen.");
    exit(EXIT_FAILURE);
  }
  printf("Server started listening on port %s\n", port_number);

  return server_socket;
}

//accept new connection
int accept_new_connection(int server_socket){
  int client_socket;

  struct sockaddr_storage their_addr;//connector's address information
  socklen_t sin_size = sizeof(their_addr);
  char s[INET6_ADDRSTRLEN];

  if( (client_socket = accept(server_socket, (struct sockaddr *)&their_addr, &sin_size)) <0 ){
    perror("Failed to accept client socket.");
    exit(EXIT_FAILURE);
  }

  inet_ntop(their_addr.ss_family, get_in_addr( (struct sockaddr*)&their_addr ), s, sizeof(s) );

  printf("Client socket accepted: %s\n", s);
  return client_socket;
}

//handle connection
//void *handle_connection(int client_socket){
void handle_connection(int client_socket){
  char *msg = "Hello from the server!";

  if( send(client_socket, msg, strlen(msg), 0) == -1){
    perror("Failed to send message to client.");
    exit(EXIT_FAILURE);
  }else{
    printf("Message sent\n");
  }
  close(client_socket);
  printf("Client socket closed.\n");
}

/*----------CLIENT FUNCTIONS----------*/
int setup_client(const char* host_name, const char* port_number){

  int client_socket;

  struct addrinfo hints, *res, *rec;
  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_protocol = IPPROTO_TCP;

  //translate the socket

  if( getaddrinfo(host_name, port_number, &hints, &res) !=0 ){
    perror("Failed to translate client socket.");
    exit(EXIT_FAILURE);
  }

  printf("Client socket translated\n");

  for(rec = res; rec!=NULL; rec = rec -> ai_next){
    client_socket = socket(rec -> ai_family, rec->ai_socktype, rec->ai_protocol);
    if(client_socket == -1){
      continue;
    }

    //try and connect
    if( connect(client_socket, rec->ai_addr, rec->ai_addrlen) !=-1){
      break;
    }

    //close the socket so it can try again with another result in the linked list
    close(client_socket);
  }

  if(rec == NULL){
    perror("Failed to create or connect client socket.");
    exit(EXIT_FAILURE);
  }
  freeaddrinfo(res);//free the linked list

  printf("Client socket created and connected\n");
  return client_socket;
}

void handle_client_connection(int client_socket){
  //getting message from the server
  const size_t buffer_size = 1000;
  char buffer[buffer_size];

  if( recv(client_socket, buffer, sizeof(buffer), 0) == -1){
    perror("Failed to receive message from server.");
    exit(EXIT_FAILURE);
  }else{
    printf("Receives message: %s\n", buffer);
  }

  //if message is too long, I could put a while(1) and receive data until it is all fully received
  close(client_socket);
  printf("Connection closed\n");
}
