/*
    El programa debe calcular todas las raíces de polinomios de segundo grado. La entrada será una secuencia
    de líneas que contendrá una serie de números reales que, tomados de tres en tres, se interpretarán como
    los coeficientes a, b y c de cada polinomio de la forma ax2 + bx + c. La salida del programa debe consistir
    en una línea por cada polinomio leído con el siguiente formato:

    Raíces de ax^2+bx+c : x1 x2

    Si x1 o x2 son valores reales se escribirán con tres cifras decimales y si son números complejos de la
    forma R+Ii donde R e I se escribirán con tres cifras decimales

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define IN 1
#define OUT 0
#define MAX_NUMBERS 6


void print(FILE *fp);
int main (int argc, char *argv[]) {

    int i;
    FILE *fp;

    for (i = 1; i<argc;i++){
        printf("[INFO] Archivo: %s\n", argv[i]);
        if ((fp = fopen(argv[i],"r"))==NULL){
            fprintf(stderr, "[ERROR] No se puede abrir el archivo:%s\n", argv[i]);
            return EXIT_FAILURE;
        }
        print(fp);
        fclose(fp);
    }
    
    

    return EXIT_SUCCESS;

}

void print(FILE *fp){
    int state = IN;
    int position=0;
    int c,i;
    char number[30];
    signed int numbers[MAX_NUMBERS];
    int contador = 0;
    int negative = 0;

    for (i=0; i<MAX_NUMBERS;i++){
        numbers[i]=0;
    }
    

    while (1){
        c = fgetc(fp);
        if (c == '-'){
            negative=1;
        }
        if (c == ' ' || c == '\n' || c == '\t'){
            state = OUT;
        }else if (state == IN){
            number[position]=c;
            position++;
        }

        if (state == OUT){
            number[position]='\0';
            if (negative == 1){
                numbers[contador]= -atoi(number);
            }else{
                numbers[contador]= atoi(number);
            }
            state = IN;
            contador++;
            position=0;
            negative = 0;
        }

        if (c == EOF){
            number[position]='\0';
            if (negative == 1){
                numbers[contador]= atoi(number)*(-1);
            }else{
                numbers[contador]= atoi(number);
            }
            break;
        }
    }
    
    printf("---------------------------------\n");

    for (i=0; i<MAX_NUMBERS;i+=3){
        if (numbers[i] != 0 && numbers[i+1]!=0 && numbers[i+2]!=0){
            float disc=pow(numbers[i+1], 2.0)-4*numbers[i]*numbers[i+2];
            if(disc>0.0){
                /*RAICES REALES*/
                float x1=((-numbers[i+1]+sqrt(disc))/(2.0*numbers[i]));
                float x2=((-numbers[i+1]-sqrt(disc))/(2.0*numbers[i]));
                printf("[INFO] Raíces de %dx^2 + %dx + %d : %.3f & %.3f\n", numbers[i],numbers[i+1],numbers[i+2],x1,x2);
            }else{
                if(disc==0.0){
                    /*UNA SOLA RAIZ*/
                    float x1=(-numbers[i+1])/(2.0*numbers[i]);
                    printf("[INFO] Raíces de %dx^2 + %dx + %d : %.3f\n", numbers[i],numbers[i+1],numbers[i+2],x1);
                }else{
                    /*RAIZ REAL E IMAGINARIA*/
                    float xr=(-numbers[i+1]/(2.0*numbers[i]));
                    float xi=(sqrt(-disc)/(2.0*numbers[i]));
                    printf("[INFO] Raíces de %dx^2 + %dx + %d : %.3f & %.3f\n", numbers[i],numbers[i+1],numbers[i+2],xr,xi);
                }
            }
        }
    }
}