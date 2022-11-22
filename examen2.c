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


/*

    ESPECIFICACIÓN: Utilizando las llamadas al sistema UNIX, construya un programa C estándar
    que cambie el nombre de cada archivo de la línea de órdenes por otro nombre que se la
    concatenación del nombre del archivo original, el carácter . y el sufijo indicado en la línea de
    comandos. Si no se indica un sufijo en la línea de órdenes se utilizará el sufijo old. La sintaxis del
    programa será:

    cambiar [-<sufijo>] <nombre>x
    
    EJECUCIÓN: Desde el directorio home del usuario alumno copie el contenido del directorio
    /var/test el subdirectorio test y ejecute el programa con los siguientes argumentos cambiar –
    dos test/rfc* comprobando que realiza la funcionalidad requerida y escriba luego el listado del
    programa en la sección denominada LISTADO:(Si es necesario continúe al dorso).

*/

void renameFile(const char *name, const char *sufix);
int main(int argc, char *argv[]){

    char *sufix;
    int i;
    while (--argc>0 && (*++argv)[0]=='-'){
        sufix = ++argv[0];
    }

    printf("[INFO] Sufijo:%s\n", sufix);

    for (i =0; i<argc;i++){
        renameFile(argv[i], sufix);
    }

    return EXIT_SUCCESS;
}


void renameFile (const char *name, const char *sufix){
    char buffer[MAXBUFFER+1];

    if (strlen(name)+1+strlen(sufix)>MAXBUFFER){
        fprintf(stderr, "[ERROR] Nombre demasiado largo:%s.%s\n", name, sufix);
        exit(EXIT_FAILURE);
    }
    sprintf(buffer, "%s.%s", name, sufix);

    if (rename(name, buffer)==-1){
        fprintf(stderr, "[ERROR] No se puede renombrar el archivo %s → %s\n", name, buffer);
        exit(EXIT_FAILURE);
    }

    printf("[INFO] Name:%s\n", buffer);
}