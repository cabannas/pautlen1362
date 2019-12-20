#include "alfa.h"
#include "y.tab.h"

extern FILE * yyin;	/*Fichero lectura de codigo alfa*/
extern FILE * yyout;	/*Fichero de reglas*/
FILE * fpasm;		/*Fichero escritura ensamblador*/
extern int yyparse();	/*Semantico*/

int main(int argc, const char* argv[]){
	
	if(argc != 3){
		return -1;
	}

	yyin = fopen(argv[1], "r");
	if(!yyin){
		printf("Imposible leer fichero de entrada\n");
		return -1;
	}

	/*Debug (fichero de reglas)*/
	yyout = fopen("yyout", "w");

	/*Abrimos el fichero asm para escribir en el (ensamlador)*/
	fpasm = fopen(argv[2], "w");
	if(!fpasm){
		printf("Imposible escribir fichero de salida\n");
		return -1;
	}
	
	yyparse(); /*Analisis sintáctico correcto si devuelve 0*/

	fclose(yyin);
	fclose(yyout);
	fclose(fpasm);

	return 0;
}
