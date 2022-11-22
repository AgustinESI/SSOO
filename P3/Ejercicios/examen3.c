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
#define true 1
#define false 0

/*
    ESPECIFICACION: Utilizando las llamadas al sistema UNIX, construya un programa C estándar
    que cree un enlace duro a cada archivo de la línea de órdenes con un nombre para el nuevo enlace
    duro que sea la concatenación del nombre del archivo original, el carácter . y el sufijo indicado en la
    línea de comandos. Si no se indica un sufijo en la línea de órdenes se utilizará el sufijo hard. La
    sintaxis del programa será:
   
    duro[-<sufijo>] [nombre]*
   
    EJECUCIÓN: Desde el directorio home del usuario alumno copie el contenido del directorio
    /var/test en el subdirectorio test y ejecute el programa con los siguientes argumentos duro –hd
    test/r* comprobando que realiza la funcionalidad requerida y escribe luego el listado del
    programa en la sección denominada LISTADO:(Si es necesario continúe al dorso).

*/


void create_link(const char *name, const char *sufix);

int main(int argc, char *argv[]){

    char *sufix = "hard";
    int i;
    while (--argc>0 && (*++argv)[0]=='-'){
        sufix = ++argv[0];
    }

    for (i=0; i<argc;i++){
        create_link(argv[i], sufix);
    }

    return EXIT_SUCCESS;
}

void create_link(const char *name, const char *sufix){

    char buffer[MAXBUFFER+1];

    if ((strlen(name)+1+strlen(sufix))>MAXBUFFER){
        fprintf(stderr, "[ERROR] Nombre demasiado largo %s.%s", name, sufix);
        exit(EXIT_FAILURE);
    }

    sprintf(buffer, "%s.%s", name, sufix);

    link(name, buffer);
}