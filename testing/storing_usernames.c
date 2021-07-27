#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(){

  int user_count=0;
  char **users;

  char *buff = NULL;
  size_t len = 0;

  while(1){

    while( printf("enter a username: ") && getline( &buff, &len, stdin) > 1 ){


      /* overwrite newline */
      buff[ strlen(buff)-1 ] = '\0' ;


      user_count++;

      if(user_count == 1){
        users = malloc(sizeof(char*)); 
      }
      else{
        users = realloc(users, sizeof(char*) * user_count);
      }

      *(users+user_count-1) = strdup(buff);

      for(int i=0; i<user_count; i++){
        printf("Users %d: %s\n", i+1, *(users+i));
      }

    }

    free(buff);
    for(int i=0; i<user_count; i++){
      free(*(users+i));
    }
    free(users);
    break;
  }


  users++;
  return 0;
}
