#include "msock.h"

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

  check( recv(client_socket, buffer, sizeof(buffer), 0),"Failed to receive message from server." );
    

  printf("Receives message: %s\n", buffer);

  //if message is too long, I could put a while(1) and receive data until it is all fully received
  close(client_socket);
  printf("Connection closed\n");
}
