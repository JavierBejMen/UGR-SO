#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdio.h>
#include<errno.h>
#include<stdlib.h>
#include<dirent.h>
#include<string.h>
#include<unistd.h>
#include <limits.h>

void closedir_safe(DIR *);
DIR* opendir_safe(char*);

struct file_cont{
  unsigned int n;
  off_t st_size;
};

void buscar_recursivo(char*, struct file_cont *);

int main(int argc, char* argv[]){
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

  struct file_cont fcont;
  fcont.n = 0;
  fcont.st_size = 0;

  printf("Los i-nodos son:\n");
  buscar_recursivo(path, &fcont);
  printf("Existen %u archivos regulares con permiso x para grupo y otros\n", fcont.n);
  printf("El tamaño total ocupado por dichos archivos es %lu bytes\n", fcont.st_size);

  return EXIT_SUCCESS;
}

void buscar_recursivo(char *path, struct file_cont *fcont){
  DIR *dir;
  if( (dir=opendir_safe(path)) != NULL){

    int i = 0;
    struct dirent *dirp;
    struct stat attr;

    for(errno = 0; (dirp=readdir(dir)) != NULL; errno=0, ++i){
      if(errno != 0){
        printf("Error %d en readdir\n",errno);
        perror("Error en readdir\n");
        closedir_safe(dir);
        exit(EXIT_FAILURE);
      }

      char dirp_name_path[PATH_MAX];
      strcpy(dirp_name_path, path);
      strcat(dirp_name_path, dirp->d_name);

      if( strcmp(dirp->d_name, ".")!=0 && strcmp(dirp->d_name, "..")!=0){
        if(lstat(dirp_name_path, &attr) < 0){
          printf("Error %d al intentar acceder a los atributos de %s\n", errno, dirp->d_name);
          perror("Error en lstat\n");
        }else{
          if(S_ISREG(attr.st_mode) && (attr.st_mode & S_IXGRP)!=0 && (attr.st_mode & S_IXOTH)!=0 ){
            printf("%s  %lu\n",  dirp_name_path, attr.st_ino);
            fcont->n += 1;
            fcont->st_size += attr.st_size;
          }else{
            if(S_ISDIR(attr.st_mode)){
              strcat(dirp_name_path, "/");
              buscar_recursivo(dirp_name_path, fcont);
            }
          }
        }
      }
    }
    closedir_safe(dir);
  }
}


DIR* opendir_safe(char *path){
  DIR* dir;
  if( (dir=opendir(path)) == NULL){
    printf("Error %d en opendir(%s)\n", errno, path);
    perror("Error en opendir\n");
    return (DIR *)NULL;
  }

  return dir;
}

void closedir_safe(DIR *dir){
  if( (closedir(dir)) < 0){
    printf("Error %d en closedir\n",errno);
    perror("Error en closedir\n");
    exit(EXIT_FAILURE);
  }
}
