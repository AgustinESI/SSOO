#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define IN 1
#define OUT 0
#define MAXWORD 30


/*
    Construir en lenguaje C estándar un programa que tome sus datos de entrada del contenido de la 
    lista de ficheros Micados en la línea de ordenes y envite sus resultados a la salida estándar. 
    El programa debe copiar la entrada en la salida estándar reempbrando cada cadena de uno o más 
    espacios en blanco (carácter blanco) por un solo espacio en blanco (opción -b) o por un guión (opción -g). e
    n función de las opciones de la finca de ordenes. Ambas opciones son incompatibles. Si no se especifica ninguna 
    opción, las cadenas de espacios en blanco se sustituirán por el carácter = (signo igual). Si no se especifica 
    ningún archivo en la linea de ordenes se debe utilizar la entrada estándar. La sintaxis de la linea de ordenes 
    será:
*/

void print(FILE *fp, const char opcion_b, const char opcion_g, const char opcion_w);
int main (int argc, char *argv[]) {

    
    int opcion_b=0;
    int opcion_g=0;
    int opcion_w=0;
    int i;
    int total = 0;
    FILE *fp;


    for (i = 0; i<argc;i++){
        if (argv[i][0]=='-'){
            switch(*++argv[i]){
                case 'b':
                    opcion_b = 1;
                    total++;
                    break;
                case 'g':
                    opcion_g = 1;
                    total++;
                    break;
                default :
                    fprintf(stderr, "[ERROR] Modo de ejecucion no valido\n");
                    return EXIT_FAILURE;
            }
        }
    }

    if (opcion_b == 0 && opcion_g == 0){
        opcion_w = 1;
    }else if (opcion_b == 1 && opcion_g == 1){
        fprintf(stderr, "[ERROR] No se pueden seleccionar ambos modos a la vez\n");
        return EXIT_FAILURE;
    }

    printf("[INFO] Opcion B:%d \t Opcion G:%d \t Opcion B-G:%d\n",opcion_b, opcion_g, opcion_w);

    if ((argc-total)==1){
        print(stdin, opcion_b, opcion_g, opcion_w);
    }else{
        for (i=(total+1);i<argc;i++){
            if ((fp = fopen(argv[i],"r"))==NULL){
                fprintf(stderr, "[ERROR] No se puede abrir el archivo:%s", argv[i]);
                return EXIT_FAILURE;
            }
            print(fp, opcion_b, opcion_g, opcion_w);
            fclose(fp);
        }
    }

    printf("\n");

    return EXIT_SUCCESS;
}

void print(FILE *fp, const char opcion_b, const char opcion_g, const char opcion_w){
    int c = 0;
    char prev_c;
    while ((c = fgetc(fp))!=EOF){
        if (c==' '){
            if (opcion_b == 1 && prev_c != ' '){
                putchar(' ');
                prev_c = ' ';
            }else if (opcion_g == 1 && prev_c != '-'){
                putchar('-');
                prev_c = '-';
            }else if (opcion_w == 1 && prev_c != '='){
                putchar('=');
                prev_c = '=';
            }
        }else{
            putchar(c);
            prev_c = c;
        }
    }
}