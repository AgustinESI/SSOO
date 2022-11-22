/*

    Crear un programa llamado cuentadigitos que imprima en la salida
    estándar el número de dígitos que contiene el fichero cuyo nombre
    se pasa como argumento en la línea de órdenes. El programa
    admitirá las siguientes opciones:
    -v el programa imprimirá el resultado de la manera 0 :X / 1: X /2: X..
    -V el programa imprimirá el resultado de la manera 0->X\n 1->X\n
    -o el programa imprimirá la cuenta de otros caracteres Otros: X\n
    Donde X es el numero en que se repite dicho valor. La función –v y –V son incompatibles.
    La sintaxis en la línea de ordenes será:
    Cuentadigitos [-o] [-v] [-V] [<archivo>]+

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define IN 1
#define OUT 0
#define MAX_NUMBERS 10

int main (int argc, char *argv[]) {

    int c, i;
    int opcion_v=0;
    int opcion_V=0;
    int opcion_o=0;
    int total=0;
    int count=0;
    FILE *fp;
    int numbers[MAX_NUMBERS];

    if (argc<2){
        fprintf(stderr, "[ERROR] Linea de ordenes no valida\n");
        return EXIT_FAILURE;
    }

    for (i =0; i<MAX_NUMBERS;i++){
        numbers[i] = 0;
    }
    
    for (i = 0; i<argc;i++){
        if (argv[i][0]=='-'){
            char opcion = *++argv[i];
            switch(opcion){
                case 'v':
                    opcion_v=1;
                    total++;
                    break;
                case 'V':
                    opcion_V=1;
                    total++;
                    break;
                case 'o':
                    opcion_o=1;
                    total++;
                    break;
                default:
                    fprintf(stderr, "[ERROR] Opcion, [-%c] no valida\n", opcion);
                    return EXIT_FAILURE;
            }
        }
    }

    if (opcion_v == 1 && opcion_V == 1){
        fprintf(stderr, "[ERROR] Opciones incompatibles\n");
        return EXIT_FAILURE;
    }else if (opcion_v == 0 && opcion_V == 0 && opcion_o == 0){
        fprintf(stderr, "[ERROR] Se debe introducir alguna opcion\n");
        return EXIT_FAILURE;
    }

    printf("[INFO] Opcion V:%d \t Opcion v:%d \t Opcion o:%d\n", opcion_V, opcion_v, opcion_o);

    for (i = (total+1); i<argc; i++){
        if ((fp = fopen(argv[i], "r"))==NULL){
            fprintf(stderr, "[ERROR] No se puede abrir el archivo:%s\n", argv[i]);
            return EXIT_FAILURE;
        }

        while ((c = fgetc(fp))!=EOF){
            if (isdigit(c)){
                numbers[c-'0'] = numbers[c-'0'] + 1;
            }else{
                count++;
            }
        }

        fclose(fp);
    }

    for (i=0; i<MAX_NUMBERS;i++){
        if (opcion_v == 1){
            printf("%d:%d/ ",i,numbers[i]);
        }else if (opcion_V == 1){
            printf("%d->%d\n",i,numbers[i]);
        }
    }

    if (opcion_o == 1){
        printf("Otros:%d\n",count);
    }
    printf("\n");
   

    return EXIT_SUCCESS;
}