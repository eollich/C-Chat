#include "msock_server.h"

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
  check(listen(server_socket, backlog),"Failed to start server socket listen.");
  
  printf("Server started listening on port %s\n", port_number);

  return server_socket;
}

//accept new connection
int accept_new_connection(int server_socket){
  int client_socket;

  struct sockaddr_storage their_addr;//connector's address information
  socklen_t sin_size = sizeof(their_addr);
  char s[INET6_ADDRSTRLEN];

  check( (client_socket = accept(server_socket, (struct sockaddr *)&their_addr, &sin_size)),"Failed to accept client socket.");
    
  

  inet_ntop(their_addr.ss_family, get_in_addr( (struct sockaddr*)&their_addr ), s, sizeof(s) );

  printf("Client socket accepted: %s\n", s);
  return client_socket;
}

//handle connection
//void *handle_connection(int client_socket){
void * handle_connection(int client_socket){
  char buffer[100];

  //if( recv(client_socket, buffer, sizeof(buffer), 0) ==-1){
  //  perror("Error getting client username.");
  //  exit(EXIT_FAILURE);
  //}
  recv(client_socket, buffer, sizeof(buffer),0);
  printf("Username: %s joined!\n", buffer);


  char *msg = "Hello from the server!";

  check( send(client_socket, msg, strlen(msg), 0),"Failed to send message to client.");
  printf("Message sent\n");
  


  //testing to not close to see effect of select comment out below 2 lines
  close(client_socket);
  printf("Client socket closed.\n");
  return strdup(buffer);
}
