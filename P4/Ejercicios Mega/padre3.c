#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include <wait.h>

int main(int argc,char *argv[]){
	int i;
	int pid;
	int status;

	if(argc<2){
		fprintf(stderr, "Error en el numero de argumentos \n");
		return EXIT_FAILURE;
	}

	for(i=1;i<argc;i++){
		switch(fork()){
			case -1:
				fprintf(stderr, "Error en la entrada de argumentos \n");
				return EXIT_FAILURE;
				break;
			case 0:
				printf("se va a crear el proceos hijo con el pid: %d\n",getpid());
				if((execlp("wc","wc","-l",argv[i],NULL))!=0){
					fprintf(stderr, "Error al crear el hijo \n");
					continue;
				}
				break;
		}
	}
	for(i=1;i<argc;i++){
		pid=wait(&status);
		if(pid==-1){
			fprintf(stderr, "Error en la espera del hijo \n");
			continue;
		}
		printf("Finaliza el proceso %d \n",pid);
	}
return EXIT_SUCCESS;
}