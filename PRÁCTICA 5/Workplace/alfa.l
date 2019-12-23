%{
  #include <stdio.h>
  #include <string.h>
  #include "alfa.h"
  #include "y.tab.h"

  FILE * yyout;
  FILE * fpasm;

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
"main" { columna += yyleng; fprintf(yyout,";D:\t%s\n",yytext);fprintf(fpasm,";D:\t%s\n",yytext); return TOK_MAIN; }
"int" { columna += yyleng; fprintf(yyout,";D:\t%s\n",yytext);fprintf(fpasm,";D:\t%s\n",yytext); return TOK_INT; }
"boolean" { columna += yyleng; fprintf(yyout,";D:\t%s\n",yytext);fprintf(fpasm,";D:\t%s\n",yytext); return TOK_BOOLEAN; }
"array" { columna += yyleng; fprintf(yyout,";D:\t%s\n",yytext);fprintf(fpasm,";D:\t%s\n",yytext); return TOK_ARRAY; }
"function" { columna += yyleng; fprintf(yyout,";D:\t%s\n",yytext);fprintf(fpasm,";D:\t%s\n",yytext); return TOK_FUNCTION; }
"if" { columna += yyleng; fprintf(yyout,";D:\t%s\n",yytext);fprintf(fpasm,";D:\t%s\n",yytext); return TOK_IF; }
"else" { columna += yyleng; fprintf(yyout,";D:\t%s\n",yytext);fprintf(fpasm,";D:\t%s\n",yytext); return TOK_ELSE; }
"while" { columna += yyleng; fprintf(yyout,";D:\t%s\n",yytext);fprintf(fpasm,";D:\t%s\n",yytext); return TOK_WHILE; }
"scanf" { columna += yyleng; fprintf(yyout,";D:\t%s\n",yytext);fprintf(fpasm,";D:\t%s\n",yytext); return TOK_SCANF; }
"printf" { columna += yyleng; fprintf(yyout,";D:\t%s\n",yytext);fprintf(fpasm,";D:\t%s\n",yytext); return TOK_PRINTF; }
"return" { columna += yyleng; fprintf(yyout,";D:\t%s\n",yytext);fprintf(fpasm,";D:\t%s\n",yytext); return TOK_RETURN; }
"true" { columna += yyleng; fprintf(yyout,";D:\t%s\n",yytext);fprintf(fpasm,";D:\t%s\n",yytext); return TOK_TRUE; }
"false" { columna += yyleng; fprintf(yyout,";D:\t%s\n",yytext);fprintf(fpasm,";D:\t%s\n",yytext); return TOK_FALSE; }
";" { columna += yyleng; fprintf(yyout,";D:\t%s\n",yytext);fprintf(fpasm,";D:\t%s\n",yytext); return TOK_PUNTOYCOMA; }
"," { columna += yyleng; fprintf(yyout,";D:\t%s\n",yytext);fprintf(fpasm,";D:\t%s\n",yytext); return TOK_COMA; }
"(" { columna += yyleng; fprintf(yyout,";D:\t%s\n",yytext);fprintf(fpasm,";D:\t%s\n",yytext); return TOK_PARENTESISIZQUIERDO; }
")" { columna += yyleng; fprintf(yyout,";D:\t%s\n",yytext);fprintf(fpasm,";D:\t%s\n",yytext); return TOK_PARENTESISDERECHO; }
"[" { columna += yyleng; fprintf(yyout,";D:\t%s\n",yytext);fprintf(fpasm,";D:\t%s\n",yytext); return TOK_CORCHETEIZQUIERDO; }
"]" { columna += yyleng; fprintf(yyout,";D:\t%s\n",yytext);fprintf(fpasm,";D:\t%s\n",yytext); return TOK_CORCHETEDERECHO; }
"{" { columna += yyleng; fprintf(yyout,";D:\t%s\n",yytext);fprintf(fpasm,";D:\t%s\n",yytext); return TOK_LLAVEIZQUIERDA; }
"}" { columna += yyleng; fprintf(yyout,";D:\t%s\n",yytext);fprintf(fpasm,";D:\t%s\n",yytext); return TOK_LLAVEDERECHA; }
"==" { columna += yyleng; fprintf(yyout,";D:\t%s\n",yytext);fprintf(fpasm,";D:\t%s\n",yytext); return TOK_IGUAL; }
"=" { columna += yyleng; fprintf(yyout,";D:\t%s\n",yytext);fprintf(fpasm,";D:\t%s\n",yytext); return TOK_ASIGNACION; }
"+" { columna += yyleng; fprintf(yyout,";D:\t%s\n",yytext);fprintf(fpasm,";D:\t%s\n",yytext); return TOK_MAS; }
"-" { columna += yyleng; fprintf(yyout,";D:\t%s\n",yytext);fprintf(fpasm,";D:\t%s\n",yytext); return TOK_MENOS; }
"/" { columna += yyleng; fprintf(yyout,";D:\t%s\n",yytext);fprintf(fpasm,";D:\t%s\n",yytext); return TOK_DIVISION; }
"*" { columna += yyleng; fprintf(yyout,";D:\t%s\n",yytext);fprintf(fpasm,";D:\t%s\n",yytext); return TOK_ASTERISCO; }
"&&" { columna += yyleng; fprintf(yyout,";D:\t%s\n",yytext);fprintf(fpasm,";D:\t%s\n",yytext); return TOK_AND; }
"||" { columna += yyleng; fprintf(yyout,";D:\t%s\n",yytext);fprintf(fpasm,";D:\t%s\n",yytext); return TOK_OR; }
"!=" { columna += yyleng; fprintf(yyout,";D:\t%s\n",yytext);fprintf(fpasm,";D:\t%s\n",yytext); return TOK_DISTINTO; }
"!" { columna += yyleng; fprintf(yyout,";D:\t%s\n",yytext);fprintf(fpasm,";D:\t%s\n",yytext); return TOK_NOT; }
"<=" { columna += yyleng; fprintf(yyout,";D:\t%s\n",yytext);fprintf(fpasm,";D:\t%s\n",yytext); return TOK_MENORIGUAL; }
">=" { columna += yyleng; fprintf(yyout,";D:\t%s\n",yytext);fprintf(fpasm,";D:\t%s\n",yytext); return TOK_MAYORIGUAL; }
"<" { columna += yyleng; fprintf(yyout,";D:\t%s\n",yytext);fprintf(fpasm,";D:\t%s\n",yytext); return TOK_MENOR; }
">" { columna += yyleng; fprintf(yyout,";D:\t%s\n",yytext);fprintf(fpasm,";D:\t%s\n",yytext); return TOK_MAYOR; }
{LETRA}({LETRAODIGITO})*  { columna += yyleng; if(yyleng > 100){printf("****Error en [lin %d, col %d]: Identificador demasiado largo\n(""%s"")\n",linea, columna, yytext); fprintf(yyout,";D:\t%s\n",yytext);fprintf(fpasm,";D:\t%s\n",yytext); error = 1; return TOK_ERROR;} fprintf(yyout,";D:\t%s\n",yytext);fprintf(fpasm,";D:\t%s\n",yytext); strcpy(yylval.atributos.lexema, yytext); return TOK_IDENTIFICADOR; }
{DIGITO}({DIGITO})* { columna += yyleng; yylval.atributos.valor_entero = atoi(yytext); fprintf(yyout,";D:\t%s\n",yytext);fprintf(fpasm,";D:\t%s\n",yytext); return TOK_CONSTANTE_ENTERA; }
"//".* { columna += yyleng;}
" " { columna += yyleng;}
"\t" { columna += yyleng;}
"\n" { columna = 1; linea++;}
"\r" { columna = 1; linea++;}
"\n\r" { columna = 1; linea++;}
. { columna += yyleng; fprintf(stdout,"****Error en [lin %d, col %d]: simbolo no permitido (""%s"")\n",linea,(columna-yyleng),yytext); error = 1; return TOK_ERROR; }
%%
