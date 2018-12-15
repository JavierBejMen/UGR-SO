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
  pid_t hijos[HIJOS_MAX];

  do{
    if( (lastchild=fork()) < 0){
      printf("Error %d en fork() %i\n", errno, n_hijos);
      perror("Error en fork()\n");
      exit(EXIT_FAILURE);
    }

    if(lastchild==0){
      printf("Soy el hijo %u\n", getpid());
    }else{
      hijos[n_hijos]=lastchild;
      ++n_hijos;
    }
  }while(n_hijos < HIJOS_MAX && lastchild != 0);

  if(lastchild==0){
    exit(EXIT_SUCCESS);
  }else{
    int waitstatus;
    //Hijos impares(0, 2, 4)
      if( (lastchild=waitpid(hijos[0], &waitstatus, 0)) < 0){
        printf("Error %d en wait()\n", errno);
        perror("Error en wait()\n");
        exit(EXIT_FAILURE);
      }else{
        if(lastchild > 0){
          --n_hijos;
          printf("Acaba de finalizar mi hijo %u (1)\n", lastchild);
          printf("Sólo me quedan %u hijos vivos\n", n_hijos);
        }
      }

      if( (lastchild=waitpid(hijos[2], &waitstatus, 0)) < 0){
        printf("Error %d en wait()\n", errno);
        perror("Error en wait()\n");
        exit(EXIT_FAILURE);
      }else{
        if(lastchild > 0){
          --n_hijos;
          printf("Acaba de finalizar mi hijo %u (3)\n", lastchild);
          printf("Sólo me quedan %u hijos vivos\n", n_hijos);
        }
      }

      if( (lastchild=waitpid(hijos[4], &waitstatus, 0)) < 0){
        printf("Error %d en wait()\n", errno);
        perror("Error en wait()\n");
        exit(EXIT_FAILURE);
      }else{
        if(lastchild > 0){
          --n_hijos;
          printf("Acaba de finalizar mi hijo %u (5)\n", lastchild);
          printf("Sólo me quedan %u hijos vivos\n", n_hijos);
        }
      }

    do{ //Hijos pares(resto)
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
