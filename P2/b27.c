/*
    Imprimir las palabras de longitud determinada y dos para parametros, al menos uno obligatorio:
        -m primera letra de inicio de palabras minusculas
        -M primera letra de inicio de palabras mayusculas
        -n valor númerico que indica la longitud de las palabras
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define IN 1
#define OUT 0
#define MAXWORD 30

int main (int argc, char *argv[]) {
    
    int i,c;
    int opcion_d=0;
    int opcion_m=0;
    int opcion_M=0;
    int state = IN;
    char word[MAXWORD]="";
    int contador =0;
    FILE *fp;

    if (argc <3){
        fprintf(stderr,"[ERROR] Linea de comandos no valida\n");
        return EXIT_FAILURE;
    }

    for (i=1;i<argc;i++){
        char opcion = (*argv[i]);
        if (opcion=='-'){
            opcion = *++argv[i];
            if (isdigit(opcion)){
                opcion_d=atoi(argv[i]);
            }else{
                switch (opcion){
                case 'M':
                    opcion_M = 1;
                    break;
                case 'm':
                    opcion_m = 1;
                    break;
                }
            }
        }
    }
    
    printf("Opcion_m:%d \tOpcion_M:%d \tOpcion_d:%d \t\n", opcion_m,opcion_M,opcion_d);

    if(argc == 3){
        while((c=getchar())!=EOF){
            if(c=='\t'||c==' '||c=='\n'){
                state = OUT;
            }else if (state == IN){
                if (contador==0){
                    if (opcion_m==1){
                        word[contador]=tolower(c);
                    }else if (opcion_M==1){
                        word[contador]=toupper(c);
                    }
                }else{
                    word[contador]=c;
                }
                contador++;
            }

            if (state== OUT){
                word[contador]='\0';
                if (contador==opcion_d){
                    printf("%s ",word);
                }
                state = IN;
                contador=0;
            }
        }
    }else{
        for(i=3;i<argc;i++){
            if ((fp = fopen(argv[i],"r"))==NULL){
                fprintf(stderr,"[ERROR] Linea de comandos no valida\n");
                return EXIT_FAILURE;
            }
            
            while ((c=fgetc(fp))!=EOF){
                if(c=='\t'||c==' '||c=='\n'){
                    state = OUT;
                }else{
                    if (state == IN){
                        if (contador==0){
                            if (opcion_m==1){
                                word[contador]=tolower(c);
                            }else if (opcion_M==1){
                                word[contador]=toupper(c);
                            }
                        }else{
                            word[contador]=c;
                        }
                        contador++;
                    }
                }

                if (state== OUT){
                    word[contador]='\0';
                    if (contador==opcion_d){
                        printf("%s ",word);
                    }
                    state = IN;
                    contador=0;
                } 
            }
        }
    }

    printf("\n");
    return EXIT_SUCCESS;
}