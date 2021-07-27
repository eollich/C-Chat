#ifndef __MSOCK_SERVER_H_
#define __MSOCK_SERVER_H_

#include "msock.h"

#ifdef __cplusplus
extern "C" {
#endif


//SERVER FUNCTIONS

//setup server
int setup_server(const char* port, int backlog);

//accept new connection
int accept_new_connection(int server_socket);

//handle connection
void * handle_connection(int client_socket);

#ifdef __cplusplus
}
#endif

#endif
