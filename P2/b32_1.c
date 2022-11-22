#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define IN 1
#define OUT 0


void print(FILE *fp, int *cont_M, int *cont_m);
int main (int argc, char *argv[]) {

    int i;
    int opcion_m =0;
    int opcion_M =0;
    int cont_m = 0;
    int cont_M = 0;
    int total = 0;
    FILE *fp;


    for (i=0; i<argc; i++){
        if (argv[i][0]=='-'){
            switch(*++argv[i]){
                case 'M':
                    opcion_M = 1;
                    total++;
                    break;
                case 'm':
                    opcion_m = 1;
                    total++;
                    break;
                default :
                    fprintf(stderr, "[ERROR] Modo de ejecucion no valido\n");
                    return EXIT_FAILURE;
            }
        }
    }

    if (opcion_M == 0 && opcion_m == 0){
        opcion_m = 1;
    }else if (opcion_M == 1 && opcion_m == 1){
        fprintf(stderr, "[ERROR] Modo de ejecucion no valido\n");
        return EXIT_FAILURE;
    }

    printf("[INFO] Minuculas:%d \t Mayusculas:%d\n", opcion_m, opcion_M);

    if ((argc-total)==1){
        print(stdin, &cont_M, &cont_m);
    }else{
        for (i = (total+1);i<argc; i++){
            if ((fp = fopen(argv[i],"r"))== NULL){
                fprintf(stderr, "[ERROR] No se puede abrir el archivo:%s\n", argv[i]);
                return EXIT_FAILURE;
            }
            print(fp, &cont_M, &cont_m);
            fclose(fp);
        }
    }

    if (opcion_M == 1){
        printf("[INFO] Mayusuclas:%d\n", cont_M);
    }else if (opcion_m == 1){
        printf("[INFO] Minusculas:%d\n", cont_m);
    }

    return EXIT_SUCCESS;
}

void print(FILE *fp, int *cont_M, int *cont_m){

    int c;
    int contador = 0;
    int state = IN;
    while ((c = fgetc(fp))!=EOF){
        if (c == '\n' || c == ' ' || c == '\t'){
            state = OUT;
        }else if (state == IN){
            if (contador == 0 && isupper(c)){
                *cont_M=*cont_M+1;
            }else if (contador == 0 && islower(c)){
                *cont_m=*cont_m+1;
            }
            contador++;
        }

        if (state == OUT){
            contador =0;
            state = IN;
        }
    } 
}
