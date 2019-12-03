%option noyywrap
%{
#include <stdio.h>
#define YY_DECL int yylex()
#include "calc.tab.h"

FILE * yyout;
int linea = 1, columna = 1;

%}

%%

[ \t]	; // ignore all whitespace
[0-9]+		{
    yylval.ival = atoi(yytext);
    return T_INT;
}
\n		{columna = 1; linea++;
    return T_NEWLINE;}
"x"		{columna += yyleng;
    return T_X;}
"y"		{columna += yyleng;
    return T_Y;}
"z"		{columna += yyleng;
    return T_Z;}
"="		{columna += yyleng;
    return T_EQUAL;}
"+"		{columna += yyleng;
    return T_PLUS;}
"-"		{columna += yyleng;
    return T_MINUS;}
"*"		{columna += yyleng;
    return T_MULTIPLY;}
"("		{columna += yyleng;
    return T_LEFT;}
")"		{columna += yyleng;
    return T_RIGHT;}
"quit"	{return T_QUIT;}

. { columna += yyleng;
    fprintf(stdout,"****Error en [lin %d, col %d]: simbolo no permitido (""%s"")\n",linea,(columna-yyleng),yytext);}

%%
