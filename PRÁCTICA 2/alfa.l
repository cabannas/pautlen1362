%{
  #include <stdio.h>

%}
%option noyywrap
%%

"main" { printf("-> TOK_MAIN\n"); }
"int" { printf("-> TOK_INT\n"); }
"bool" { printf("-> TOK_BOOLEAN\n"); }


"array" { printf("-> TOK_ARRAY\n"); }                     ///////////////////////////////////////////////////OJAZO, POR CONFIRMAR
"function" { printf("-> TOK_FUNCTION\n"); }               ///////////////////////////////////////////////////OJAZO, POR CONFIRMAR

"if" { printf("-> TOK_IF\n"); }
"else" { printf("-> TOK_ELSE\n"); }
"while" { printf("-> TOK_WHILE\n"); }
"scanf" { printf("-> TOK_SCANF\n"); }
"printf" { printf("-> TOK_PRINTF\n"); }
"return" { printf("-> TOK_RETURN\n"); }



";" { printf("-> TOK_PUNTOYCOMA\n"); }
"," { printf("-> TOK_COMA\n"); }
"(" { printf("-> TOK_PARENTESISIZQUIERDO\n"); }
")" { printf("-> TOK_PARENTESISDERECHO\n"); }
"[" { printf("-> TOK_CORCHETEIZQUIERDO\n"); }
"]" { printf("-> TOK_CORCHETEDERECHO\n"); }
"{" { printf("-> TOK_LLAVEIZQUIERDA\n"); }
"}" { printf("-> TOK_LLAVEDERECHA\n"); }
"=" { printf("-> TOK_ASIGNACION\n"); }
"+" { printf("-> TOK_MAS\n"); }
"-" { printf("-> TOK_MENOS\n"); }
"/" { printf("-> TOK_DIVISION\n"); }
"*" { printf("-> TOK_ASTERISCO\n"); }
"&&" { printf("-> TOK_AND\n"); }
"||" { printf("-> TOK_OR\n"); }
"!" { printf("-> TOK_NOT\n"); }
"==" { printf("-> TOK_IGUAL\n"); }
"!=" { printf("-> TOK_DISTINTO\n"); }
"<=" { printf("-> TOK_MENORIGUAL\n"); }
">=" { printf("-> TOK_MAYORIGUAL\n"); }
"<" { printf("-> TOK_MENOR\n"); }
">" { printf("-> TOK_MAYOR\n"); }



"id" { printf("-> TOK_IDENTIFICADOR\n"); }                ///////////////////////////////////////////////////OJAZO, POR CONFIRMAR



"const int" { printf("-> TOK_CONSTANTE_ENTERA\n"); }      ///////////////////////////////////////////////////OJAZO, POR CONFIRMAR

"true" { printf("-> TOK_TRUE\n"); }
"false" { printf("-> TOK_FALSE\n"); }



"error" { printf("-> TOK_ERROR\n"); }                     ///////////////////////////////////////////////////OJAZO, POR CONFIRMAR




%%
int main() {
return yylex();
}
