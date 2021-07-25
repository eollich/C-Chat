#ifndef __MSOCK_H_
#define __MSOCK_H_


#ifdef __cplusplus
extern "C" {
#endif

//SERVER FUNCTIONS

//setup server
int setup_server(const char* port, int backlog);

//accept new connection
int accept_new_connection(int server_socket);

//handle connection
void *handle_connection(int client_socket);

//handle errors
int check(int exp, const char *msg);

//CLIENT FUNCTIONS
int setup_client(const char* host_name, const char* port_number);

void handle_client_connection(int client_socket);

#ifdef __cplusplus
}
#endif


#endif
