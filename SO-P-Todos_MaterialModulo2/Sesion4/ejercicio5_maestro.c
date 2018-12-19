//maestro.c
#define _GNU_SOURCE

#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>


int main(int argc, char *argv[]){

  //Comprobamos que se pasan el número de argumentos correcto
  if(argc > 4 || argc < 3){
    printf("Uso: %s <intervalo_inicio(int)> <intervalo_fin(int)> [0<n_hijos<=8 : default 2]\n", argv[0]);
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

  //Vector de cauces
  int fd[nP][2];

  //Creación y asignación de los procesos hijo y creación de cauces
  pid_t PID;
  for (size_t i = 0; i < nIntervals-1; i++) {

    //creamos el cauce
    pipe(fd[i]);

    //Creamos el hijo
    if( (PID=fork()) < 0){
      printf("Error %d en fork()\n", errno);
      perror("Error en fork\n");
      exit(EXIT_FAILURE);
    }

    if( PID == 0 ){
      //Ajuste del cauce en hijo
      close(fd[i][0]); //Cerramos el descriptor de lectura
      dup2(fd[i][1], STDOUT_FILENO); //Redireccionamos a la salida estándar

      //Ejecucion
      char param1[30], param2[30];
      if(i == 0){
        sprintf(param1, "%li", intervals[i]);
        sprintf(param2, "%li", intervals[i+1]);
      }else{
        sprintf(param1, "%li", intervals[i]+1);
        sprintf(param2, "%li", intervals[i+1]);
      }

      if( (execlp("/home/zes/Desktop/SO/SO-P-Todos_MaterialModulo2/Sesion4/ejercicio5_esclavo",
      "ejercicio5_esclavo", param1, param2, (char*)NULL)) < 0 ){
        printf("Error %d en execlp()\n", errno);
        perror("Error en exceclp()\n");
        exit(EXIT_FAILURE);
      }

    }else{
      //Ajuste del cauce padre
      close(fd[i][1]); //Cerramos el descriptor de escritura
      dup2(fd[i][0], STDIN_FILENO); //Redireccionamos a la entrada estándar
      if(i == 0){
        printf("Intervalo %lu: [%li, %li] ===> hijo(%u)\n", i+1, intervals[i], intervals[i+1], PID);
      }else{
        printf("Intervalo %lu: [%li, %li] ===> hijo(%u)\n", i+1, intervals[i]+1, intervals[i+1], PID);
      }

      //Recibir números y mostrarlos por consola
      printf("Números primos:\n");
      char buf[20];
      for(size_t i = 0; i < 1;){
        fgets(buf, 20, stdin);
        if(strcmp(buf, "END\n") == 0){
          ++i;
        }else{
          printf("%s", buf);
        }
      }
    }
  }
  
  return EXIT_SUCCESS;
}
