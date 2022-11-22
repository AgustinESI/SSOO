#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define IN 1
#define OUT 0
#define MAXWORD 30
#define _TRUE 1
#define _FALSE 0

int main (int argc, char *argv[]) {
    int c,i;
    int contador=0;
    int length;
    int state = IN;
    char word[MAXWORD]="";
    FILE *fp;

    if (argc>1){
        if ((*++argv)[0]!='-'){
            fprintf(stderr, "[WARNING] Se tomara por defecto el valor 1\n");
            length=1;
        }else{
            length = atoi(++argv[0]);
            argc--;
        }
    }else{
        length=1;
    }

    printf("[INFO] Length:%d\n",length);

    if (argc==1){
        while((c=getchar())!=EOF){
            if (c == '\n'||c == '\t'||c == ' '){
                state = OUT;
            }else if (state == IN){
                word[contador]=c;
                contador++;
            }

            if(state == OUT){
                word[contador]='\0';
                if (contador<=length){
                    printf("%s ",word);    
                }
                state = IN;
                contador = 0;
            }
        }
    }else{
        for (i = 1; i<argc; i++){
            printf("Argc:%d \t Str:%s \t  i:%d\n",argc,argv[i],i);
            if ((fp = fopen(argv[i], "r")) == NULL){
                fprintf(stderr, "[ERROR] No se ha podido abrir el archivo %s\n",argv[i]);
                return EXIT_FAILURE;
            }

            while ((c=fgetc(fp))!=EOF){
                if (c == '\n'||c == '\t'||c == ' '){
                    state = OUT;
                }else if (state == IN){
                    word[contador]=c;
                    contador++;
                }

                if(state == OUT){
                    word[contador]='\0';
                    if (contador<=length){
                        printf("%s ",word);    
                    }
                    state = IN;
                    contador = 0;
                }
            }
        }
    }


    return EXIT_SUCCESS;

}