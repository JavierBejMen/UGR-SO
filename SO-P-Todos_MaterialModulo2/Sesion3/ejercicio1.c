#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include<errno.h>
#include<stdlib.h>

int _multiplo_4(long int n){
  if(n % 4 == 0){
    return 1;
  }else{
    return 0;
  }
}

int _par(long int n){
  if(n % 2 == 0){
    return 1;
  }else{
    return 0;
  }
}

int main(int argc, char *argv[]){

  if(argc != 2){
    printf("Uso: %s <long_int>\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  long int n;

  if( (n=strtol(argv[1], (char**)NULL, 10)) == 0 && errno != 0 ){
    printf("Error %d en strtol(%s)\n",errno, argv[1]);
    perror("Error en strtol\n");
    exit(EXIT_FAILURE);
  }
  printf("El numero %li:\n", n);

  pid_t pid;
  pid=fork();

  if(pid==0){
    if(_par(n)){
      printf("(%i) es par\n", pid);
    }else{
      printf("(%i) es impar\n", pid);
    }
  }else{
    if(_multiplo_4(n)){
      printf("(%i) es multiplo de 4\n", pid);
    }else{
      printf("(%i) no es multiplo de 4\n", pid);
    }
  }

  return EXIT_SUCCESS;
}
