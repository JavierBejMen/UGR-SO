#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<math.h>

int es_primo(long int);

int main(int argc, char *argv[]){
  if(argc != 3){
    printf("Uso: %s <intervalo_inicio> <intervalo_fin>\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  long int interval_i, interval_f;

  if( (interval_i=strtol(argv[1], (char**)NULL, 10)) == 0 && errno == EINVAL){
    printf("Error %d en strtol(%s)\n", errno, argv[1]);
    perror("Error en strtol()\n");
    exit(EXIT_FAILURE);
  }else{
    if(errno == ERANGE){
      printf("Number %s set to %li\n", argv[1], interval_f);
      perror("Error en strtol()\n");
      errno=0;
    }
  }

  if( (interval_f=strtol(argv[2], (char**)NULL, 10)) == 0 && errno == EINVAL){
    printf("Error %d en strtol(%s)\n", errno, argv[2]);
    perror("Error en strtol()\n");
    exit(EXIT_FAILURE);
  }else{
    if(errno == ERANGE){
      printf("Number %s set to %li\n", argv[2], interval_f);
      perror("Error en strtol()\n");
      errno=0;
    }
  }
  for(long int i = interval_i; i < interval_f; ++i){
    if(es_primo(i)){
      printf("%li\n", i);
    }
  }
  printf("END\n");
  return EXIT_SUCCESS;
}

int es_primo(long int n){

  long int max = (long int)sqrt(n);
  for(long int i = 2; i <= max; ++i){
    if(n%i == 0){
      return 0;
    }
  }

  return 1;
}
