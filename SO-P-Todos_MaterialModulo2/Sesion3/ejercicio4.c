#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>
#include<errno.h>
#include <stdlib.h>
#include <sys/wait.h>

#define HIJOS_MAX 5

int main(int argc, char *argv[]){

  unsigned int n_hijos = 0;
  pid_t lastchild;

  do{
    if( (lastchild=fork()) < 0){
      printf("Error %d en fork() %i\n", errno, n_hijos);
      perror("Error en fork()\n");
      exit(EXIT_FAILURE);
    }

    if(lastchild==0){
      printf("Soy el hijo %u\n", getpid());
    }else{
      ++n_hijos;
    }
  }while(n_hijos < HIJOS_MAX && lastchild != 0);

  if(lastchild==0){
    exit(EXIT_SUCCESS);
  }else{
    int waitstatus;
    do{
      if( (lastchild=wait(&waitstatus)) < 0){
        printf("Error %d en wait()\n", errno);
        perror("Error en wait()\n");
        exit(EXIT_FAILURE);
      }else{
        --n_hijos;
        printf("Acaba de finalizar mi hijo %u\n", lastchild);
        printf("Sólo me quedan %u hijos vivos\n", n_hijos);
      }
    }while(n_hijos > 0);
  }

  return EXIT_SUCCESS;
}
