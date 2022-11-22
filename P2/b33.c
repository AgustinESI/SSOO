#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define IN 1
#define OUT 0
#define MAXWORD 30

/*
c caracteres
w palabras
l lineas
*/

void print(FILE *fp, int *num_c, int *num_w, int *num_l);
int main (int argc, char *argv[]) {

    int opcion_w=0;
    int opcion_c=0;
    int opcion_l=0;
    int num_w=1;
    int num_c=0;
    int num_l=0;
    int i;
    
    int total = 0;
    FILE *fp;

    if(argc >1){
        for(i=1; i < argc;i++){
            if (argv[i][0]=='-'){
                char opcion = *++argv[i];
                switch (opcion){
                    case 'w':
                        opcion_w=1;
                        total++;
                        break;
                    case 'l':
                        opcion_l=1;
                        total++;
                        break;
                    case 'c':
                        opcion_c=1;
                        total++;
                        break;
                    default:
                        fprintf(stderr,"[ERROR] Opcion [%c] no valida \n",opcion);
                        return EXIT_FAILURE;
                }
            }
        }
    }

    if (opcion_c==0 && opcion_l==0 && opcion_w==0){
        opcion_c=1; 
        opcion_l=1; 
        opcion_w=1;
    }


    printf("[INFO] Opcion C:%d\tOpcion L:%d\tOpcion W:%d\t\n",opcion_c,opcion_l,opcion_w);

    if ((argc-total)==1){
       print(stdin, &num_c, &num_w, &num_l);
    }else{
        
        for(i=total+1;i<argc;i++){
            if ((fp = fopen(argv[i],"r"))==NULL){
                fprintf(stderr,"[ERROR] Error en la apertura del archivo %s\n",argv[i]);
                return EXIT_FAILURE;
            }

           print(fp, &num_c, &num_w, &num_l);
        }
    }

    if (opcion_l==1 && opcion_w==1 && opcion_c==1){
        printf("[INFO] Caracteres:%d\t Lineas:%d\t Palabras:%d\t\n",num_c,num_l,num_w);
    }else if (opcion_c == 1){
        printf("[INFO] Caracteres:%d\t\n",num_c);
    }else if (opcion_l == 1){
        printf("[INFO] Lineas:%d\t\n",num_l);
    }else if (opcion_w == 1){
        printf("[INFO] Palabras:%d\t\n",num_w);
    }

    return EXIT_SUCCESS;

}

void print(FILE *fp, int *num_c, int *num_w, int *num_l){

    int c;
    int state=IN;

    while ((c= fgetc(fp))!=EOF){
        *num_c=*num_c+1;
        if (c == ' '||c == '\n'||c == '\t'){
            state = OUT;
        }else if (state == OUT){
            state = IN;
            *num_w=*num_w+1;
        }
        if (c=='\n'){
            *num_l=*num_l+1;
        }  
    }
}