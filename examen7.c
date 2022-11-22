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

    mostrar de una lista de directorios el que mas ficheros tenga en el directorio y subdirectorios

*/

void limpiarNombre(char *name);
int contar(const char *name);

int main(int argc, char *argv[])
{

    int max=0;
    char *maxName;

    int i;

    for (i = 1; i < argc; i++)
    {
        char *name = argv[i];
        limpiarNombre(name);
        int num = contar(name);
        if (num >max){
            max = num;
            maxName= name;
        }

    }

    printf("[INFO] Num:%d\t Name:%s\n", max, maxName);

    return EXIT_SUCCESS;
}

int contar(const char *name)
{

    struct stat st;
    struct dirent *nodo;
    DIR *d;
    int contador = 0;
    char buffer[MAXBUFFER + 1];

    if ((d = opendir(name)) == NULL)
    {
        fprintf(stderr, "[ERROR] No se puede abrir el ficher:%s\n", name);
        exit(EXIT_FAILURE);
    }

    while ((nodo = readdir(d)) != NULL)
    {
        if (strcmp(nodo->d_name, ".") == 0 || strcmp(nodo->d_name, "..") == 0)
        {
            continue;
        }

        if (strlen(nodo->d_name) + 1 + strlen(name) > MAXBUFFER)
        {
            continue;
        }

        sprintf(buffer, "%s/%s", name, nodo->d_name);

        if (stat(buffer, &st) == -1)
        {
            fprintf(stderr, "[ERROR] No se pueden obtener los atributos del archivo:%s\n", name);
            exit(EXIT_FAILURE);
        }

        if (S_ISREG(st.st_mode)){
            contador++;
        }

        if (S_ISDIR(st.st_mode)){
            contador+= contar(buffer);
        }
    }

    return contador;
}

void limpiarNombre(char *name)
{

    int pos = strlen(name) - 1;
    if (name[pos] == '/')
    {
        name[pos] = '\0';
    }
}