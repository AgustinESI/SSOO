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

    Construir un programa llamado mayor que imprima los nombres de los archivos regulares de un di-
    rectorio, y de sus subdirectorios recursivamente, y los tamaños de los nodos que sean archivos cuyo
    tamaño sea mayor que uno dado (mayor <número><directorio>). La salida consistirá en líneas con
    los nombres de los archivos y los respectivos tamaños (un archivo por línea). Los nombres deberán ser
    nombres relativos al directorio que se pasa como argumento en la línea de órdenes. Se aconseja consultar
    las páginas del manual correspondientes a las llamadas al sistema opendir, readdir, stat y closedir

*/

void ListarDirectorio(const char *name, const int length);

int main(int argc, char *argv[])
{

    int length = 0;
    int i;

    if (argc != 3)
    {
        fprintf(stderr, "[ERROR] Linea de ordenes no valida\n");
        return EXIT_FAILURE;
    }

    while (--argc > 0 && (*++argv)[0] == '-' && isdigit(*++argv[0]))
    {
        length = atoi(argv[0]);
    }

    for (i = 0; i < argc; i++)
    {
        ListarDirectorio(argv[i], length);
    }

    return EXIT_SUCCESS;
}

void ListarDirectorio(const char *name, const int length)
{
    struct stat st;
    struct dirent *nodo;
    DIR *d;
    char buffer[MAXBUFFER + 1];

    if ((d = opendir(name)) == NULL)
    {
        fprintf(stderr, "[ERROR] No se puede abrir el archivo:%s \n", name);
        exit(EXIT_FAILURE);
    }

    while ((nodo = readdir(d)) != NULL)
    {
        if (strcmp(nodo->d_name, ".") == 0 || strcmp(nodo->d_name, "..") == 0)
        {
            continue;
        }

        if (strlen(name) + 1 + strlen(nodo->d_name) > MAXBUFFER)
        {
            continue;
        }

        sprintf(buffer, "%s/%s", name, nodo->d_name);

        if (stat(buffer, &st))
        {
            continue;
        }

        if (S_ISDIR(st.st_mode))
        {
            ListarDirectorio(buffer, length);
        }

        if (S_ISREG(st.st_mode) && ((int)st.st_size) <= length)
        {
            printf("Bytes:%d \tName:%s\n", ((int)st.st_size), nodo->d_name);
        }
    }
    closedir(d);
}