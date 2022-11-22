#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define IN 1
#define OUT 0
#define MAXWORD 30

void print (FILE *fp, int *num_M, int *num_m);

int main (int argc, char *argv[]) {

    int opcion_m, opcion_M, num_m, num_M, i, total;
    opcion_m = opcion_M = num_m = num_M = total = 0;
    FILE *fp;
    int c;

    for(i=1;(i<argc) && (opcion_m!=1||opcion_M!=1);i++){
        printf("polla\n");
        if (argv[i][0]=='-'){
            while ((c = *++argv[i])){
                switch (c){
                    case 'm':
                        opcion_m = 1;
                        break;
                    case 'M':
                        opcion_M = 1;
                        break;
                    case '-':
                        printf("-\n");
                        break;
                    default:
                        fprintf(stderr, "[ERROR] Linea de comandos no valida\n");
                        return EXIT_FAILURE;
                }
            }
        }
    }

    if (opcion_M == 1 && opcion_m == 1){
        fprintf(stderr, "[ERROR] Opcion [-m] y [-M] no validas de forma simultanea\n");
        return EXIT_FAILURE;
    }else if (opcion_M == 0 && opcion_m == 0){
        printf("[INFO] No se ha seleccionado un modo, por defecto [-m]\n");
        opcion_m = 1;
    }

    printf("[INFO] Opcion M:%d \t Opcion m:%d\n", opcion_M, opcion_m);

    printf("i:%d\n",i);
    if ((argc - i)==1){
        print(stdin,&num_M,&num_m);
    }else{
        for (i=i; i<argc; i++){
            if ((fp = fopen(argv[i], "r"))== NULL){
                fprintf(stderr, "[ERROR] Error en la apertura del archivo %s\n", argv[i]);
                return EXIT_FAILURE;
            }
            print(fp,&num_M,&num_m);
            fclose(fp);
        }
    }

    if (opcion_M == 1){   
        printf("[INFO] Masyusculas:%d\n", num_M);
    }else if (opcion_m == 1){
        printf("[INFO] Minusculas:%d\n", num_m);
    }
    return EXIT_SUCCESS;
}


void print (FILE *fp, int *num_M, int *num_m){
    int state = IN;
    int c;
    int contador = 0;

    while ((c = fgetc(fp))!=EOF){
        if (c == '\n' || c == '\t' || c == ' '){
            state = OUT;
        }else if (state == IN){
            if (contador == 0){
                if (isupper(c)){
                    *num_M = *num_M + 1;
                }else if (islower(c)){
                    *num_m = *num_m + 1;
                }
            }
            contador++;
        }
        if (state == OUT){
            state = IN;
            contador = 0;
        } 
    }
}
