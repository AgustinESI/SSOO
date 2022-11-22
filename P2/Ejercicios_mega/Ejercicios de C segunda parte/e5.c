/*

    Realizar un programa que imite el comando HEAD, el programa recibirá una opción –x donde x es el número de
    líneas a mostrar, si no se indica nada mostrara las 3 primeras líneas.
    Headc [-<n>] [<fichero>]+

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define IN 1
#define OUT 0
#define MAX_NUMBERS 10

void print(const char length, FILE *fp);

int main (int argc, char *argv[]) {

    int i;
    FILE *fp;
    int length=0;
    int opcion=0;

    for (i = 0; i<argc; i++){
        if (argv[i][0]=='-' && isdigit(*++argv[i])){
            length = atoi(argv[i]);
            opcion++;
        }
    }

    if (length == 0){
        length = 3;
        printf("[INFO] Por defecto se establece:%d\n",length);
    }

    printf("[INFO] Length:%d\n",length);

    if ((argc-opcion) == 1){
        print(length, stdin);
    }else{
        for (i = (opcion+1); i<argc;i++){
            if ((fp = fopen(argv[i], "r"))==NULL){
                printf("[ERROR] No se puede abrir el archivo:%d\n",length);
            }
            print(length, fp);
            fclose(fp);
        }
    }
    return EXIT_SUCCESS;
}


void print(const char length, FILE *fp){
    int contador=0;
    int c;
    while ((c = fgetc(fp))!=EOF && contador < length){
        if (c == '\n'){
            contador++;
        }
        putchar(c);
    }
}