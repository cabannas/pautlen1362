%{
//Sección de definiciones
#include <stdio.h>
#include <stdlib.h>

extern int yylex();
extern int yyparse();
extern FILE* yyin;
void yyerror(const char* s);
%}

%union {
	int ival;
}
%token<ival> T_INT
%token T_PLUS T_MINUS T_MULTIPLY T_LEFT T_RIGHT
%token T_NEWLINE T_QUIT
%left T_PLUS T_MINUS
%left T_MULTIPLY
%type<ival> expression
%start calculation

//Sección de reglas
%%
calculation:
	| calculation line
;
line: T_NEWLINE
    | expression T_NEWLINE { printf("Result: %i\n", $1); }
    | T_QUIT T_NEWLINE { printf("Bye!\n"); exit(0); }
;
expression: T_INT				{ $$ = $1; }
	| expression T_PLUS expression	{ $$ = $1 + $3; }
	| expression T_MINUS expression	{ $$ = $1 - $3; }
	| expression T_MULTIPLY expression	{ $$ = $1 * $3; }
	| T_LEFT expression T_RIGHT		{ $$ = $2; }
;
%%

//Sección de funciones de usuario
int main() {
	yyin = stdin;
	do { 
		yyparse();
	} while(!feof(yyin));
	return 0;
}

void yyerror(const char* s) {
	fprintf(stderr, "Parse error: %s\n", s);
	exit(1);
}
