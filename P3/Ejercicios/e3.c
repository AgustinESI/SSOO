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

    Construir un programa llamado mimv que cambie el nombre de un nodo del sistema de archivos
    (mimv <nodo origen> <nodo destino o directorio>). Si el último argumento de la línea de órdenes
    es un directorio, el nombre del nodo origen estará en el directorio indicado. Se aconseja consultar las
    páginas del manual correspondientes a las llamadas al sistema rename y stat

*/


int main(int argc, char *argv[]){
    
    if (argc<3){
        fprintf(stderr, "[ERROR] Linea de ordenes no valida\n");
        return EXIT_SUCCESS;
    }
    
    char name[MAX_LENGTH+1];
    struct stat st;

    if ((strlen(argv[2])+1)> sizeof(name)){
        fprintf(stderr, "[ERROR] Nombre %s demadiado largo\n", argv[2]);
        return EXIT_FAILURE;
    }
    strcpy(name, argv[2]);

    if (stat (name, &st)==0){
        if (S_ISDIR(st.st_mode)){
            if ((strlen(argv[2] + strlen(argv[1] +2)) > sizeof(name))){
                fprintf(stderr, "[ERROR] Nombre %s → %s demasido largo\n", argv[2], argv[1]);
                return EXIT_FAILURE;
            }
            sprintf(name, "%s/%s\n", argv[2], argv[1]);
        }
    }

    if (rename(argv[1], name)==-1){
        fprintf(stderr, "[ERROR] Nos se ha podido cambiar de nombre\n");
        return EXIT_FAILURE;
    }

    printf("[INFO] %s", argv[2]);

    
    return EXIT_SUCCESS;
}