#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define IN 1
#define OUT 0
#define MAXWORD 30
#define _TRUE 1
#define _FALSE 0


/*
    imprimir las -n palabras de -x tamaño
    [-n] [-x] [archivo]*
    si no se introducen ninguna de las opciones se tomaran los valores 10 y 3

*/

void print(const char c, int *state, int *contador, char word[], int *cont_num_words, const int num_words, const int length_word);

int main (int argc, char *argv[]) {

    char word[MAXWORD];
    int length_word=0;
    int num_words=0;
    int i=0;
    int total = 0;
    int c;
    int state = IN;
    int contador =0;
    int cont_num_words = 0;
    FILE *fp;

    for(i=0; i<argc; i++){
        if (argv[i][0]=='-'){
            if (total==0 && length_word == 0){
                length_word = atoi(++argv[i]);
                total++;
            }else if (total == 1 && num_words==0 && length_word!=0){
                num_words = atoi(++argv[i]);
                total++;
            }
        }
    }

    if (num_words==0){
        num_words=10;
    }
    if (length_word==0){
        length_word=3;
    }

    printf("[INFO] Nº Palabras:%d \t Tamaño:%d\t\n", length_word, num_words);


    if ((argc - total)==1){
        while((c=getchar())!=EOF){
            print(c, &state, &contador, word, &cont_num_words, num_words, length_word);
        }
    }else{
        for (i=(total+1); i<argc; i++){
            if ((fp = fopen(argv[i], "r"))==NULL){
                fprintf(stderr,"[ERROR] No se puede abrir el archivo %s\n", argv[i]);
                return EXIT_FAILURE;
            }

            while((c = fgetc(fp))!=EOF){
                print(c, &state, &contador, word, &cont_num_words, num_words, length_word);
            }
        }
    }
    printf("\n");

    return EXIT_SUCCESS;

}

void print(const char c, int *state, int *contador, char word[], int *cont_num_words, const int num_words, const int length_word){

    if (c=='\n'||c==' '||c=='\t'){
        *state = OUT;
    }else if (*state == IN){
        word[*contador] =c;
        *contador=*contador+1;
    }

    if (*state == OUT){
        word[*contador]='\0';
        if (strlen(word)==length_word && *cont_num_words<num_words){
            printf("%s ",word);
            *cont_num_words=*cont_num_words+1;
        }
        *contador=0;
        *state = IN;
    }
}