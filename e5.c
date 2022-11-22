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

    Construir un programa llamado mils que imprima por la salida estándar los nombres de los nodos de
    un directorio (mils <directorio>). La impresión en la salida estándar consistirá en un nombre por línea.
    Se aconseja consultar las páginas del manual correspondientes a las llamadas al sistema opendir, readdir
    y closedir

*/

void limpiarNombre(char *nombre);
int main(int argc, char *argv[])
{

    if (argc != 2)
    {
        fprintf(stderr, "[ERROR] Linea de ordenes no valida\n");
        return EXIT_FAILURE;
    }

    DIR *d;
    struct dirent *dir;
    char *name = argv[1];

    limpiarNombre(name);

    if ((d = opendir(argv[1])) == NULL)
    {
        fprintf(stderr, "[ERROR] Error en la apertura del directorio:%s\n", name);
        return EXIT_FAILURE;
    }
    

    while ((dir = readdir(d)) != NULL)
    {
        if (strcmp(dir->d_name, ".") == 0 || strcmp(dir->d_name, "..") == 0)
        {
            continue;
        }

        if (strlen(name) + 1 + strlen(dir->d_name) > MAXBUFFER)
        {
            continue;
        }

        printf("%s/%s\n", name, dir->d_name);
    }

    return EXIT_SUCCESS;
}

void limpiarNombre(char *nombre)
{
    int pos=0;
    pos = strlen(nombre) - 1;
    if (nombre[pos] == '/'){
        nombre[pos] = '\0';
    }
}