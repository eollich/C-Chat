#include "msock.h"
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
  if(exp==-1){
    perror(msg);
    exit(EXIT_FAILURE);
  }
  return exp;
}

