#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>

int main(int argc, char *argv[]){
	int c;
	if (argc<3){
		fprintf(stderr, "Error en el numero de argumentos \n");
		return EXIT_FAILURE;
	}

	c=argv[2][0];
	printf("Fin hijo <%c> \n",c);
	printf("El proceso hijo ha acabado %d \n",getpid());
return EXIT_SUCCESS;
}