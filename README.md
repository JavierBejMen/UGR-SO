# UGR-SO

Memoria de las prácticas de Sistemas Operativos.

## Módulo II

### Sesión I
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
El programa abre un archivo de nombre *archivo* con los flags `O_CREAT` para crear el archivo en caso de que no exista, `O_TRUNC` para truncar el archivo a longitud 0 en caso de que ya exista, `O_WRONLY` para especificar el modo escritura-lectura, `S_IRUSR` y `S_IWUSR` para garantizar permiso de lectura y escritura, respectivamente, al usuario.

------------
