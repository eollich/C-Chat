#ifndef __MSOCK_CLIENT_H_
#define __MSOCK_CLIENT_H_

#include "msock.h"

#ifdef __cplusplus
extern "C" {
#endif

//CLIENT FUNCTIONS
int setup_client(const char* host_name, const char* port_number);

void handle_client_connection(int client_socket);

#ifdef __cplusplus
}
#endif


#endif
