# UGR-SO

Memoria de las prácticas de Sistemas Operativos.

## Índice

+ [Módulo II](#modulo2)
  + [Sesión 1](#sesion1)
    + [Ejercicio 1](#ejer1)
    + [Ejercicio 2](#ejer2)
    + [Ejercicio 3](#ejer3)
    + [Ejercicio 4](#ejer4)
  + [Sesión 2](#sesion2)
    + [Ejercicio 1](#ejer21)
    + [Ejercicio 2](#ejer22)
    + [Ejercicio 3](#ejer23)
    + [Ejercicio 4](#ejer24)
  + [Sesión 3](#sesion3)



---

<a name="modulo2"></a>
## Módulo II

<a name="sesion1"></a>
### Sesión I

<a name="ejer1"></a>
**Ejercicio 1**. ¿Qué hace el siguiente programa? Probad tras la ejecución del programa las siguientes órdenes del shell: `$> cat archivo y $> od -c archivo`

```c
/*
tarea1.c
Trabajo con llamadas al sistema del Sistema de Archivos ''POSIX 2.10 compliant''
*/
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>  	/* Primitive system data types for abstraction\
			   of implementation-dependent data types.
			   POSIX Standard: 2.6 Primitive System Data Types
			   <sys/types.h>
			*/
#include<sys/stat.h>
#include<fcntl.h>
#include<errno.h>

char buf1[]="abcdefghij";
char buf2[]="ABCDEFGHIJ";

int main(int argc, char *argv[])
{
int fd;

if( (fd=open("archivo",O_CREAT|O_TRUNC|O_WRONLY,S_IRUSR|S_IWUSR))<0) {
	printf("\nError %d en open",errno);
	perror("\nError en open");
	exit(EXIT_FAILURE);
}
if(write(fd,buf1,10) != 10) {
	perror("\nError en primer write");
	exit(EXIT_FAILURE);
}

if(lseek(fd,40,SEEK_SET) < 0) {
	perror("\nError en lseek");
	exit(EXIT_FAILURE);
}

if(write(fd,buf2,10) != 10) {
	perror("\nError en segundo write");
	exit(EXIT_FAILURE);
}

return EXIT_SUCCESS;
}
```
Primero el programa abre un archivo de nombre *archivo* con los flags `O_CREAT` para crear el archivo en caso de que no exista, `O_TRUNC` para truncar el archivo a longitud 0 en caso de que ya exista, `O_WRONLY` para especificar el modo escritura, `S_IRUSR` y `S_IWUSR` para garantizar permiso de lectura y escritura, respectivamente, al usuario. Imprimiendo por la salida estándar el número de error en caso de error, almacenado en `errno`.

Luego escribimos en el archivo hasta 10B empezando por la posición a la que referencia `buf1`, en caso de que `write()` devuelva un valor distinto de 10 (el número de bytes que queremos escribir) notificamos el error en la salida de error.

Ahora situamos el offset del archivo a 40B desde el inicio del fichero, flag `SEEK_SET`, esta opción nos permite situarnos en una posición mayor a la longitud actual del fichero, que posteriormente si realizamos una escritura, rellenará las posiciones del fichero inexistentes con el carácter nulo `\0`.

Finalmente escribimos el buffer `buff2` en el fichero.

Tras compilar y ejecutar, realizamos la orden `$> cat archivo` y obtenemos la siguiente salida:

```shell
abcdefghijABCDEFGHIJ
```
Con `cat` no se imprimen los caracteres nulos, ya que no son representables en el formato **ASCII**. Si utilizamos la opción `cat -v archivo` obtenemos una *representación* del carácter nulo:

```shell
abcdefghij^@^@^@^@^@^@^@^@^@^@^@^@^@^@^@^@^@^@^@^@^@^@^@^@^@^@^@^@^@^@ABCDEFGHIJ
```

Hacemos un volcado del archivo `$> od -c archivo`, obteniendo:

```shell
0000000   a   b   c   d   e   f   g   h   i   j  \0  \0  \0  \0  \0  \0
0000020  \0  \0  \0  \0  \0  \0  \0  \0  \0  \0  \0  \0  \0  \0  \0  \0
0000040  \0  \0  \0  \0  \0  \0  \0  \0   A   B   C   D   E   F   G   H
0000060   I   J
0000062
```

Y observamos el contenido del archivo en sus distintas posiciones, que corresponden a los 10 primeros bytes de la primera escritura, 30 bytes con el carácter nulo escritos al definir el offset en 40 bytes y la posterior escritura de 10 bytes.

<a name="ejer2"></a>
**Ejercicio 2**. Implementa un programa que realice la siguiente funcionalidad. El programa acepta como argumento el nombre de un archivo (pathname), lo abre y lo lee en bloques de tamaño 80 Bytes, y crea un nuevo archivo de salida, salida.txt, en el que debe aparecer la siguiente información:
```
Bloque 1
// Aquí van los primeros 80 Bytes del archivo pasado como argumento.

Bloque 2
// Aquí van los siguientes 80 Bytes del archivo pasado como argumento.

...

Bloque n
// Aquí van los siguientes 80 Bytes del archivo pasado como argumento.
```
Si no se pasa un argumento al programa se debe utilizar la entrada estándar como archivo de entrada.

Solución:
```c
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
  if((fd_out=open("salida.txt",O_CREAT|O_TRUNC|O_WRONLY,S_IRUSR|S_IWUSR))<0) {
    printf("\nError %d en open fd_out",errno);
    perror("\nError en open");
    exit(EXIT_FAILURE);
  }

  for(int i = 1; !eof; ++i){
    count = 0;
    count = read(fd, buf, BLOCK_SIZE);
    char buf_w[BLOCK_SIZE+20];
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

  close_fd(fd_out);
  return EXIT_SUCCESS;
}
```
**Modificación adicional**. ¿Cómo tendrías que modificar el programa para que una vez finalizada la escritura en el archivo de salida y antes de cerrarlo, pudiésemos indicar en su primera línea el número de etiquetas ''Bloque i'' escritas de forma que tuviese la siguiente apariencia?:

```
El número de bloques es <nº_bloques>  
Bloque 1  
// Aquí van los primeros 80 Bytes del archivo pasado como argumento.  
Bloque 2  
// Aquí van los siguientes 80 Bytes del archivo pasado como argumento.  
...
```
Situando el `offset` mediante `lseek` al inicio, leemos y copiamos todo el contenido del archivo (cambiamos el flag `O_WRONLY` por `O_RDWR`), y escribimos el número de bloques (sacamos el contador `i` fuera del bucle) y volvemos a escribir todo el contenido copiado.

Solución:

```c
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

```

<a name="ejer3"></a>
**Ejercicio 3**. ¿Qué hace el siguiente programa?

```c
/*
tarea2.c
Trabajo con llamadas al sistema del Sistema de Archivos ''POSIX 2.10 compliant''
*/

#include<unistd.h>  /* POSIX Standard: 2.10 Symbolic Constants <unistd.h>
		     */
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>  /* Primitive system data types for abstraction	\
			   of implementation-dependent data types.
			   POSIX Standard: 2.6 Primitive System Data Types
			   <sys/types.h>
		       */
#include<sys/stat.h>
#include<stdio.h>
#include<errno.h>
#include<string.h>

int main(int argc, char *argv[])
{
int i;
struct stat atributos;
char tipoArchivo[30];

if(argc<2) {
	printf("\nSintaxis de ejecucion: tarea2 [<nombre_archivo>]+\n\n");
	exit(EXIT_FAILURE);
}
for(i=1;i<argc;i++) {
	printf("%s: ", argv[i]);
	if(lstat(argv[i],&atributos) < 0) {
		printf("\nError al intentar acceder a los atributos de %s",argv[i]);
		perror("\nError en lstat");
	}
	else {
		if(S_ISREG(atributos.st_mode)) strcpy(tipoArchivo,"Regular");
		else if(S_ISDIR(atributos.st_mode)) strcpy(tipoArchivo,"Directorio");
		else if(S_ISCHR(atributos.st_mode)) strcpy(tipoArchivo,"Especial de caracteres");
		else if(S_ISBLK(atributos.st_mode)) strcpy(tipoArchivo,"Especial de bloques");
		else if(S_ISFIFO(atributos.st_mode)) strcpy(tipoArchivo,"Tuberia con nombre (FIFO)");
		else if(S_ISLNK(atributos.st_mode)) strcpy(tipoArchivo,"Enlace relativo (soft)");
		else if(S_ISSOCK(atributos.st_mode)) strcpy(tipoArchivo,"Socket");
		else strcpy(tipoArchivo,"Tipo de archivo desconocido");
		printf("%s\n",tipoArchivo);
	}
}

return EXIT_SUCCESS;
}
```

Muestra por la salida estandar el tipo de archivo para cada archivo pasado por parámetro.


<a name="ejer4"></a>
**Ejercicio 4**. Define una macro en lenguaje C que tenga la misma funcionalidad que la macro S_ISREG(mode) usando para ello los flags definidos en <sys/stat.h> para el campo st_mode de la struct stat, y comprueba que funciona en un programa simple. Consulta en un libro de C o en internet cómo se especifica una macro con argumento en C.

```c
#define S_ISREG2(mode)
...
```
Solución:
```c
#define S_ISREG2(mode)  (((mode_t)(mode) & S_IFREG ) ? 1 : 0)
```

---

<a name="sesion2"></a>
### Sesión II

<a name="ejer21"></a>
**Ejercicio 1**. ¿Qué hace el siguiente programa?

```c
/*
tarea3.c
Trabajo con llamadas al sistema del Sistema de Archivos ''POSIX 2.10 compliant''
Este programa fuente est� pensado para que se cree primero un programa con la parte
 de CREACION DE ARCHIVOS y se haga un ls -l para fijarnos en los permisos y entender
 la llamada umask.
En segundo lugar (una vez creados los archivos) hay que crear un segundo programa
 con la parte de CAMBIO DE PERMISOS para comprender el cambio de permisos relativo
 a los permisos que actualmente tiene un archivo frente a un establecimiento de permisos
 absoluto.
*/

#include<sys/types.h>	//Primitive system data types for abstraction of implementation-dependent data types.
						//POSIX Standard: 2.6 Primitive System Data Types <sys/types.h>
#include<unistd.h>		//POSIX Standard: 2.10 Symbolic Constants         <unistd.h>
#include<sys/stat.h>
#include<fcntl.h>		//Needed for open
#include<stdio.h>
#include<errno.h>
#include<stdlib.h>

int main(int argc, char *argv[])
{
int fd1,fd2;
struct stat atributos;

//CREACION DE ARCHIVOS
if( (fd1=open("archivo1",O_CREAT|O_TRUNC|O_WRONLY,S_IRGRP|S_IWGRP|S_IXGRP))<0) {
	printf("\nError %d en open(archivo1,...)",errno);
	perror("\nError en open");
	exit(EXIT_FAILURE);
}

umask(0);
if( (fd2=open("archivo2",O_CREAT|O_TRUNC|O_WRONLY,S_IRGRP|S_IWGRP|S_IXGRP))<0) {
	printf("\nError %d en open(archivo2,...)",errno);
	perror("\nError en open");
	exit(EXIT_FAILURE);
}

//CAMBIO DE PERMISOS
if(stat("archivo1",&atributos) < 0) {
	printf("\nError al intentar acceder a los atributos de archivo1");
	perror("\nError en lstat");
	exit(EXIT_FAILURE);
}
if(chmod("archivo1", (atributos.st_mode & ~S_IXGRP) | S_ISGID) < 0) {
	perror("\nError en chmod para archivo1");
	exit(EXIT_FAILURE);
}
if(chmod("archivo2",S_IRWXU | S_IRGRP | S_IWGRP | S_IROTH) < 0) {
	perror("\nError en chmod para archivo2");
	exit(EXIT_FAILURE);
}

return EXIT_SUCCESS;
}
```
El programa crea dos archivos, asignando permisos de lectura, escritura y ejecución al grupo, seguidamente se leen los atributos del `archivo1`, se desactiva el permiso de ejecución para el grupo y se activa el *Sticky bit*, mientras que al `archivo2` se le asignan los permisos `rwx` al usuario, `rw` al grupo y `r` a otros.
Con la llamada `umask(0)` especificamos que cualquier permiso puede ser modificado.

<a name="ejer22"></a>
**Ejercicio 2**.Realiza un programa en C utilizando las llamadas al sistema necesarias que acepte como entrada:

- Un argumento que representa el 'pathname' de un directorio.
- Otro argumento que es un número octal de 4 dígitos (similar al que se puede utilizar para cambiar los permisos en la llamada al sistema chmod). Para convertir este argumento tipo cadena a un tipo numérico puedes utilizar la función strtol. Consulta el manual en línea para conocer sus argumentos.

El programa tiene que usar el número octal indicado en el segundo argumento para cambiar los permisos de todos los archivos que se encuentren en el directorio indicado en el primer argumento.  
El programa debe proporcionar en la salida estándar una línea para cada archivo del directorio que esté formada por:  
```shell
<nombre_de_archivo> : <permisos_antiguos> <permisos_nuevos>
```
Si no se pueden cambiar los permisos de un determinado archivo se debe especificar la siguiente información en la línea de salida:  
```shell
<nombre_de_archivo> : <errno> <permisos_antiguos>
```

Solución:
```c
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
```
<a name="ejer23"></a>
**Ejercicio 3**. Programa una nueva orden que recorra la jerarquía de subdirectorios existentes a partir de uno dado como argumento y devuelva la cuenta de todos aquellos archivos regulares que tengan permiso de ejecución para el grupo y para otros. Además del nombre de los archivos encontrados, deberá devolver sus números de inodo y la suma total de espacio ocupado por dichos archivos. El formato de la nueva orden será:
```shell
$ ./buscar <pathname>
```
Donde `<pathname>` especifica la ruta del directorio a partir del cual queremos que empiece a analizar la estructura del árbol de subdirectorios. En caso de que no se le de argumento, tomará como punto de partida el directorio actual. Ejemplo de la salida después de ejecutar el programa:
```shell
Los i-nodos son:
./a.out 55
./bin/ej 123
./bin/ej2 87
...
Existen 24 archivos regulares con permiso x para grupo y otros
El tamaño total ocupado por dichos archivos es 2345674 bytes
```

Solución:
```c
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
```
<a name="ejer24"></a>
**Ejercicio 4**. Implementa de nuevo el programa buscar del ejercicio 3 utilizando la llamada al sistema nftw.

Solución:

```c
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
```

---

<a name="sesion3"></a>
### Sesión3

---
