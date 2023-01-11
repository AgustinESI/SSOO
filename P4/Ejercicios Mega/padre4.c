#define _POSIX_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <wait.h>
#include <unistd.h>
#include <sys/types.h>

#define NOMBREHIJO "hijo4"
#define ESPERA 1

int main(int argc,char *argv[]){

	int numhijos;
	int i;
	int pid;

	if(argc!=2){
		fprintf(stderr, "Error en el numero de argumentos \n");
		return EXIT_FAILURE;
	}
	if((numhijos=atoi(argv[1]))<=0){
		fprintf(stderr, "Error en el argumento numero de hijos \n");
		return EXIT_FAILURE;
	}

	pid_t pids[numhijos];

	for(i=0;i<numhijos;i++){
		switch(pids[i]=fork()){
			case -1:
				fprintf(stderr, "Error al crear el hijo \n");
				return EXIT_FAILURE;
				break;
			case 0:
				if(execl(NOMBREHIJO,NOMBREHIJO,NULL)==-1){
					fprintf(stderr, "Error en la ejecucion del hijo \n");
					return EXIT_FAILURE;
				}
				break;
			default:
				break;
		}
	}

	for(i=0;i<numhijos;i++){
		sleep(ESPERA);
		if(kill(pids[i],SIGINT)==-1){
			fprintf(stderr, "Error al envio de la señal \n");
		}
	}
	sleep(ESPERA);
	for(i=0;i<numhijos;i++){
		if((pid=wait(NULL))==-1){
			fprintf(stderr, "Error en la espera\n");
			continue;
		}
		printf("fin del hijo %d\n",pid);
	}

	fprintf(stderr, "Fin del proceso padre\n");
	return EXIT_SUCCESS;
}