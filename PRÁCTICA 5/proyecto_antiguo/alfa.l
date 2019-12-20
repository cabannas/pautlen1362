%{
#include <stdio.h>
#include <string.h>
#include "alfa.h"
#include "y.tab.h"

FILE * yyout;
int linea = 1,columna = 1, error = 0;

%}
%option noyywrap
%option nounput
%option noinput

DIGITO [0-9]
LETRA [a-zA-Z]
LETRAODIGITO [a-zA-Z0-9]
LETRAODIGITOESPACIO [a-zA-ZO-9 ]

%%
"//".* { columna += yyleng;}
"array" { columna += yyleng; fprintf(yyout,";D:\t%s\n",yytext); return TOK_ARRAY; }
"boolean" { columna += yyleng; fprintf(yyout,";D:\t%s\n",yytext); return TOK_BOOLEAN; }
"else" { columna += yyleng; fprintf(yyout,";D:\t%s\n",yytext);  return TOK_ELSE; }
"function" { columna += yyleng; fprintf(yyout,";D:\t%s\n",yytext);  return TOK_FUNCTION; }
"if" { columna += yyleng; fprintf(yyout,";D:\t%s\n",yytext); return TOK_IF; }
"int" { columna += yyleng; fprintf(yyout,";D:\t%s\n",yytext); return TOK_INT; }
"main" { columna += yyleng; fprintf(yyout,";D:\t%s\n",yytext); return TOK_MAIN; }
"printf" { columna += yyleng; fprintf(yyout,";D:\t%s\n",yytext); return TOK_PRINTF; }
"return" { columna += yyleng; fprintf(yyout,";D:\t%s\n",yytext); return TOK_RETURN; }
"scanf" { columna += yyleng; fprintf(yyout,";D:\t%s\n",yytext); return TOK_SCANF; }
"while" { columna += yyleng; fprintf(yyout,";D:\t%s\n",yytext); return TOK_WHILE; }
";" { columna += yyleng; fprintf(yyout,";D:\t%s\n",yytext); return TOK_PUNTOYCOMA; }
"," { columna += yyleng; fprintf(yyout,";D:\t%s\n",yytext); return TOK_COMA; }
"(" { columna += yyleng; fprintf(yyout,";D:\t%s\n",yytext); return TOK_PARENTESISIZQUIERDO; }
")" { columna += yyleng; fprintf(yyout,";D:\t%s\n",yytext); return TOK_PARENTESISDERECHO; }
"[" { columna += yyleng; fprintf(yyout,";D:\t%s\n",yytext); return TOK_CORCHETEIZQUIERDO; }
"]" { columna += yyleng; fprintf(yyout,";D:\t%s\n",yytext); return TOK_CORCHETEDERECHO; }
"{" { columna += yyleng; fprintf(yyout,";D:\t%s\n",yytext); return TOK_LLAVEIZQUIERDA; }
"}" { columna += yyleng; fprintf(yyout,";D:\t%s\n",yytext); return TOK_LLAVEDERECHA; }
"+" { columna += yyleng; fprintf(yyout,";D:\t%s\n",yytext); return TOK_MAS; }
"-" { columna += yyleng; fprintf(yyout,";D:\t%s\n",yytext); return TOK_MENOS; }
"/" { columna += yyleng; fprintf(yyout,";D:\t%s\n",yytext); return TOK_DIVISION; }
"*" { columna += yyleng; fprintf(yyout,";D:\t%s\n",yytext); return TOK_ASTERISCO; }
"&&" { columna += yyleng; fprintf(yyout,";D:\t%s\n",yytext); return TOK_AND; }
"||" { columna += yyleng; fprintf(yyout,";D:\t%s\n",yytext); return TOK_OR; }
"==" { columna += yyleng; fprintf(yyout,";D:\t%s\n",yytext); return TOK_IGUAL; }
"=" { columna += yyleng; fprintf(yyout,";D:\t%s\n",yytext); return TOK_ASIGNACION; }
"!=" { columna += yyleng; fprintf(yyout,";D:\t%s\n",yytext); return TOK_DISTINTO; }
"!" { columna += yyleng; fprintf(yyout,";D:\t%s\n",yytext); return TOK_NOT; }
"<=" { columna += yyleng; fprintf(yyout,";D:\t%s\n",yytext); return TOK_MENORIGUAL; }
">=" { columna += yyleng; fprintf(yyout,";D:\t%s\n",yytext); return TOK_MAYORIGUAL; }
"<" { columna += yyleng; fprintf(yyout,";D:\t%s\n",yytext); return TOK_MENOR; }
">" { columna += yyleng; fprintf(yyout,";D:\t%s\n",yytext);return TOK_MAYOR; }
"true" { columna += yyleng; fprintf(yyout,";D:\t%s\n",yytext); return TOK_TRUE; }
"false" { columna += yyleng; fprintf(yyout,";D:\t%s\n",yytext); return TOK_FALSE; }
{LETRA}({LETRAODIGITO})*  { columna += yyleng; if(yyleng > 100){printf("****Error en [lin %d, col %d]: Identificador demasiado largo\n(""%s"")\n",linea, columna, yytext); fprintf(yyout,";D:\t%s\n",yytext); error = 1; return TOK_ERROR;} fprintf(yyout,";D:\t%s\n",yytext); strcpy(yylval.atributos.lexema, yytext); return TOK_IDENTIFICADOR; }
{DIGITO}({DIGITO})* { columna += yyleng; yylval.atributos.valor_entero = atoi(yytext); fprintf(yyout,";D:\t%s\n",yytext); return TOK_CONSTANTE_ENTERA; }
"\t" { columna += yyleng;}
" " { columna += yyleng;}
"\n\r" { columna = 1; linea++;}
"\n" { columna = 1; linea++;}
"\r" { columna = 1; linea++;}
. { columna += yyleng; fprintf(stdout,"****Error en [lin %d, col %d]: simbolo no permitido (""%s"")\n",linea,(columna-yyleng),yytext); error = 1; return TOK_ERROR; }
%%
