#include <stdio.h>
#include <string.h>

#include "tokens.h"

int main(int argc, char * argv[]) {

  FILE * yyin;  // Fichero de entrada para yylex
  FILE * yyout;  // Fichero de salida para yylex

  int yylex(); // Ejecutamos yylex

  char * yytext;
  int yyleng;

  /* Variables de control */
  int tok = 1;
  int fil =1, col = 1;


  // Abrimos los ficheros de entrada y salida de yylex
  yyin = fopen(argv[1], "r");

  yyout = fopen(argv[2]. "w");

  // Analizamos el fichero de entrada con un bucle while y escribimos en el
  // fichero de salida

  while(tok != 0){

    // Recibimos el token del yylex
    tok = yylex()

    switch(tok){

      case TOK_MAIN:
        fprintf(yyout, "TOK_MAIN\t%d\t%s\n", TOK_MAIN, yytext );
        col += yyleng;
        break;

      case TOK_INT:
        fprintf(yyout, "TOK_INT\t%d\t%s\n", TOK_INT, yytext );
        col += yyleng;
        break;

      case TOK_BOOLEAN:
        fprintf(yyout, "TOK_BOOLEAN\t%d\t%s\n", TOK_BOOLEAN, yytext );
        col += yyleng;
        break;

      case TOK_ARRAY:
        fprintf(yyout, "TOK_ARRAY\t%d\t%s\n", TOK_ARRAY, yytext );
        col += yyleng;
        break;

      case TOK_FUNCTION:
        fprintf(yyout, "TOK_FUNCTION\t%d\t%s\n", TOK_FUNCTION, yytext );
        col += yyleng;
        break;

      case TOK_IF:
        fprintf(yyout, "TOK_IF\t%d\t%s\n", TOK_IF, yytext );
        col += yyleng;
        break;

      case TOK_ELSE:
        fprintf(yyout, "TOK_ELSE\t%d\t%s\n", TOK_ELSE, yytext );
        col += yyleng;
        break;

      case TOK_WHILE:
        fprintf(yyout, "TOK_WHILE\t%d\t%s\n", TOK_WHILE, yytext );
        col += yyleng;
        break;

      case TOK_SCANF:
        fprintf(yyout, "TOK_SCANF\t%d\t%s\n", TOK_SCANF, yytext );
        col += yyleng;
        break;

      case TOK_PRINTF:
        fprintf(yyout, "TOK_PRINTF\t%d\t%s\n", TOK_PRINTF, yytext );
        col += yyleng;
        break;

      case TOK_RETURN:
        fprintf(yyout, "TOK_RETURN\t%d\t%s\n", TOK_RETURN, yytext );
        col += yyleng;
        break;

      case TOK_PUNTOYCOMA:
        fprintf(yyout, "TOK_PUNTOYCOMA\t%d\t%s\n", TOK_PUNTOYCOMA, yytext );
        col += yyleng;
        break;

      case TOK_COMA:
        fprintf(yyout, "TOK_COMA\t%d\t%s\n", TOK_COMA, yytext );
        col += yyleng;
        break;

      case TOK_PARENTESISIZQUIERDO:
        fprintf(yyout, "TOK_PARENTESISIZQUIERDO\t%d\t%s\n", TOK_PARENTESISIZQUIERDO, yytext );
        col += yyleng;
        break;

      case TOK_PARENTESISDERECHO:
        fprintf(yyout, "TOK_PARENTESISDERECHO\t%d\t%s\n", TOK_PARENTESISDERECHO, yytext );
        col += yyleng;
        break;

      case TOK_CORCHETEIZQUIERDO:
        fprintf(yyout, "TOK_CORCHETEIZQUIERDO\t%d\t%s\n", TOK_CORCHETEIZQUIERDO, yytext );
        col += yyleng;
        break;

      case TOK_CORCHETEDERECHO:
        fprintf(yyout, "TOK_CORCHETEDERECHO\t%d\t%s\n", TOK_CORCHETEDERECHO, yytext );
        col += yyleng;
        break;

      case TOK_LLAVEIZQUIERDA:
        fprintf(yyout, "TOK_LLAVEIZQUIERDA\t%d\t%s\n", TOK_LLAVEIZQUIERDA, yytext );
        col += yyleng;
        break;

      case TOK_LLAVEDERECHA:
        fprintf(yyout, "TOK_LLAVEDERECHA\t%d\t%s\n", TOK_LLAVEDERECHA, yytext );
        col += yyleng;
        break;

      case TOK_IGUAL:
        fprintf(yyout, "TOK_IGUAL\t%d\t%s\n", TOK_IGUAL, yytext );
        col += yyleng;
        break;

      case TOK_ASIGNACION:
        fprintf(yyout, "TOK_ASIGNACION\t%d\t%s\n", TOK_ASIGNACION, yytext );
        col += yyleng;
        break;

      case TOK_MAS:
        fprintf(yyout, "TOK_MAS\t%d\t%s\n", TOK_MAS, yytext );
        col += yyleng;
        break;

      case TOK_MENOS:
        fprintf(yyout, "TOK_MENOS\t%d\t%s\n", TOK_MENOS, yytext );
        col += yyleng;
        break;

      case TOK_DIVISION:
        fprintf(yyout, "TOK_DIVISION\t%d\t%s\n", TOK_DIVISION, yytext );
        col += yyleng;
        break;

      case TOK_ASTERISCO:
        fprintf(yyout, "TOK_ASTERISCO\t%d\t%s\n", TOK_ASTERISCO, yytext );
        col += yyleng;
        break;

      case TOK_AND:
        fprintf(yyout, "TOK_AND\t%d\t%s\n", TOK_AND, yytext );
        col += yyleng;
        break;

      case TOK_OR:
        fprintf(yyout, "TOK_OR\t%d\t%s\n", TOK_OR, yytext );
        col += yyleng;
        break;

      case TOK_DISTINTO:
        fprintf(yyout, "TOK_DISTINTO\t%d\t%s\n", TOK_DISTINTO, yytext );
        col += yyleng;
        break;

      case TOK_NOT:
        fprintf(yyout, "TOK_NOT\t%d\t%s\n", TOK_NOT, yytext );
        col += yyleng;
        break;

      case TOK_MENORIGUAL:
        fprintf(yyout, "TOK_MENORIGUAL\t%d\t%s\n", TOK_MENORIGUAL, yytext );
        col += yyleng;
        break;

      case TOK_MAYORIGUAL:
        fprintf(yyout, "TOK_MAYORIGUAL\t%d\t%s\n", TOK_MAYORIGUAL, yytext );
        col += yyleng;
        break;

      case TOK_MENOR:
        fprintf(yyout, "TOK_MENOR\t%d\t%s\n", TOK_MENOR, yytext );
        col += yyleng;
        break;

      case TOK_MAYOR:
        fprintf(yyout, "TOK_MAYOR\t%d\t%s\n", TOK_MAYOR, yytext );
        col += yyleng;
        break;

      case TOK_IDENTIFICADOR:
        if(yyleng > 100){
          printf("****Error en [lin %d, col %d]: identificador demasiado largo\n(%s)", fil, col, yytext);
    			return -1;
    		}
        fprintf(yyout, "TOK_IDENTIFICADOR\t%d\t%s\n", TOK_IDENTIFICADOR, yytext );
        col += yyleng;
        break;

      case TOK_CONSTANTE_ENTERA:
        fprintf(yyout, "TOK_CONSTANTE_ENTERA\t%d\t%s\n", TOK_CONSTANTE_ENTERA, yytext );
        col += yyleng;
        break;

      case TOK_TRUE:
        fprintf(yyout, "TOK_TRUE\t%d\t%s\n", TOK_TRUE, yytext );
        col += yyleng;
        break;

      case TOK_FALSE:
        fprintf(yyout, "TOK_FALSE\t%d\t%s\n", TOK_FALSE, yytext );
        col += yyleng;
        break;

      /* Los tabuladores los obviamos */
      case TOK_TABULADOR:
        col += yyleng;
        break;

      /* Los espacios los obviamos */
      case TOK_ESPACIO:
        col += yyleng;
        break;

      /* Los fin de linea los obviamos */
      case TOK_FIN_DE_LINEA:
        fil++;  // Aumentamos la fila
        col = 1;  // Reseteamos la columna
        break;

      /* Los comentarios los obviamos */
      case TOK_COMENTARIO:
        while(tok != TOK_FIN_DE_LINEA){
          tok = yylex();
        }
        fil++;  // Aumentamos la fila
        col = 1;  // Reseteamos la columna
        break;

      default:
        if (tok == 0){
          break;
        }
      printf("****Error en [lin %d, col %d]: simbolo no permitido (%s)\n", fil, col, yytext);
      return -1;
    }

    return 0;
  }






}
