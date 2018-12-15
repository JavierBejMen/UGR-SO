#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<stdio.h>
#include<errno.h>
#include<stdlib.h>
#include<string.h>

int main(int argc, char *argv[]){

  if(argc < 2){
    printf("Uso: %s <path_programa> [<program_name>...<argumento_n>] [<bg>]\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  int bg=0;
  if(strcmp(argv[argc-1], "bg") == 0){
    bg=1;
    printf("Background option detected\n" );
  }

  int err_exec;
  char *params[argc-1];

  if(bg){
    for(int i = 0; i < argc-3; ++i){
      params[i]=argv[i+2];
    }

    params[argc-3] = "&";
  }else{
    for(int i = 0; i < argc-2; ++i){
      params[i] = argv[i+2];
    }
  }

  params[argc-2]=(char*)NULL;



  if( (err_exec=execv(argv[1], params)) < 0){
    printf("Error %d en execv()\n", errno);
    perror("Error en execl()\n");
    exit(EXIT_FAILURE);
  }

  return EXIT_SUCCESS;
}
