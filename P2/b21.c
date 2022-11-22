#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define IN 1
#define OUT 0
#define MAXWORD 30
#define _TRUE 1
#define _FALSE 0

void pintar(const char c, int *state, int opcion_M, int opcion_m);
int main (int argc, char *argv[]) {

    int opcion_M = 0;
    int opcion_m = 0;
    int c,i;
    int state = OUT;
    FILE *fp;

    if (argc<2){
        fprintf(stderr, "[ERROR] La sitaxis es: [-m]/[-M] [<archivo>]*\n");
        return EXIT_FAILURE;
    }

    if ((*++argv)[0] != '-'){
        fprintf(stderr, "[ERROR]2 La sitaxis es: [-m]/[-M] [<archivo>]*\n");
        return EXIT_FAILURE;
    }
    const char character = *++argv[0];
    switch(character){
        case 'M':
            opcion_M = 1;
            --argc;
            printf("Opcion seleccionada Mayuscula [-M]\n");
            break;
        case 'm':
            opcion_m = 1;
            --argc;
            printf("Opcion seleccionada Minuscula [-m]\n");
            break;
    }

    if (opcion_M == 0 && opcion_m == 0){
        fprintf(stderr, "[ERROR] No hay ninguna opcion elegida\n");
        return EXIT_FAILURE;
    }

    if (argc == 1){
        while((c = getchar()) !=EOF){
            pintar(c, &state, opcion_M, opcion_m);
        }
    }else{
        for(i= 1; i<argc; i++){
            if ((fp = fopen(argv[i],"r"))== NULL){
                fprintf(stderr, "[ERROR] No se puede abrir el archivo %s\n", argv[i]);
                return EXIT_FAILURE;
            }

            printf("[INFO] Archivo:%s --------------------------------------------------------------------------\n", argv[i]);
            while ((c = fgetc(fp))!=EOF){
                pintar(c, &state, opcion_M, opcion_m);
            }

            printf("\n");
        }
        
    }

    return EXIT_SUCCESS;
}

void pintar(char c, int *state, int opcion_M, int opcion_m){
    if (c == '\n' || c == ' ' || c == '\t'){
        *state = OUT;
    }else if (*state == OUT){
        *state = IN;
        if (opcion_M == 1){
            c = toupper(c);
        }else if (opcion_m == 1){
            c = tolower(c);
        }
    }
    putchar(c);
}