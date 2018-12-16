//maestro.c
#define _GNU_SOURCE

#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>


int main(int argc, char *argv[]){

  //Comprobamos que se pasan el número de argumentos correcto
  if(argc != 3){
    printf("Uso: %s <intervalo_inicio(int)> <intervalo_fin(int)>\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  long int interval_i, interval_f;

  //Comprobamos que los argumentos del intervalo son numéricos y los convertimos
  if( (interval_i=strtol(argv[1], (char**)NULL, 10)) == 0 && errno == EINVAL){
    printf("Error %d en strtol(%s)\n", errno, argv[1]);
    perror("Error en strtol()\n");
    exit(EXIT_FAILURE);
  }else{
    if(errno == ERANGE){
      printf("Number %s set to %li\n", argv[1], interval_i);
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

  //Comprobamos que interval_f > interval_i
  if(interval_f <= interval_i){
    printf("Error, <intervalo_inicio(int)> tiene que ser menor que <intervalo_fin(int)>\n");
    exit(EXIT_FAILURE);
  }

  //Creamos los sub-intervalos para los procesos hijoss
  long int interval_m1, interval_m2;
  interval_m2 = interval_i + (interval_f - interval_i)/2;
  interval_m1 = interval_m2++;

  printf("Sub-intervalo 1: [%li, %li]\nSub-intervalo 2: [%li, %li]\n",
    interval_i, interval_m1, interval_m2, interval_f);



  return EXIT_SUCCESS;
}
