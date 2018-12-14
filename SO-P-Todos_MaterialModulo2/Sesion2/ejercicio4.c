#define _XOPEN_SOURCE 500
#include<ftw.h>

#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>
#include<limits.h>

struct file_cont{
  unsigned int n;
  off_t st_size;
}global_fcont;

int buscar(const char*, const struct stat*, int, struct FTW*);

/*int nftw (const char *dirpath, int (*func) (const char *pathname, const struct stat *statbuf,
 int typeflag, struct FTW *ftwbuf), int nopenfd, int flags);*/

int main(int argc, char *argv[]){

  char path[PATH_MAX];

  if(argc > 2){
    printf("Uso: %s [<path_name/>]\n", argv[0]);
    exit(EXIT_FAILURE);
  }else{
    if(argc == 1){
      if( (getcwd(path, PATH_MAX)) == NULL ){
        printf("Error %d en getcwd()\n", errno);
        perror("Error en getcwd()\n");
        exit(EXIT_FAILURE);
      }
      strcat(path, "/");
    }else{
      strcpy(path, argv[1]);
    }
  }

  printf("%s\n", path);

  struct file_cont *fcont = &global_fcont;
  fcont->n=0;
  fcont->st_size=0;

  printf("Los i-nodos son:\n");
  if( (nftw(path, buscar, 10, 0)) != 0){
    perror("Error en nftw()\n");
    exit(EXIT_FAILURE);
  }
  printf("Existen %u archivos regulares con permiso x para grupo y otros\n", fcont->n);
  printf("El tamaño total ocupado por dichos archivos es %lu bytes\n", fcont->st_size);

  return EXIT_SUCCESS;
}

int buscar(const char* path, const struct stat* stat, int flags, struct FTW* ftw){
  struct file_cont *fcont = &global_fcont;
  if((flags & FTW_D)==0){
    if(S_ISREG(stat->st_mode) && (stat->st_mode & S_IXGRP)!=0 && (stat->st_mode & S_IXOTH)!=0 ){
      printf("%s  %lu\n",  path, stat->st_ino);
      fcont->n += 1;
      fcont->st_size += stat->st_size;
    }
  }
  return 0;
}
