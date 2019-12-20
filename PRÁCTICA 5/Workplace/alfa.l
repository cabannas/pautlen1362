%{
  #include <stdio.h>
  #include <string.h>
  #include "y.tab.h"

  int linea = 1;
  int columna = 1;
  int error = 0;

%}

%option nounput
%option noinput
%option noyywrap

DIGITO [0-9]
LETRA [a-zA-Z]
LETRAODIGITO[a-zA-Z0-9]

%%
"main" { columna += yyleng; strcpy(yylval.cad,yytext); fprintf(yyout,";D:\t%s\n",yytext); return TOK_MAIN; }
"int" { columna += yyleng; strcpy(yylval.cad,yytext); fprintf(yyout,";D:\t%s\n",yytext); return TOK_INT; }
"bool" { columna += yyleng; strcpy(yylval.cad,yytext); fprintf(yyout,";D:\t%s\n",yytext); return TOK_BOOLEAN; }
"array" { columna += yyleng; strcpy(yylval.cad,yytext); fprintf(yyout,";D:\t%s\n",yytext); return TOK_ARRAY; }
"function" { columna += yyleng; strcpy(yylval.cad,yytext); fprintf(yyout,";D:\t%s\n",yytext); return TOK_FUNCTION; }
"if" { columna += yyleng; strcpy(yylval.cad,yytext); fprintf(yyout,";D:\t%s\n",yytext); return TOK_IF; }
"else" { columna += yyleng; strcpy(yylval.cad,yytext); fprintf(yyout,";D:\t%s\n",yytext); return TOK_ELSE; }
"while" { columna += yyleng; strcpy(yylval.cad,yytext); fprintf(yyout,";D:\t%s\n",yytext); return TOK_WHILE; }
"scanf" { columna += yyleng; strcpy(yylval.cad,yytext); fprintf(yyout,";D:\t%s\n",yytext); return TOK_SCANF; }
"printf" { columna += yyleng; strcpy(yylval.cad,yytext); fprintf(yyout,";D:\t%s\n",yytext); return TOK_PRINTF; }
"return" { columna += yyleng; strcpy(yylval.cad,yytext); fprintf(yyout,";D:\t%s\n",yytext); return TOK_RETURN; }
"true" { columna += yyleng; strcpy(yylval.cad,yytext); fprintf(yyout,";D:\t%s\n",yytext); return TOK_TRUE; }
"false" { columna += yyleng; strcpy(yylval.cad,yytext); fprintf(yyout,";D:\t%s\n",yytext); return TOK_FALSE; }
";" { columna += yyleng; strcpy(yylval.cad,yytext); fprintf(yyout,";D:\t%s\n",yytext); return TOK_PUNTOYCOMA; }
"," { columna += yyleng; strcpy(yylval.cad,yytext); fprintf(yyout,";D:\t%s\n",yytext); return TOK_COMA; }
"(" { columna += yyleng; strcpy(yylval.cad,yytext); fprintf(yyout,";D:\t%s\n",yytext); return TOK_PARENTESISIZQUIERDO; }
")" { columna += yyleng; strcpy(yylval.cad,yytext); fprintf(yyout,";D:\t%s\n",yytext); return TOK_PARENTESISDERECHO; }
"[" { columna += yyleng; strcpy(yylval.cad,yytext); fprintf(yyout,";D:\t%s\n",yytext); return TOK_CORCHETEIZQUIERDO; }
"]" { columna += yyleng; strcpy(yylval.cad,yytext); fprintf(yyout,";D:\t%s\n",yytext); return TOK_CORCHETEDERECHO; }
"{" { columna += yyleng; strcpy(yylval.cad,yytext); fprintf(yyout,";D:\t%s\n",yytext); return TOK_LLAVEIZQUIERDA; }
"}" { columna += yyleng; strcpy(yylval.cad,yytext); fprintf(yyout,";D:\t%s\n",yytext); return TOK_LLAVEDERECHA; }
"==" { columna += yyleng; strcpy(yylval.cad,yytext); fprintf(yyout,";D:\t%s\n",yytext); return TOK_IGUAL; }
"=" { columna += yyleng; strcpy(yylval.cad,yytext); fprintf(yyout,";D:\t%s\n",yytext); return TOK_ASIGNACION; }
"+" { columna += yyleng; strcpy(yylval.cad,yytext); fprintf(yyout,";D:\t%s\n",yytext); return TOK_MAS; }
"-" { columna += yyleng; strcpy(yylval.cad,yytext); fprintf(yyout,";D:\t%s\n",yytext); return TOK_MENOS; }
"/" { columna += yyleng; strcpy(yylval.cad,yytext); fprintf(yyout,";D:\t%s\n",yytext); return TOK_DIVISION; }
"*" { columna += yyleng; strcpy(yylval.cad,yytext); fprintf(yyout,";D:\t%s\n",yytext); return TOK_ASTERISCO; }
"&&" { columna += yyleng; strcpy(yylval.cad,yytext); fprintf(yyout,";D:\t%s\n",yytext); return TOK_AND; }
"||" { columna += yyleng; strcpy(yylval.cad,yytext); fprintf(yyout,";D:\t%s\n",yytext); return TOK_OR; }
"!=" { columna += yyleng; strcpy(yylval.cad,yytext); fprintf(yyout,";D:\t%s\n",yytext); return TOK_DISTINTO; }
"!" { columna += yyleng; strcpy(yylval.cad,yytext); fprintf(yyout,";D:\t%s\n",yytext); return TOK_NOT; }
"<=" { columna += yyleng; strcpy(yylval.cad,yytext); fprintf(yyout,";D:\t%s\n",yytext); return TOK_MENORIGUAL; }
">=" { columna += yyleng; strcpy(yylval.cad,yytext); fprintf(yyout,";D:\t%s\n",yytext); return TOK_MAYORIGUAL; }
"<" { columna += yyleng; strcpy(yylval.cad,yytext); fprintf(yyout,";D:\t%s\n",yytext); return TOK_MENOR; }
">" { columna += yyleng; strcpy(yylval.cad,yytext); fprintf(yyout,";D:\t%s\n",yytext); return TOK_MAYOR; }
{LETRA}({LETRAODIGITO})*  { columna += yyleng; strcpy(yylval.cad,yytext); if(yyleng > 100){printf("****Error en [lin %d, col %d]: Identificador demasiado largo\n(""%s"")\n",linea, columna, yytext); fprintf(yyout,";D:\t%s\n",yytext); error = 1; return TOK_ERROR;} fprintf(yyout,";D:\t%s\n",yytext); return TOK_IDENTIFICADOR; }
{DIGITO}({DIGITO})* { columna += yyleng; yylval.num = atoi(yytext); fprintf(yyout,";D:\t%s\n",yytext); return TOK_CONSTANTE_ENTERA; }
"//".* { columna += yyleng;}
" " { columna += yyleng;}
"\t" { columna += yyleng;}
"\n" { columna = 1; linea++;}
"\r" { columna = 1; linea++;}
"\n\r" { columna = 1; linea++;}
. { columna += yyleng; strcpy(yylval.cad,yytext); fprintf(stdout,"****Error en [lin %d, col %d]: simbolo no permitido (""%s"")\n",linea,(columna-yyleng),yytext); error = 1; return TOK_ERROR; }
%%
