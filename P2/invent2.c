#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define IN 1
#define OUT 0
#define MAXWORD 30
#define _TRUE 1
#define _FALSE 0

void print(const char c, int *state, int *contador, char word[], const int length, const int option_M, const char option_m);

int main (int argc, char *argv[]) {
    int i;
    int length=0;
    int option_m=0;
    int option_M=0;
    int total = 0;
    char word[MAXWORD];
    int state = IN;
    int c;
    int contador = 0;
    FILE *fp;
    
    for (i=0;i<argc;i++){
        if (argv[i][0]=='-'){
            char opcion = *++argv[i];
            if (isdigit(opcion)){
                length=atoi(argv[i]);
                total++;
            }else{
                switch(opcion){
                    case 'M':
                        option_M=1;
                        total++;
                        break; 
                    case 'm':
                        option_m=1;
                        total++;
                        break; 
                }
            }
        }
    }

    if (length==0){
        length = 3;
    }

    if (option_M == 0 && option_m == 0){
        option_M = 1;
    }

    printf("[INFO] Lenght:%d \t Opcion M:%d \t Opcion m:%d\n", length, option_M, option_m);

    if ((argc-total)==1){
        while((c = getchar())!=EOF){
            print(c, &state, &contador, word, length, option_M, option_m);
        }
    }else{
        for (i=(total+1);i<argc;i++){
            if ((fp = fopen(argv[i], "r"))==NULL){
                fprintf(stderr, "[ERROR] No se puede abrir el archivo:%s", argv[i]);
                return EXIT_FAILURE;
            }

            while ((c = fgetc(fp))!=EOF){
                print(c, &state, &contador, word, length, option_M, option_m);
            }
        }
    }

   
    printf("\n");
    return EXIT_SUCCESS;
}

void print(const char c,int *state, int *contador, char word[], const int length, const int option_M, const char option_m){
    if (c == '\n'||c == ' '||c == '\t'){
        *state = OUT;
    }else {
        if (*state == IN){
            if (option_M == 1){
                word[*contador] = toupper(c);
            }else if (option_m == 1){
                word[*contador] = tolower(c);
            }
            *contador = *contador +1;
        }

    }

    if (*state == OUT){
        word[*contador]='\0';
        if (strlen(word)==length){
            printf("%s ", word);
        }
        *contador = 0;
        *state = IN;
    }
}