#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define IN 1
#define OUT 0
#define MAXWORD 30

void print(FILE *fp, const int opcion_b, const int opcion_g, const char character);
int main (int argc, char *argv[]) {
    
    int opcion_b=0;
    int opcion_g=0;
    char character;
    int c,i;
    int total =0;
    FILE *fp;

    for(i=0;i<argc;i++){
        if (argv[i][0]=='-'){
            char opcion = *++argv[i];
            switch (opcion){
                case 'b':
                    opcion_b=1;
                    character=' ';
                    total++;
                    break;
                case 'g':
                    opcion_g=1;
                    character='-';
                    total++;
                    break;
            }
        }
    }

    if (opcion_b == 1 && opcion_g == 1){
        fprintf(stderr, "[ERROR] Solo se admite un metodo de ejcucion\n");
        return EXIT_FAILURE;
    }else if (opcion_b == 0 && opcion_g == 0){
        character = '=';
        opcion_b = 1;
        opcion_g = 1;
    }
    printf("Opcion B:%d\t Opcion G:%d\t Character:>%c<\n", opcion_b, opcion_g, character);


    if ((argc-total)==1){
        print(fp, opcion_b, opcion_g, character);
    }else{
        for (i = 1+total; i < argc; i++){
            
            if ((fp = fopen(argv[i],"r"))==NULL){
                fprintf(stderr, "[ERROR] No se puede abrir el archivo:%s\n",argv[i]);
                return EXIT_FAILURE;
            }
            
            print(fp, opcion_b, opcion_g, character);
        }
    }
    printf("\n");


    return EXIT_SUCCESS;
}

void print(FILE *fp, const int opcion_b, const int opcion_g, const char character){
    int c;
    char prev_character;
    while ((c = fgetc(fp))!=EOF){
        if (c == ' '){   
            if (opcion_b == 1 && opcion_g == 1){
                putchar(character);
            }else if (opcion_g == 1){
                putchar(character);
            }else if (opcion_b == 1){
                if (prev_character == ' '){
                /* Do nothing */
                }else{
                    putchar(c);
                }
            }
        }else{
            putchar(c);
        }
        prev_character = c;
    }
}