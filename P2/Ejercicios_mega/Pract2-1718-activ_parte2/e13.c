/*
    Realizar un programa que cuente los dígitos de un fichero introducido y los muestre por pantalla.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define IN 1
#define OUT 0
#define MAX_WORD 30
#define ALPHABET 26

void print(FILE *fp, const char caracteres[]);
int returnPosition(const char characters[], int c);

int main (int argc, char *argv[]) {

    char characters[ALPHABET] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
    FILE *fp;
    int i;

    if (argc == 1){
        print(stdin, characters);
    }else {
        for (i = 1; i<argc;i++){
            if ((fp = fopen(argv[i],"r"))==NULL){
                fprintf(stderr,"[ERROR] No se puede abrir el archivo:%s\n",argv[i]);
                return EXIT_FAILURE;
            }
            print(fp, characters);
            fclose(fp);
        }
    }

    return EXIT_SUCCESS;

}

int returnPosition(const char characters[], int c){
    int i=0;
    for (i=0; i<strlen(characters); i++){
        if (tolower(c)==characters[i]){
            return i;
        }
    }
    return i;
}

void print(FILE *fp, const char caracteres[]){

    int c;
    char words[ALPHABET][MAX_WORD];
    int numbers[ALPHABET];
    int numbers_line[ALPHABET];
    int state = IN;
    int contador = 0;
    int posicion = 0;
    int i;
    int contador_linea = 1;

    for (i =0; i<ALPHABET;i++){
        numbers[i]=0;
        numbers_line[i]=0;
        words[i][0]='\0';
    }

    while ((c = fgetc(fp))!=EOF){
        if (c == '\n' ||c == ' ' ||c == '\t'){
            state = OUT;
            if (c == '\n'){
                contador_linea++;
            }
        }else if (state == IN){
            if (contador == 0){
                posicion = returnPosition(caracteres, c);
                numbers[posicion]=numbers[posicion]+1;
                numbers_line[posicion]=contador_linea;
            }
            words[posicion][contador]=c;
            contador++;
        }

        if (state == OUT){
            words[posicion][contador++]='\0';
            contador = 0;
            posicion = 0;
            state = IN;
        }
    }

    words[posicion][contador++]='\0';

    printf("LETRA \tPALABRA \tNUMER0 \tLINEA\n");
    printf("=====================================\n");
    for(i=0; i<ALPHABET;i++){
        printf("  %c \t%s\t\t%i\t%i\n",caracteres[i],words[i],numbers[i],numbers_line[i]);
    }

}