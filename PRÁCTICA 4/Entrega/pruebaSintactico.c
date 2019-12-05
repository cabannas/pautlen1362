#include <stdio.h>
#include <string.h>
#include "y.tab.h"

extern FILE *yyin;
extern FILE *yyout;
extern int yyparse();

int main(int argc, char** argv){

	/* Ficheros de entrada y salida*/
	yyin = fopen(argv[1], "r");
	yyout = fopen(argv[2], "w");

	/* yyparce se inicia cuando ejecutamos el main, devuelve 0 si todo es correcto,
	en caso contraro, error sintactico */
	if(yyparse() == 0)
	{

			printf("\n");
	  	printf("Ejecucion correcta del analisis sintactico\n");
			printf("\n");

	}
	else
	{

		printf("\n");
		printf("Error en la ejecucion del analisis sintactico\n");
		printf("\n");

	}

	/* Cerramos los ficheros de entrada y salida */

	fclose(yyin);
	fclose(yyout);

	return 0;
}
