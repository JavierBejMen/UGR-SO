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
Probar tras la ejecuci�n del programa: $>cat archivo y $> od -c archivo
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
Primero el programa abre un archivo de nombre *archivo* con los flags `O_CREAT` para crear el archivo en caso de que no exista, `O_TRUNC` para truncar el archivo a longitud 0 en caso de que ya exista, `O_WRONLY` para especificar el modo escritura-lectura, `S_IRUSR` y `S_IWUSR` para garantizar permiso de lectura y escritura, respectivamente, al usuario. Imprimiendo por la salida estándar el número de error en caso de error, almacenado en `errno`.

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

------------
