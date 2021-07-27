#include <msock_client.h>

int main(){

  char *host_name = "0.0.0.0";
  char* port_number = "9898";

  int client_socket = setup_client(host_name, port_number);
  handle_client_connection(client_socket);

  return 0;
}
