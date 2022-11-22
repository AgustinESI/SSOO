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

    Construir un programa llamado micp2 que copie el contenido de una zona de una lista de archivos en
    la salida estándar. La sintaxis de la línea de órdenes sera:
    
    micp2 -< desplazamiento archivo>:<número bytes> [ <archivo> ] +
    
    La zona de los archivos a copiar se indica con un desplazamiento archivo desde el inicio del archivo y
    con el el n o de bytes a copiar ( número bytes ). Se supondrá que los archivos tienen la zona indicada
    en la línea de órdenes. Se aconseja consultar las páginas del manual correspondientes a las llamadas al
    sistema open, read, write, lseek y close y no utilizar las funciones de la biblioteca estándar C para el
    manejo de la salida estándar

*/

void print(const char *name, const int bytes, const int offset);

int main(int argc, char *argv[]){
    
    int offset;
    int i;
    int bytes;
    char *ptr;

    if (argc<3){
        fprintf(stderr, "[ERROR] Linea de ordenes no valida\n");
        return EXIT_FAILURE;
    }


    if (argv[1][0]!='-'){
        fprintf(stderr, "[ERROR] Linea de ordenes incorrecta\n");
        return EXIT_FAILURE;
    }

    if ((ptr = strchr(argv[1], ':'))==NULL){
        fprintf(stderr, "[ERROR] Linea de ordenes incorrecta\n");
        return EXIT_FAILURE;
    }

    offset = atoi(argv[1]+1);
    bytes=atoi(ptr+1);

    printf("[INFO] Desplazamiento→ %d \t Bytes→ %d\n", offset, bytes);


    for (i = 2; i<argc;i++){
        printf("Fichero:%s\n",argv[i]);
        print(argv[i], bytes, offset);
        printf("\n===========\n");
    }
  
    printf("\n");
    return EXIT_SUCCESS;
}

void print(const char *name, const int bytes, const int offset){
    
    char content[MAX_LENGTH];
    int file;
    int num_leidos=0;
    int num_lectura = 0;

    if ((file = open(name, O_RDONLY))==-1){
        fprintf(stderr, "[ERROR] No se puede abrir el fichero:%s\n", name);
        exit(EXIT_FAILURE);
    }

    if (lseek(file, offset, SEEK_SET)==-1){
        fprintf(stderr, "[ERROR] No se puede posicionar en:%d\n", offset);
        exit(EXIT_FAILURE);
    }

    while (num_leidos < bytes){

        if ((bytes - num_leidos)>= MAX_LENGTH){
            num_lectura = MAX_LENGTH;
        }else{
            num_lectura = bytes - num_leidos;
        }
        if (read(file, content, num_lectura)!=num_lectura){
            fprintf(stderr, "[ERROR] No se ha puede leer el fichero:%s\n", name);
            exit(EXIT_FAILURE);
        }

        if (write(1, content, num_lectura)!=num_lectura){
            fprintf(stderr, "[ERROR] No se pudee escribir en la salida estandar\n");
            exit(EXIT_FAILURE);
        }

        num_leidos+=num_lectura;
    }

    close(file);
}