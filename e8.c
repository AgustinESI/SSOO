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

    Construir un programa llamado michmod que cambie los permisos de un nodo del sistema de archivos.
    La sintaxis del programa será michmod <permisos en octal><nodo>. Se aconseja consultar las páginas
    del manual correspondientes a la llamada al sistema chmod y a la función de la biblioteca estándar sscanf

*/

int main(int argc, char *argv[])
{

    unsigned int perm = 0;

    if (argc != 3)
    {
        fprintf(stderr, "[ERROR] Linea de comandos no valida\n");
        return EXIT_FAILURE;
    }


    printf("[INFO] Permisos:%s\n", argv[1]);

    if (sscanf(argv[1], "%o", &perm)!=1){
        fprintf(stderr, "[ERROR] No se ha podido obtener los permisos\n");
        return EXIT_FAILURE;
    }

    printf("[INFO] Permisos:%d\n", perm);

    if (chmod(argv[0],perm)==-1){
        fprintf(stderr, "[ERROR] No se ha podido cambiar los permisos\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}