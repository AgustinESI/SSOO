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

void print(FILE *fp, int *count_p, int *count_i);

int main (int argc, char *argv[]) {
    
    int i;
    int opcion_p = 0;
    int opcion_i = 0;
    int opcion_words=0;
    int count_p=0;
    int count_i=0;
    int total=0;
    FILE *fp;

    for(i =0; i<argc;i++){
        if (argv[i][0]=='-'){
            char opcion = *++argv[i];
            switch(opcion){
                case 'p':
                    opcion_p++;
                    total++;
                    break;
                case 'i':
                    opcion_i++;
                    total++;
                    break;
                default:
                    fprintf(stderr, "[ERROR] Opcion no valida:%c\n",opcion);
                    return EXIT_FAILURE;
            }
        }
    }

    if (opcion_i == 1 && opcion_p == 1){
        fprintf(stderr, "[ERROR] No se pueden seleccionar ambos modos de ejecucion\n");
        return EXIT_FAILURE;
    }else if (opcion_i == 0 && opcion_p == 0){
        printf("[INFO] No se ha seleccionado ningun modo, se contaran las palabras\n");
        opcion_words=1;
    }

    printf("[INFO] Opcion P:%d \tOpcion I:%d\n",opcion_p, opcion_i);

    if ((argc-total)==1){
        print(stdin, &count_p, &count_i);
    }else{
        for (i = (total+1); i<argc;i++ ){
            if ((fp = fopen(argv[i],"r"))==NULL){
                fprintf(stderr, "[ERROR] No se puede abrir el archivo:%s",argv[i]);
                return EXIT_FAILURE;
            }
            print(fp, &count_p, &count_i);
            fclose(fp);
        }
    }

    if (opcion_i == 1){
       printf("[RESULT] Opcion I:%d palabras impares\n",count_i); 
    }else if (opcion_p == 1){
        printf("[RESULT] Opcion P:%d palabras palabras\n",count_p); 
    }else if (opcion_words == 1){
         printf("[RESULT] Total de palrabras:%d\n",(count_i + count_p)); 
    }

    return EXIT_SUCCESS;
}

void print(FILE *fp, int *count_p, int *count_i){
    int contador = 0;
    int state = IN;
    int c;

    while ((c = fgetc(fp))!=EOF){

        if (c == '\t' || c == ' ' || c == '\n'){
            state = OUT;
        }else if (state == IN){
            contador++;
        }

        if (state == OUT){
            if ((contador%2)==0){
                *count_p=*count_p+1;
            }else{
                *count_i=*count_i+1;
            }
            state = IN;
            contador=0;
        }
    }
}