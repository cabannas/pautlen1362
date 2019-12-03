%{
//Sección de definiciones
#include <stdio.h>
#include <stdlib.h>

extern int yylex();
extern int yyparse();
extern FILE* yyin;
void yyerror(const char* s);

int x=0, y=0, z=0;

%}

%union {
	int ival;
}
%token<ival> T_INT T_X T_Y T_Z
%token T_PLUS T_MINUS T_MULTIPLY T_LEFT T_RIGHT T_EQUAL
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
		| T_X T_EQUAL T_INT T_NEWLINE { x = $3;}
		| T_Y T_EQUAL T_INT T_NEWLINE { y = $3;}
		| T_Z T_EQUAL T_INT T_NEWLINE { z = $3;}
;


expression: T_INT	{ $$ = $1;}
	| T_X	{ $$ = x;}
	| T_Y	{ $$ = y;}
	| T_Z	{ $$ = z;}
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
