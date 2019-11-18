%{
  #include <stdio.h>
  #include "tokens.h"

%}

%option noyywrap

DIGITO [0-9]
LETRA [a-zA-Z]
LETRAODIGITO[a-zA-Z0-9]

%%

"main" { return TOK_MAIN; }
"int" { return TOK_INT; }
"bool" { return TOK_BOOLEAN; }
"array" { return TOK_ARRAY; }
"function" { return TOK_FUNCTION; }
"if" { return TOK_IF;}
"else" { return TOK_ELSE; }
"while" { return TOK_WHILE; }
"scanf" { return TOK_SCANF; }
"printf" { return TOK_PRINTF; }
"return" { return TOK_RETURN; }

";" { return TOK_PUNTOYCOMA; }
"," { return TOK_COMA; }
"(" { return TOK_PARENTESISIZQUIERDO; }
")" { return TOK_PARENTESISDERECHO; }
"[" { return TOK_CORCHETEIZQUIERDO; }
"]" { return TOK_CORCHETEDERECHO; }
"{" { return TOK_LLAVEIZQUIERDA; }
"}" { return TOK_LLAVEDERECHA; }
"==" { return TOK_IGUAL; }
"=" { return TOK_ASIGNACION; }
"+" { return TOK_MAS; }
"-" { return TOK_MENOS; }
"/" { return TOK_DIVISION; }
"*" { return TOK_ASTERISCO; }
"&&" { return TOK_AND; }
"||" { return TOK_OR; }
"!=" { return TOK_DISTINTO; }
"!" { return TOK_NOT; }
"<=" { return TOK_MENORIGUAL; }
">=" { return TOK_MAYORIGUAL; }
"<" { return TOK_MENOR; }
">" { return TOK_MAYOR; }

{LETRA}({LETRAODIGITO})* { return TOK_IDENTIFICADOR; }  /* Cualquier combinacion de palabras y numeros */
{DIGITO}({DIGITO})* { return TOK_CONSTANTE_ENTERA; }  /* Cualquier combinacion de numeros */

"true" { return TOK_TRUE; }
"false" { return TOK_FALSE; }

"\t" { return TOK_TABULADOR; }
"//" { return TOK_COMENTARIO; }
" " { return TOK_ESPACIO; }
"\n" { return TOK_FIN_DE_LINEA; }

. { return TOK_ERROR; }  /* Todo lo demas se consideran errores morfologicos */


%%
