#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define IN 1
#define OUT 0

void print(FILE *fp, const int length);
int main (int argc, char *argv[]) {

    int i;
    int length=-1;
    int arguments=0;
    FILE *fp;

    for (i = 0; i<argc; i++){
        if (argv[i][0]=='-' && isdigit(*++argv[i])){
            if (length == -1){
                length = atoi(argv[i]);
                arguments++;
            }else{
                fprintf(stderr, "[ERROR] No se puede introducir mas de un numero\n");
                return EXIT_FAILURE;
            }
        }
    }

    if (length == 0){
        length = 1;
    }

    printf("[INFO] Length:%d\n",length);

    if ((argc - arguments)==1){
        print(stdin, length);
    }else{
        for (i=(arguments+1); i<argc;i++){
            if ((fp = fopen(argv[i], "r"))==NULL){
                fprintf(stderr, "[ERROR] No se puede abrir el archivo:%s\n", argv[i]);
                return EXIT_FAILURE;
            }

            print(fp, length);
            fclose(fp);
        }
    }
    printf("\n");
   return EXIT_SUCCESS;
}

void print(FILE *fp, const int length){
    int c;
    int contador=0;
    char prev_c;
    
    while ((c = fgetc(fp))!=EOF){       
        if (c == prev_c){
            contador++;
        }else{
            contador=1;
        }
        if (contador<=length){
            putchar(c);
        }
        prev_c = c;
    }
}