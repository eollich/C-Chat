#ifndef __MSOCK_H_
#define __MSOCK_H_

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <arpa/inet.h>


#ifdef __cplusplus
extern "C" {
#endif

void *get_in_addr(struct sockaddr *sa);

//handle errors
int check(int exp, const char *msg);


#ifdef __cplusplus
}
#endif


#endif
