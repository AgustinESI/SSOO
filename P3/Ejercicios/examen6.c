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
   ESPECIFICACIÓN: Utilizando las llamadas al sistema UNIX, construya un programa C estándar
    que imprima en la salida estándar los nombres de los directorios de la línea de órdenes cuya suma
    total de los archivos regulares que contenga ese directorio (y de sus subdirectorios) sea mayor que
    uno dado. La salida consistirá en líneas con los nombres de los directorios y los respectivos tamaños
    totales (un archivo por línea) y la sintaxis del programa será:

    tamaño -<número>[<directorio>]+

    EJECUCIÓN: Anote en la sección RESULTADO el resultado de ejecutar el programa con los
    siguientes argumentos tamaño – 1000000 /var/log/packages /var/test
    /sbin y
    escriba luego el listado del programa en la sección denominada LISTADO:(Si es necesario continúe
    al dorso).
*/

int contar(const char *name);
void limpiarNombre(char *name);

int main(int argc, char *argv[])
{

    int length = 0;
    int i;

    while (--argc > 0 && (*++argv)[0] == '-' && isdigit(*++argv[0]))
    {
        length = atoi(argv[0]);
    }

    printf("[INFO] Length:%d\n", length);

    for (i = 0; i < argc; i++)
    {
        char *name = argv[i];
        limpiarNombre(name);
        int num;
        if ((num=contar(name)) >=length){
            printf("[INFO]Dir:%s \t\t Bytes:%d\n", name, num);
        }
    }

    return EXIT_SUCCESS;
}

int contar(const char *name)
{

    struct stat st;
    struct dirent *nodo;
    DIR *dir;
    char buffer[MAXBUFFER+1];
    int contador = 0;

    if ((dir = opendir(name))==NULL){
        fprintf(stderr, "[ERROR] No se puede abrir el directorio:%s\n", name);
        exit(EXIT_FAILURE);
    }

    while ((nodo = readdir(dir))!=NULL){

        if (strcmp(nodo->d_name, "..") == 0 || strcmp(nodo->d_name, ".") == 0){
            continue;
        }

        if (strlen(name)+1+strlen(nodo->d_name)>MAXBUFFER){
            continue;
        }

        sprintf(buffer, "%s/%s", name, nodo->d_name);

        if (stat(buffer, &st)==-1){
            continue;
        }

        if (S_ISREG(st.st_mode)){
            contador+=((int) st.st_size);
        }

        if (S_ISDIR(st.st_mode)){
            contador+=contar(buffer);
        }
    }
    return contador;
}

void limpiarNombre(char *name){
    int pos= strlen(name)-1;
    if (name[pos] =='/'){
        name[pos] ='\0';
    }
}