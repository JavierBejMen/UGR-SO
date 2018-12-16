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
  if(argc > 4){
    printf("Uso: %s <intervalo_inicio(int)> <intervalo_fin(int)> [0<n_Paralelismo<=8 : default 2]\n", argv[0]);
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
  int nP;

  if(argc == 4){
    if( (nP=strtol(argv[3], (char**)NULL, 10)) == 0 && errno == EINVAL){
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

    if(nP <= 0 | nP > 8){
      printf("Paralelismo por defecto: 2\n");
      nP = 2;
    }
  }else{
    printf("Paralelismo por defecto: 2\n");
    nP = 2;
  }

  size_t nIntervals = nP+1;
  long int intervals[nIntervals];
  long int mid_interval = (interval_f - interval_i)/nP;
  intervals[0] = interval_i;
  intervals[nIntervals-1] = interval_f;
  for(size_t i = 1; i < nIntervals-1; ++i){
    intervals[i] = intervals[i-1] + mid_interval;
  }

  for (size_t i = 0; i < nIntervals-1; i++) {
    if(i == 0){
      printf("Intervalo %lu: [%li, %li]\n", i+1, intervals[i], intervals[i+1]);
    }else{
      printf("Intervalo %lu: [%li, %li]\n", i+1, intervals[i]+1, intervals[i+1]);
    }
  }

  //Creación de cauces sin nombre
  int fd_in[2], fd_out[2];
  pipe(fd_in); //Cauce esclavos>>maestro
  pipe(fd_out); //Cauce maestro>>esclavos

  //Creación y asignación de los procesos hijo
  pid_t PID;
  for (size_t i = 0; i < nIntervals-1; i++) {
    if(i == 0){
      printf("Intervalo %lu: [%li, %li]\n", i+1, intervals[i], intervals[i+1]);
    }else{
      printf("Intervalo %lu: [%li, %li]\n", i+1, intervals[i]+1, intervals[i+1]);
    }
  }



  return EXIT_SUCCESS;
}
