#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define IN 1
#define OUT 0
#define MAXWORD 30
#define _TRUE 1
#define _FALSE 0

int main (int argc, char *argv[]) {

	int c,i;
	int state = IN;
	int num = 0;
	FILE *fp;
	int length;
	
	if (argc>1){
		if ((*++argv)[0] != '-'){
			fprintf(stderr, "[WARNING] No se he definido un argmento como valor,  por defecto sera 30\n");
			length = 30;
		}else{
			length = atoi(++argv[0]);
			--argc;
		}
	}else{
		length = 30;
	}

	printf("Argumentos:%d\n",argc);
	printf("Tamaño:%d\n",length);

	if (argc == 1){
		while ((c = getchar())!=EOF){
			if (c == '\n'){
				state = IN;
				num = 0;
			}else{
				if (state == IN){
					num++;
				}
				if (num<=length){
					putchar(c);
				}else{
					state = OUT;
				}
			}
		}
	}else{
		for (i = 1; i < argc; i++){

			if ((fp = fopen(argv[i],"r"))==NULL){
				fprintf(stderr, "[ERROR] En la lectura del archivo %s\n", argv[i]);
				return EXIT_FAILURE;
			}

			printf("[INFO] Archivo:%s\n",argv[i]);

			while ((c = fgetc(fp))!=EOF){
				if (c == '\n'){
					state = IN;
					num = 0;
				}else{
					if (state == IN){
						num++;
						if (num<=length){
							putchar(c);
						}else{
							state = OUT;
							printf("\n");
						}
					}
				}
			}
			
			fclose(fp);
		}
	}

	printf("\n");
	
	return EXIT_SUCCESS;

}