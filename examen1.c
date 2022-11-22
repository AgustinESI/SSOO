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

    ESPECIFICACIÓN: Utilizando las llamadas al sistema UNIX, construya un programa C estándar
    que concatene el contenido de una lista de archivos en un archivo de destino. La lectura y escritura
    de los archivos se deberá realizar con un buffer de 4096 bytes. Si en la lista de archivos o en el
    archivo de destino se indica el nombre – se entenderá que se debe leer y/o escribir de la entrada
    estándar y/o salida estándar. La sintaxis del programa sera:

    concatenar [<lista de archivos>]+ <archivo destino>

    EJECUCIÓN: Anote en la sección RESULTADO la suma MD5 del contenido del archivo de destino
    salida.txt correspondiente al resultado de ejecutar el programa con los siguientes argumentos
    concatenar /var/test/num* salida.txt y escriba luego el listado del programa en la sección
    denominada LISTADO:(si es necesario continúe al dorso).

*/

void concatenar(int destino, const char *origen_nombre);

int main(int argc, char *argv[])
{

    int i;
    int destino;

    char *destino_nombre = argv[argc - 1];
    printf("[INFO] Destino:%s\n", destino_nombre);

    if ((destino = open(destino_nombre, O_WRONLY | O_RDONLY, O_CREAT, 0664)) == -1)
    {
        fprintf(stderr, "[ERROR] No se puede abrir el archivo de destino\n");
        return EXIT_FAILURE;
    }

    for (i = 1; i < (argc - 1); i++)
    {
        printf("[INFO] File:%s\n", argv[i]);
        concatenar(destino, argv[i]);
    }

    close(destino);

    return EXIT_SUCCESS;
}

void concatenar(int destino, const char *origen_nombre)
{
    int origen;
    struct stat st;
    int numLeidos = 0;
    int numLectura = 0;
    char buffer[MAXBUFFER];

    if ((origen = open(origen_nombre, O_RDONLY)) == -1)
    {
        fprintf(stderr, "[ERROR] No se puede abrir el archivo:%s\n", origen_nombre);
        exit(EXIT_FAILURE);
    }

    if (fstat(origen, &st) == -1)
    {
        fprintf(stderr, "[ERROR] No se pueden obtener los atributos del archivo:%s\n", origen_nombre);
        exit(EXIT_FAILURE);
    }

    while (numLeidos < st.st_size)
    {
        if ((st.st_size - numLeidos) >= MAXBUFFER)
        {
            numLectura = MAXBUFFER;
        }
        else
        {
            numLectura = st.st_size - numLeidos;
        }

        if (lseek(destino, SEEK_SET, SEEK_END) == -1)
        {
            fprintf(stderr, "[ERROR] No se ha podido situar al final del archivo del directorio origen\n");
            exit(EXIT_FAILURE);
        }

        if (read(origen, buffer, numLectura) != numLectura)
        {
            fprintf(stderr, "[ERROR] No se ha podido leer el archivo:%s\n", origen_nombre);
            exit(EXIT_FAILURE);
        }

        if (write(destino, buffer, numLectura) != numLectura)
        {
            fprintf(stderr, "[ERROR] No se ha podido escribir el archivo de origen");
            exit(EXIT_FAILURE);
        }

        numLeidos += numLectura;
    }

    close(origen);
}
