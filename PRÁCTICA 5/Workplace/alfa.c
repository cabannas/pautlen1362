#include "alfa.h"
#include "y.tab.h"



/*Semantico*/
extern int yyparse();
/*Fichero escritura ensamblador*/
FILE * fpasm;
/*Fichero de reglas*/
extern FILE * yyout;
/*Fichero lectura de codigo alfa*/
extern FILE * yyin;

int main(int argc, const char* argv[]){

	if(argc != 3){
		return -1;
	}

	yyin = fopen(argv[1], "r");

	if(yyin == NULL)
	{
		printf("Error al acceder al fichero de entrada\n");

		return -1;
	}

	/* Abrimos el fichero de reglas */
	yyout = fopen("yyout", "w");

	/* Abrimos el fichero de escritura ensamblador */
	fpasm = fopen(argv[2], "w");

	if(fpasm == NULL)
	{
		printf("Error al acceder al fichero de salida\n");
		return -1;
	}

	/* Realizamos el analisis sintactico*/
	/* Devuelve 0 si todo esta correcto*/
	yyparse();

	/* Liberacion de recursos */
	fclose(fpasm);
	fclose(yyout);

	fclose(yyin);
	
	return 0;
}
