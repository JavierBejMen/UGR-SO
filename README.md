# UGR-SO

Memoria de las prácticas de Sistemas Operativos.

## Índice

+ [Módulo II](#modulo2)
  + [Sesión 1](#sesion1)
    + [Ejercicio 1](#ejer1)
    + [Ejercicio 2](#ejer2)
  + Sesión 2



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







------------
