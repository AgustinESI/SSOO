/*
    Realizar un programa que cuente los dígitos de un fichero introducido y los muestre por pantalla.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define IN 1
#define OUT 0
#define MAX_NUMBERS 10

int main (int argc, char *argv[]) {

    int numbers[10];
    FILE *fp;
    int i, c;

    if (argc<2){
        fprintf(stderr, "[ERROR] Linea de comandos no valida\n");
        return EXIT_FAILURE;
    }


    for (i=0; i<MAX_NUMBERS;i++){
        numbers[i]=0;
    }

    for (i=1;i<argc;i++){
        if ((fp = fopen(argv[i], "r"))==NULL){
            fprintf(stderr, "[ERROR] No se puede abrir el archivo:%s\n", argv[i]);
            return EXIT_FAILURE;
        }

        while ((c = fgetc(fp))!=EOF){
            if (isdigit(c)){
                int num = c -'0';
                numbers[num]=numbers[num]+1;
            }
        }
    }

    for (i=0; i<MAX_NUMBERS; i++){
        printf("%d esta:%d\n", i,numbers[i]);
    }

    return EXIT_SUCCESS;

}