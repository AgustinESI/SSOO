/*
    Opcion -p y -i para palabras cuyo numero de caracteres es par o impar, 
    son excluyentes las opciones y si no se indica ninguna 
    se contaran todas las palabras. Si no hay ficheros las entrada estandar 
    y si los hay cuenta las palabras segun la opcion de los ficheros.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define IN 1
#define OUT 0
#define MAXWORD 30

int main (int argc, char *argv[]) {
    
    int opcion_p = 0;
    int opcion_i = 0;
    int c;
    int state=IN;
    int contador = 0;

    int num_p=0;
    int num_i=0;


    if (argc >= 2){
        if ((*++argv)[0]!='-'){
            fprintf(stderr, "[ERROR] Linea de comandos no valida\n");
            return EXIT_FAILURE;
        }else{
            char opcion = *++argv[0];
            printf("OPCION:%c\n",opcion);
            switch (opcion){
                case 'p':
                    opcion_p = 1;
                    break;
                case 'i':
                    opcion_i = 1;
                    break;
            }
        }
    }

    if (opcion_i == 0 && opcion_p == 0){
            opcion_i=1;
            opcion_p=1;
        }

    printf("[INFO] Par:%d\tImpar:%d\tPar&Impar:%d\n",opcion_p,opcion_i,(opcion_i+opcion_p));

    if (argc ==1 || (argc ==2 && (opcion_i ==1 && opcion_p == 1))){
        while ((c=getchar())!=EOF){
            if(c=='\t'||c==' '||c=='\n'){
                state = OUT;
            }else if (state == IN){
                contador++;
            }

            if (state == OUT){
                if (opcion_i == 1 && opcion_p == 1){
                    if (opcion_i == 1 && (contador % 2)!=0){
                        num_i++;
                    }else if(opcion_p == 1 && (contador % 2)==0){
                        num_p++;
                    }
                }else if (opcion_i == 1 && (contador % 2)!=0){
                    num_i++;
                }else if(opcion_p == 1 && (contador % 2)==0){
                    num_p++;
                }

                state = IN;
                contador=0;
            }
        }
    }else{
        int cont=0;
        while (contador-->0){
            
        }
    }

    printf("[INFO] Par:%d\tImpar:%d\tPar&Impar:%d\n",num_p,num_i,(num_i+num_p));

    return EXIT_SUCCESS;
}