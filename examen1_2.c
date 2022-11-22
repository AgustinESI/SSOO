#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>

#define MAXBUFFER 4096

/*

    ESPECIFICACIÓN: Utilizando las llamadas al sistema UNIX, construya un programa C estándar
    que concatene el contenido de una lista de archivos en un archivo de destino. La lectura y escritura
    de los archivos se deberá realizar con un buffer de 4096 bytes. Si en la lista de archivos o en el
    archivo de destino se indica el nombre – se entenderá que se debe leer y/o escribir de la entrada
    estándar y/o salida estándar. La sintaxis del programa sera:

    concatenar [<lista de archivos>]+ <archivo destino>

    EJECUCIÓN: Anote en la sección RESULTADO la suma MD5 del contenido del archivo de destino
    salida.txt correspondiente al resultado de ejecutar el programa con los siguientes argumentos
    concatenar /var/test/num* salida.txt y escriba luego el listado del programa en la sección
    denominada LISTADO:(si es necesario continúe al dorso).

*/

void concatenar(const char destino_name, const int destino_name, int flag);

int main(int argc, char *argv[])
{


		int destino_fd;
		char *destino_name = argv[argc-1];
		int flag = 0;

		if (destino_name[0]=='-'){
			flag = 1;
			++destino_name;
		}

		if ((destino_fd = open(destino_name, O_CREAT|O_TRUNC|O_WRONLY, 0664))==-1){
			fprintf(stderr, "No se puede abrir el archivo:%s\n", destino_name);
			return EXIT_FAILURE;
		}

		printf("[INFO] Flag:%d \t Name:%s\n",destino_name);


		for (i = 1; i<argc-1; i++){
			concatenar(argv[i], destino_fd, flag);
		}

		return EXIT_SUCCESS;
}



void concatenar(const char origen_name, const int destino_fd, int falg){
		
}
