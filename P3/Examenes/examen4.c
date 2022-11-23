#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>

#define MAXBUFFER 4096
#define true 1
#define false 0

/*
    Programa que permite listar todos los ficheros regulares menores que un tamaño dado.

*/



void ListarDirectorio(const char *name, const int length);

int main(int argc, char *argv[]){

    int length=0;
    int i;

    while (--argc >0 && (*++argv)[0]=='-' && isdigit(*++argv[0])){
        length= atoi(argv[0]);
    }

    for (i = 0; i<argc; i++){
        ListarDirectorio(argv[i], length);
    }
 

    return EXIT_SUCCESS;
}


void ListarDirectorio(const char *name, const int length){
    DIR *d;
    struct dirent *dr;
    struct stat st;
    char buffer[MAXBUFFER+1];

    if ((d = opendir(name))== NULL){
        fprintf(stderr, "[ERROR] No se puede abrir el directorio:%s\n", name);
        exit(EXIT_FAILURE);
    }

    while ((dr = readdir(d))!=NULL){

        if (strcmp(dr->d_name, ".") == 0 || strcmp(dr->d_name, "..") ==0){
            continue;
        }

        if (strlen(dr->d_name)+1+strlen(name)>MAXBUFFER){
            continue;
        }   

        sprintf(buffer, "%s/%s", name, dr->d_name);

        if ((stat(buffer, &st))==-1){
            continue;
        }

        if ((S_ISREG(st.st_mode)) && (((int) st.st_size)<=length)){
            printf("Bytes:%d\t\t Dir:%s\n", ((int) st.st_size), buffer);
        }
        if (S_ISDIR(st.st_mode)){
            ListarDirectorio(buffer, length);
        }
    }

   

}
