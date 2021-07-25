#include <msock.h>

int main(){

  const char *port_number = "9898";
  const int backlog = 10;

  int server_socket = setup_server(port_number, backlog);

  //loop for connections
  while(1){
    int client_socket = accept_new_connection(server_socket);
    handle_connection(client_socket);
  }

  return 0;
}
