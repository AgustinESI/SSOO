/*

    Crear un programa llamado sustituir que imprima en la
    salida estándar el contenido del fichero según las
    siguientes opciones:
    -a El programa sustituirá los dígitos por el carácter ‘@’
    -A El programa sustituirá los dígitos por el carácter ‘#’
    -M El programa mostrara todo en mayúsculas
    -m el programa mostrara todo en minúsculas
    Las opciones –a y –A son incompatibles, al igual que las
    opciones –m y –M
    Si no se pone ninguna opción, se imprimirá el fichero tal
    cual.
    La sintaxis en la línea de ordenes será:
    Sustituir [-m] [-M] [-a] [-A] [<archivo>]+

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define IN 1
#define OUT 0
#define MAX_NUMBERS 10


/*
    Realizar un programa que implemente la función del comando cat
*/

void print(FILE *fp);

int main (int argc, char *argv[]) {

    FILE *fp;
    int i;

    if (argc == 1){
        print(stdin);
    }else{
        for (i=0; i<argc; i++){
            if ((fp = fopen(argv[i], "r"))==NULL){
                fprintf(stderr, "[ERROR] No se puede abrir el archivo %s\n", argv[i]);
                return EXIT_FAILURE;
            }
            print(fp);
        }
    }

    return EXIT_SUCCESS;
}

void print(FILE *fp){
    int c;
    while ((c = fgetc(fp))!=EOF){
        putchar(c);
    }
}