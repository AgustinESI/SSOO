#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <wait.h>
#include <fcntl.h>
#include <sys/stat.h>

#define NOMBREHIJO "hijo2"
#define PERMISOS 0644

int main(int argc,char *argv[]){
	int i;
	int pid;
	int fd;
	int status;

	if(argc<3){
		fprintf(stderr, "Error en el numero de argumentos \n");
		return EXIT_FAILURE;
	}
	if((fd=mkfifo(argv[1],PERMISOS))!=0){
		fprintf(stderr, "Error al crear la tuberia \n");
		return EXIT_FAILURE;
	}

	for(i=0;i<argc-2;i++){
		switch(fork()){
			case -1:
				fprintf(stderr, "Error al crear los procesos hijos \n");
				return EXIT_FAILURE;
				break;
			case 0:
				printf("Creacion del nuevo hijo \n");
				close(1);
				if(dup(fd)!=1){
					fprintf(stderr, "Error en la duplicacion \n");
					return EXIT_FAILURE;
				} 
				
				if(execl(NOMBREHIJO,NOMBREHIJO,argv[1],argv[i+2],NULL)==-1){
					fprintf(stderr, "Error al ejecutar \n");
					return EXIT_FAILURE;
				}
				break;
			default:
				break;
		}
		
	}

	for(i=0;i<argc-2;i++){
		if((pid=wait(&status))==-1){
			fprintf(stderr, "Error en la espera\n");
			continue;
		}
		printf("Fin del proceso %d \n",pid);
	}
	 unlink(argv[1]); 
return EXIT_SUCCESS;
}