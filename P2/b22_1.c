#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define IN 1
#define OUT 0
#define MAXWORD 30
#define _TRUE 1
#define _FALSE 0

void print(const char c, int *contador, int *state, const int length);

int main (int argc, char *argv[]) {

	int length=0;
	int c, i;
	int total = 0;
	int contador = 0;
	int state = IN;
	FILE *fp;

	for (i =0; i<argc;i++){
		if (argv[i][0]=='-' && length==0){
			length = atoi(++argv[i]);
			total++;
		}
	}

	if (length==0 || total == 0){
		printf("[INFO] No se ha definido un tamaño, por defecto se establece el 30\n");
		length=30;
	}

	printf("[INFO] Tamaño:%d\n", length);

	if ((argc-total)==1){
		while ((c = getchar())!=EOF){
			print(c, &contador, &state, length);
		}
	}else{
		for (i = (total+1) ; i < argc; i++){
			if ((fp = fopen(argv[i],"r"))==NULL){
				fprintf(stderr, "[ERROR] Error en la apertura del archivo:%s \n", argv[i]);
				return EXIT_FAILURE;
			}

			while ((c = fgetc(fp))!=EOF){
				print(c, &contador, &state, length);
			}
		}
	}

	return EXIT_SUCCESS;

}

void print(const char c, int *contador, int *state, const int length){
	if (c == '\n'){
		*state = OUT;
	}else if (*state == IN && *contador <= length){
		putchar(c);
		*contador = *contador +1;
	}

	if (*state == OUT){
		*contador = 0;
		*state = IN;
	}
}