#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>

#define MAX_LENGTH 4096
#define true 1
#define false 0

/*

    Construir un programa llamado micp que copie el contenido de un archivo de entrada en otro de salida

    ( micp <archivo entrada><archivo salida> ). 
    
    Se aconseja consultar las páginas del manual correspon-
    dientes a las llamadas al sistema open, creat, read, write y close

*/


int main(int argc, char *argv[]){
    char buffer[MAX_LENGTH];
    int origen, destino;
    int numLeidos;

    if (argc!=3){
        fprintf(stderr, "[ERROR] Linea de ordenes no valida\n");
        return EXIT_FAILURE;
    }

    if ((origen = open(argv[1], O_RDONLY))==-1){
        fprintf(stderr, "[ERROR] No se puede abrir el archivo:%s\n", argv[1]);
        return EXIT_FAILURE;
    }

    if ((destino = open(argv[argc-1], O_WRONLY|O_CREAT|O_TRUNC))==-1){
        fprintf(stderr, "[ERROR] No se puede abrir el archivo:%s\n", argv[argc-1]);
        return EXIT_FAILURE;
    }

    while ((numLeidos=read(origen, buffer, sizeof(buffer)))>0){
        if (write(destino, buffer, numLeidos)!=numLeidos){
             fprintf(stderr, "[ERROR] No se puede escribir\n");
            return EXIT_FAILURE;
        }
    }

    if (numLeidos == -1){
        fprintf(stderr, "[ERROR] No se puede leer\n");
        return EXIT_FAILURE;
    }

    close(origen);
    close(destino);

    return EXIT_SUCCESS;
}