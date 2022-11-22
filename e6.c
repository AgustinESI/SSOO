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

    Construir un programa mitree que imprima los nombres de los nodos de un directorio cuyo nombre se
    pasa por la línea de órdenes. El programa debe admitir la presencia en la línea de órdenes, de una opción
    -R que, cuando esté presente indique que el listado del directorio debe ser recursivo (mitree [<-R>]
    <directorio>). Se supondrá que en el directorio (y en sus descendientes) no hay enlaces simbólicos. La
    impresión en la salida estándar consistirá en un nombre por línea. Los nombres deberán ser nombres
    relativos al directorio que se pasa como argumento en la línea de órdenes. Se aconseja consultar las
    páginas del manual correspondientes a las llamadas al sistema opendir, readdir, stat y closedir

*/

void leerDirectorio(const char *name, int opcion_m);
void limpiarNombre(char *nombre);

int main(int argc, char *argv[])
{

    int opcion_m = 0;
    while (--argc > 0 && (*++argv)[0] == '-')
    {
        switch (*++argv[0])
        {
        case 'R':
            opcion_m = 1;
            break;
        default:
            fprintf(stderr, "[ERROR] Opcion no valida\n");
            return EXIT_FAILURE;
        }
    }

    printf("[INFO] Opcion:%d\n", opcion_m);

    char *name = argv[0];
    limpiarNombre(name);
    leerDirectorio(name, opcion_m);

    return EXIT_SUCCESS;
}

void leerDirectorio(const char *name, int opcion_m)
{

    struct stat st;
    struct dirent *nodo;
    DIR *d;
    char buffer[MAXBUFFER + 1];

    if ((d = opendir(name)) == NULL)
    {
        fprintf(stderr, "[ERROR] No se puede abrir el directorio:%s\n", name);
        exit(EXIT_FAILURE);
    }

    while ((nodo = readdir(d)) != NULL)
    {
        if (strcmp(nodo->d_name, ".") == 0 || strcmp(nodo->d_name, "..") == 0)
        {
            continue;
        }

        if ((strlen(name)+1+strlen(nodo->d_name))>MAXBUFFER){
            continue;
        }

        sprintf(buffer, "%s/%s", name, nodo->d_name);


        if ((stat(buffer, &st))==-1){
            continue;
        }


        if (S_ISREG(st.st_mode)){
            printf("Name:%s\n", buffer);
        }
        if (S_ISDIR(st.st_mode) && opcion_m == 1){
            leerDirectorio(buffer, opcion_m);
        }

    }
}

void limpiarNombre(char *nombre)
{
    int pos = 0;
    pos = strlen(nombre) - 1;
    if (nombre[pos] == '/')
    {
        nombre[pos] = '\0';
    }
}