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
    que imprima en la salida estándar los nombres de los archivos regulares ocultos de un directorio o
    de sus subdirectorios (incluyendo aquellos subdirectorios que no se puedan acceder) y tengan un
    tamaño menor que uno dado. La salida consistirá en líneas con los nombres de los archivos
    regulares ocultos y sus respectivos tamaños (un archivo por línea) y la sintaxis del programa será:

    ocultos <numero> <directorio>

    EJECUCIÓN: Anote en la sección RESULTADO el resultado de ejecutar el programa con los
    siguientes argumentos ocultos 1000 /etc y escriba luego el listado del programa en la sección
    denominada LISTADO:(si es necesario continúe al dorso).
*/

void ImprimirDirectorio(const char *name, const int length);

int main(int argc, char *argv[])
{

    int length = 0;
    int i;
    while (--argc > 0 && (*++argv)[0] == '-' && isdigit(*++argv[0]))
    {
        length = atoi(argv[0]);
    }

    for (i = 0; i < argc; i++)
    {
        ImprimirDirectorio(argv[i], length);
    }

    printf("[INFO] Length:%d\n", length);

    return EXIT_SUCCESS;
}

void ImprimirDirectorio(const char *name, const int length)
{

    char buffer[MAXBUFFER];
    DIR *d;
    struct stat st;
    struct dirent *dir;

    if ((d = opendir(name)) == NULL)
    {
        fprintf(stderr, "[ERROR] No se puede abrir el ficher:%s\n", name);
        exit(EXIT_FAILURE);
    }

    while ((dir = readdir(d)) != NULL)
    {
        if (strcmp(dir->d_name, ".") == 0 || strcmp(dir->d_name, "..") == 0)
        {
            continue;
        }

        if ((strlen(name) + 1 + strlen(dir->d_name)) > MAXBUFFER)
        {
            continue;
        }

        sprintf(buffer, "%s/%s", name, dir->d_name);

        printf("Entraa:%s\n", buffer);

        if (stat(buffer, &st) == -1)
        {
            continue;
        }

          if ((S_ISREG(st.st_mode)) && (((int)st.st_size) <= length))
        {
            printf("Bytes:%ld \tName:%s", st.st_size, buffer);
        }

        if (S_ISDIR(st.st_mode))
        {
            ImprimirDirectorio(buffer, length);
        }
    }

    closedir(d);
}