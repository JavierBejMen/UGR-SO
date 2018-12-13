#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdio.h>
#include<errno.h>
#include<stdlib.h>
#include<dirent.h>
#include<string.h>

void closedir_safe(DIR*);

int main(int argc, char *argv[]){
  size_t name_len = strlen(argv[0])-2;
  char name[name_len];
  char *name_p = &argv[0][2];
  sprintf(name,"%.*s", (int)name_len, name_p);

  if(argc != 3){
    printf("Sintaxis de ejecucion: %s <nombre_directorio> <mascara_octal_4d>\n\n"
    , argv[0]);

    exit(EXIT_FAILURE);
  }

  long int mask;
  if((mask=strtol(argv[2], (char**)NULL, 8)) == 0 && argv[2] != 0 ){
    printf("Error %d en strtol(%s)\n",errno, argv[2]);
    perror("Error en strtol\n");
    exit(EXIT_FAILURE);
  }
  //printf("mask: %li\n", mask);

  DIR* dir;

  if( (dir=opendir(argv[1])) == NULL ){
    printf("Error %d en opendir(%s)\n",errno, argv[1]);
    perror("Error en opendir\n");
    exit(EXIT_FAILURE);
  }

  struct dirent *dirp;
  struct stat attr;
  unsigned int permisos_antiguos;

  int i = 0;
  for(errno = 0; (dirp=readdir(dir)) != NULL; errno = 0, ++i){
    if(errno != 0){
      printf("Error %d en readdir\n",errno);
      perror("Error en readdir\n");
      exit(EXIT_FAILURE);
    }

    if( strcmp(dirp->d_name, ".")!=0 && strcmp(dirp->d_name, "..")!=0 && strcmp(dirp->d_name, name)!=0){
      if(lstat(dirp->d_name, &attr) < 0){
        printf("Error %d al intentar acceder a los atributos de %s\n", errno, dirp->d_name);
        perror("Error en lstat\n");
      }else{
        permisos_antiguos = ((attr.st_mode & S_IRUSR)|(attr.st_mode & S_IWUSR)|(attr.st_mode & S_IXUSR)|/*owner*/
        (attr.st_mode & S_IRGRP)|(attr.st_mode & S_IWGRP)|(attr.st_mode & S_IXGRP)|/*group*/
        (attr.st_mode & S_IROTH)|(attr.st_mode & S_IWOTH)|(attr.st_mode & S_IXOTH));/*other*/
        if( chmod(dirp->d_name, mask) < 0 ){
          printf("Error %d en chmod para %s\n", errno, dirp->d_name);
          printf("%s : <%d> <%.4o>\n", dirp->d_name, errno, permisos_antiguos);
        }else{
          printf("%s : <%.4o> <%.4o>\n", dirp->d_name, permisos_antiguos, (unsigned int)mask);
        }
      }
    }

  }


  closedir_safe(dir);
  return EXIT_SUCCESS;
}

void closedir_safe(DIR* dir){
  if(closedir(dir) < 0){
    printf("Error %d en closedir\n",errno);
    perror("Error en closedir\n");
    exit(EXIT_FAILURE);
  }
}
