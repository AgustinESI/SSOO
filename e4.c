#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>

#define MAX_LENGTH 4096
#define true 1
#define false 0

/*

    Construir un programa llamado miln que cree enlaces de no dos en el sistema de archivos. La sintaxis
    de la línea de órdenes será:

    a ) miln [<opciones> ] <objetivo> <nodo>
    b ) miln [<opciones> ] <objetivo>
    c ) miln [<opciones> ] [<objetivo> ]+<directorio>

    En la primera forma se crea un enlace a objetivo con el nombre nodo. 
    En la segunda forma se crea una enlace a objetivo en el directorio actual.
    En la tercera forma se crea un enlace a cada uno de los objetivos en el directorio indicado. 
    
    Por defecto, se crean enlaces físicos o duros salvo que se utilice la
    opción -s que se crearan enlaces simbólicos o blandos. Si es utiliza la opción -f y el nombre del enlace
    que debe crearse ya existe, se deberá borrar el nodo previamente existente y crear luego el enlace. Las
    opciones se escribirán en el formato habitual de UNIX. Se aconseja consultar las páginas del manual
    correspondientes a las llamadas al sistema link, symlink, unlink y stat

*/

void LimpiarNombre(char *nombre);

int main(int argc, char *argv[]){
   
   int c;
   int opcion_s = 0;
   int opcion_f = 0;
   char *objetivo;
   char *ptr;
   char nodo[MAX_LENGTH+1];

    while (--argc>0 && (*++argv)[0]=='-'){
        while ((c = *++argv[0])!='\0'){
            switch (c){
                case 's':
                    if (opcion_f==0){
                        opcion_s = 1;
                    }
                    break;
                case 'f':
                    if (opcion_s==0){
                        opcion_f = 1;
                    }
                    break;
                default: 
                    fprintf(stderr, "[ERROR] Opcion no valida\n");
                    return EXIT_FAILURE;
            }
        }
    }

    if(opcion_s == 0 && opcion_f == 0){
        opcion_f = 1;
    }

    printf("[INFO] Simbolico:%d \tFisico:%d\n", opcion_s, opcion_f);
    printf("[INFO] ARGC:%d\n",argc);

    switch (argc){
        case 0:
            fprintf(stderr, "[ERROR] Linea de ordenes no valida\n");
            return EXIT_FAILURE;
        case 1:
            objetivo = *argv;
            printf("[INFO] Objetivo:%s\n", objetivo);
            LimpiarNombre(objetivo);


            if ((ptr=strrchr(objetivo, '/'))==NULL){
                strcpy(nodo, objetivo);
            }else{
                strcpy(nodo, ptr+1);
            }

            printf("[INFO] NODO:%s\n",nodo);

            break;
        case 2:
            objetivo = *argv;
            argv++;

            LimpiarNombre(objetivo);
            LimpiarNombre(*argv);
            printf("[INFO] Objetivo:%s\tArgv:%s\n",objetivo, *argv);

            break;
        default:
            printf("CIPOTE\n");
            break;
    }



    
    return EXIT_SUCCESS;
}


void LimpiarNombre(char *nombre){
    int pos; 
    pos = strlen(nombre)-1;
    if (nombre[pos]=='/'){
        nombre[pos]= '\0';
    }
}