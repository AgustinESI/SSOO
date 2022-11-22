#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define IN 1
#define OUT 0
#define MAXWORD 30

/*
c caracteres
w palabras
l lineas
*/

void print(FILE *fp, int *cont_c, int *cont_w, int *cont_l);

int main (int argc, char *argv[]) {

    int opcion_c, opcion_w, opcion_l, total, cont_c, cont_w, cont_l, i;
    opcion_c = opcion_w = opcion_l = total = cont_c = cont_w = cont_l = 0;
    FILE *fp;
   
    for (i = 0; i < argc; i++){
        if (argv[i][0]=='-'){
            switch (*++argv[i]){
                case 'c':
                    opcion_c=1;
                    total++;
                    break;
                case 'w':
                    opcion_w=1;
                    total++;
                    break;
                case 'l':
                    opcion_l=1;
                    total++;
                    break;
                default:
                    printf("[ERROR] Opcion no valida\n");
                    return EXIT_FAILURE;
            }
        }
    }

    if ((argc - total )==1){
        print(stdin, &cont_c, &cont_w, &cont_l);
    }else{
        for (i = (total +1); i<argc; i++){
            if ((fp = fopen(argv[i], "r"))== NULL){
                    fprintf(stderr, "[ERROR] No se puede abrir el archivo:%s\n", argv[i]);
                    return EXIT_FAILURE;
            }

            print(fp, &cont_c, &cont_w, &cont_l);
            fclose(fp);
        }
    }

    if (opcion_c == 1 && opcion_w ==0 && opcion_l == 0){
        printf("[INFO] Caracteres:%d\n", cont_c);
    }else if (opcion_c == 0 && opcion_w ==1 && opcion_l == 0){
        printf("[INFO] Palabras:%d\n", cont_w);
    }else if (opcion_c == 0 && opcion_w ==0 && opcion_l == 1){
        printf("[INFO] Lineas:%d\n", cont_l);
    }else if (opcion_c == 1 && opcion_w ==1 && opcion_l == 1){
        printf("[INFO] Caracteres:%d \t\t Palabras:%d \t\t Lineas:%d\n", cont_c, cont_w, cont_l);
    }

   return EXIT_SUCCESS;
}


void print(FILE *fp, int *cont_c, int *cont_w, int *cont_l){
    int c;
    int state = IN;
    while ((c = fgetc(fp))!=EOF){
        if (c == '\n'){
            *cont_l=*cont_l+1;
        }
        *cont_c=*cont_c+1;

        if (c == '\t' || c == '\n' || c == ' '){
            state = OUT;
        }else if (state == IN){
            
        }

        if (state == OUT){
            *cont_w=*cont_w+1;
            state = IN;
        }
    }
}