%{

#include <stdio.h>
#include <stdlib.h>

extern int yylex();
extern int yyparse();
extern FILE* yyin;
extern FILE* out;

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

%%

calculation:
	| calculation line
;

line: T_NEWLINE { fprintf(out, "R: line: T_NEWLINE\n"); }
    | expression T_NEWLINE { fprintf(out, "R: expression T_NEWLINE\n"); printf("Result: %i\n", $1); }
    | T_QUIT T_NEWLINE { fprintf(out, "R: T_QUIT T_NEWLINE\n"); printf("Bye!\n"); fclose(out); exit(0); }
;

expression: T_INT				{ fprintf(out, "R: T_INT\n"); $$ = $1; }
	| expression T_PLUS expression	{ fprintf(out, "R: expression T_PLUS expression\n"); $$ = $1 + $3; }
	| expression T_MINUS expression	{ fprintf(out, "R: expression T_MINUS expression\n"); $$ = $1 - $3; }
	| expression T_MULTIPLY expression	{ fprintf(out, "R: expression T_MULTIPLY expression\n"); $$ = $1 * $3; }
	| T_LEFT expression T_RIGHT		{ fprintf(out, "R: T_LEFT expression T_RIGHT\n"); $$ = $2; }
;

%%

int main() {
	yyin = stdin;
    out = fopen("log.txt", "w");
	do {
		yyparse();
	} while(!feof(yyin));
    fclose(out);
	return 0;
}

void yyerror(const char* s) {
	fprintf(stderr, "Parse error: %s\n", s);
	exit(1);
}
