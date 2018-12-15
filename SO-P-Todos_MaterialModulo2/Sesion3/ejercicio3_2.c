#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>
#include<errno.h>
#include <stdlib.h>

#define MAX_CHILD 10

int main(int argc, char *argv[]){

  //Jerarquia tipo 2(solo el proceso sin hijo crea un hijo)

  pid_t pid;
  for(unsigned int i = 0; (i < MAX_CHILD) && (pid=fork()) == 0 ; ++i){

    if(pid == -1){
      printf("Error %d en fork() %i\n", errno, i);
      perror("Error en fork()\n");
      exit(EXIT_FAILURE);
    }
  }

  printf("PID %u, PPID %u\n", getpid(), getppid());
  return EXIT_SUCCESS;
}
