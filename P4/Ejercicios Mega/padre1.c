#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

int cont=0;
int n;

void Manejador(int num){
	++cont;
	printf("Se ha recibido la señal: %d \n numero de señales recibidas: %d \n",num,cont);
	if(cont==n){
		printf("Fin del proceso padre \n");
		exit(EXIT_SUCCESS);
	}
	if(signal(SIGINT,Manejador)==SIG_ERR){
		fprintf(stderr,"Error al manipular la señal \n");
		exit(EXIT_FAILURE);
	}
}

int main(int argc,char *argv[]){
	int i;

	if(argc!=2){
		fprintf(stderr, "Erro en el numero de argumentos \n");
		return EXIT_FAILURE;
	}
	if(signal(SIGINT,Manejador)==SIG_ERR){
		fprintf(stderr, "Error al manipular la señal \n");
		return EXIT_FAILURE;
	}
	if((n=atoi(argv[1]))<=0){
		fprintf(stderr, "Error en el numero de hijos \n");
		return EXIT_FAILURE;
	}

	for(i=0;i<n;i++){
		switch(fork()){
			case -1:
				fprintf(stderr, "Error en la crecion de procesos hijos \n");
				return EXIT_FAILURE;
				break;
			case 0:
				execl("hijo1","hijo1",NULL);
				break;
		}
	}
	while(1);
	return EXIT_SUCCESS;
}