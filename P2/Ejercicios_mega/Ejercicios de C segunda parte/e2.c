#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define IN 1
#define OUT 0
#define MAX_NUMBERS 10

/*
    Realizar un programa que cuente los caracteres de un fichero y si no se
    introduce fichero, que cuente los de la entrada estándar.
*/

int main (int argc, char *argv[]) {

    int c, i;
    FILE *fp;
    int contador=0;

    if (argc==1){
        while ((c = getchar())!=EOF){
            contador++;

            if (c=='\n'){
                printf("[INFO] Caracteres:%d\n", contador);
            }
        }
    }else{
        for (i = 1; i<argc; i++){
            if ((fp = fopen(argv[i], "r"))== NULL){
                fprintf(stderr,"[ERROR] No se puede abrir el archivo:%s\n", argv[i]);
                return EXIT_FAILURE;
            }

            while ((c = fgetc(fp))!=EOF){
                contador++;
            }

            printf("[INFO] Caracteres:%d\n", contador);
        }
    }


    return EXIT_SUCCESS;

}