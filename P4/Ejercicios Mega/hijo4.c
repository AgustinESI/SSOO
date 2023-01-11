#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <fcntl.h>
#include <wait.h>
#include <unistd.h>

void Manejador(int num){
	char c;
	srand((int)getpid());
	c=(rand()%25 + 65);
	printf("Recibida la señal %d , finalizando proceso %d Caracter aleatorio %c\n",num,getpid(),c);
	
	_exit(EXIT_SUCCESS);
}

int main(int argc,char *argv[]){

	if(argc!=1){
		fprintf(stderr, "Error en el numero de argumentos \n");
		return EXIT_FAILURE;
	}

	if(signal(SIGINT,Manejador)==SIG_ERR){
		fprintf(stderr, "Error en la manipulacion de la señal \n");
		return EXIT_FAILURE;
	}
	

	while(1);


}