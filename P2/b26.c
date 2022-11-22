#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define IN 1
#define OUT 0
#define MAXWORD 30
#define _TRUE 1
#define _FALSE 0

void print(const int option_m, const int option_M, const int option_d, const char c);

int main (int argc, char *argv[]) {
    int option_m=0;
    int option_M=0;
    int option_d=0;
    int i,c;
    FILE *fp;

    if (argc<2){
        fprintf(stderr, "[ERROR]1 Linea de comandos no valida\n");
        return EXIT_FAILURE;
    }else{
        int count=0;
        for (i = 0; i<argc;i++){
            if (argv[i][0] =='-'){
                count++;
            }
        }

        if (count != 1){
            fprintf(stderr, "[ERROR] Se debe seleccionar un unico modo\n");
            return EXIT_FAILURE;
        }

        if ((*++argv)[0]!='-'){
            fprintf(stderr, "[ERROR]2 Linea de comandos no valida\n");
            return EXIT_FAILURE;
        }else{
            char *option =++argv[0]; 
            switch (*option){
                case 'd':
                    option_d=1;
                    argc--;
                    break;
                case 'm':
                    option_m=1;
                    argc--;
                    break;
                case 'M':
                    option_M=1;
                    argc--;
                    break;
                default:
                    fprintf(stderr, "[ERROR]3 Linea de comandos no valida\n");
                    return EXIT_FAILURE;
            }
        }
        
    }



    printf("[INFO] Opcion seleccionada %s\n",argv[0]);
    printf("Opcion_m:%d \tOpcion_M:%d \tOpcion_d:%d \t\n", option_m,option_M,option_d);

    if(argc==1){
        while ((c = getchar())!=EOF){
           print(option_m, option_M, option_d,c);
        }
    }else{
        for(i = 1; i<argc; i++){
            if((fp = fopen(argv[i],"r"))==NULL){
                fprintf(stderr, "[ERROR] No se puede abrir el archivo %s\n", argv[i]);
                return EXIT_FAILURE;
            }

            while ((c = fgetc(fp))!=EOF){
                print(option_m, option_M, option_d,c);
            }
        }
    }


    printf("\n");
    return EXIT_SUCCESS;

}

void print(const int option_m, const int option_M, const int option_d, const char c){
    if ((option_d == 1 && isdigit(c)) || (option_M==1 && isupper(c)) || (option_m ==1 && islower(c))){
        /* Do nothing */
    }else{
        putchar(c);
    }
}