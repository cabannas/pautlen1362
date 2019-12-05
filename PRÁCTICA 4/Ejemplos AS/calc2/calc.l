%option noyywrap

%{
#include <stdio.h>
#define YY_DECL int yylex()
#include "calc.tab.h"
FILE* out;
%}

%%

[ \t]	; // ignore all whitespace
[0-9]+		{ 
    fprintf(out, "T_INT:\t%s\n",yytext);
    yylval.ival = atoi(yytext); 
    return T_INT;
}
\n		{fprintf(out, "T_NEWLINE\n"); return T_NEWLINE;}
"+"		{fprintf(out, "T_PLUS\n"); return T_PLUS;}
"-"		{fprintf(out, "T_MINUS\n"); return T_MINUS;}
"*"		{fprintf(out, "T_MULTIPLY\n"); return T_MULTIPLY;}
"("		{fprintf(out, "T_LEFT\n"); return T_LEFT;}
")"		{fprintf(out, "T_RIGHT\n"); return T_RIGHT;}
"quit"	{fprintf(out, "T_QUIT\n"); return T_QUIT;}

%%
