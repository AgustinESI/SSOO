#define _POSIX_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>

int main(int argc,char *argv[]){
	int n;
	n=getppid();
	if(kill(n,SIGINT)==-1){
		fprintf(stderr, "Error al enviar la señal \n");
		return EXIT_FAILURE;
	}
	printf("Señal enviada al proceso padre %d desde %d \n",n,getpid());
return EXIT_SUCCESS;
}