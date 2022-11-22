#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define IN 1
#define OUT 0

void print(const int length, FILE *fp);
int main (int argc, char *argv[]) {

    int total=0;
    int length=0;
    int i;
    FILE *fp;

    for (i =0;i<argc; i++){
        if (argv[i][0]=='-' && isdigit(*++argv[i])){
            length = atoi(argv[i]);
            total++;
        }
    }

    if (length == 0){
        length = 1;
        printf("[INFO] Por defecto se pone:%d\n", length);
    }

    printf("[INFO] Length:%d\n", length);

    if ((argc - total)==1){
        print(length, stdin);
    }else{
        for (i=(total+1); i<argc; i++){
            if ((fp = fopen(argv[i], "r"))==NULL){
                fprintf(stderr, "[ERROR] No se puede abir el fichero:%s\n", argv[i]);
                return EXIT_FAILURE;
            }
            print(length, fp);
            fclose(fp);
        }
    }
    return EXIT_SUCCESS;
}

void print(const int length, FILE *fp){
    int prev_c;
    int contador=1;
    int c;
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