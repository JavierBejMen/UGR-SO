/*
ejercicio2.c
*/
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<errno.h>
#include <string.h>

#define BLOCK_SIZE 80
char buf[BLOCK_SIZE];
int read_blocks(int);

int main(int argc, char *argv[]){
  int fd;
  int std_read = 1;
  if(argc == 1){
    printf("Se ha seleccionado la entrada estándar como archivo de entrada\n");
    fd = STDIN_FILENO;
    read_blocks(fd);
  }
  else{
    if(argc == 2){
      if( (fd=open(argv[1], O_RDONLY)) < 0){
        printf("\nError %d en open",errno);
        perror("\nError en open");
        exit(EXIT_FAILURE);
      }

      read_blocks(fd);
      if(close(fd) < 0){
        printf("\nError %d en close",errno);
        perror("\nError en close");
        exit(EXIT_FAILURE);
      }
    }
    else{
      printf("\nError, invalid number of arguments\nUso: ejercicio2 [pathname_to_file]");
      exit(EXIT_FAILURE);
    }
  }

  return EXIT_SUCCESS;
}

void close_fd(int fd){
  if(close(fd) < 0){
    printf("\nError %d en close",errno);
    perror("\nError en close");
    exit(EXIT_FAILURE);
  }
}

int read_blocks(int fd){

  int count;
  int eof = 0;
  int fd_out;
  int i=0;
  char buf_w[BLOCK_SIZE+20];

  if((fd_out=open("salida.txt",O_CREAT|O_TRUNC|O_RDWR,S_IRUSR|S_IWUSR))<0) {
    printf("\nError %d en open fd_out",errno);
    perror("\nError en open");
    exit(EXIT_FAILURE);
  }

  for(i = 1; !eof; ++i){
    count = 0;
    count = read(fd, buf, BLOCK_SIZE);
    if(count < 0){
      printf("\nError %d en read",errno);
      perror("\nError en read");
      close_fd(fd_out);
      exit(EXIT_FAILURE);
    }else{
      sprintf(buf_w, "Bloque %i\n%.*s\n", i, count, buf);
      if(write(fd_out, buf_w, strlen(buf_w)) < 0){
        printf("\nError %d en write",errno);
        perror("\nError en write");
        close_fd(fd_out);
        exit(EXIT_FAILURE);
      }

      if(count < BLOCK_SIZE)eof=1;
    }
  }

  int sfd = lseek(fd_out, 0, SEEK_END);

  lseek(fd_out, 0, SEEK_SET);
  char file_copy[sfd];
  read(fd_out, file_copy, sfd);
  lseek(fd_out, 0, SEEK_SET);


  sprintf(buf_w, "El número de bloques es %i\n", i-1);
  if(write(fd_out, buf_w, strlen(buf_w)) < 0){
    printf("\nError %d en write",errno);
    perror("\nError en write");
    close_fd(fd_out);
    exit(EXIT_FAILURE);
  }
  if(write(fd_out, file_copy, sfd) < 0){
    printf("\nError %d en write",errno);
    perror("\nError en write");
    close_fd(fd_out);
    exit(EXIT_FAILURE);
  }


  close_fd(fd_out);
  return EXIT_SUCCESS;
}
