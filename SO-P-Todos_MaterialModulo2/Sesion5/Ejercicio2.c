#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <errno.h>

int sig_count[64];


void sig_USR_hdlr(int sigNum){
  sig_count[sigNum]++;
  printf("La señal %i se ha recibido %i veces\n", sigNum, sig_count[sigNum]);
}

int main(int argc, char *argv[]){

  for(int i=0; i<SIGRTMAX; ++i){
    sig_count[i]=0;
  }

  srand(time(0));
  int n_skip = 1 + rand() % 10;


  struct sigaction sa;
  sa.sa_handler = sig_USR_hdlr;

  if(sigfillset(&sa.sa_mask) != 0){
    perror("\nError al intenar inicializar sa_mask");
    exit(EXIT_FAILURE);
  }

  int s_skip = 0;
  for(int i=0; i<n_skip; ++i){
    s_skip = SIGRTMIN+1 + rand() % SIGRTMAX;
    if(sigdelset(&sa.sa_mask, s_skip) != 0){
      perror("\nError al eliminar señal de sa_mask");
    }else{
      printf("\nLa señal %i es ignorada", s_skip);
    }
  }
}
