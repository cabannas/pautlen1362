%{
#include <stdio.h>
#include <string.h>

#include "generacion.h"
#include "y.tab.h"
#include "tablaSimbolos.h"
#include "alfa.h"
#include "tablaHash.h"

extern FILE * fpasm;
extern FILE * yyout;
extern int yylex();
extern int yyleng;
extern int linea, columna, error;
void yyerror(char* s);

TABLA_HASH * tabla_global = NULL;
TABLA_HASH * tabla_local = NULL;

INFO_SIMBOLO* valor;
INFO_SIMBOLO* valor1;
INFO_SIMBOLO* valor2;

/* para los ids */
AMBITO ambito_actual;
CATEGORIA categoria_actual;
CLASE clase_actual;
TIPO tipo_actual;

/* para los parametros */
int adicional1;
int declarar;
int tipo_retorno;
int en_exp_list;

/* para los vectores */

/* tamano del vector actual */
int tamano_vector_actual = 1;
/* nombre del vector actual*/
int nombre_vector_actual[MAX_LON_ID];


/* para las funciones */

/* numero de variables locales */
int n_variables_locales_actual;
 /* posicion de la variable local */
int pos_variable_local_actual;
/* numero parametros actual */
int n_parametros_actual;
/* numero de parametros que se llama actualmente */
int n_parametros_llamada_actual;
/* posicion del parametro */
int pos_parametros_actual;
/* posicion de la llamada del parametro */
int pos_parametros_llamada_actual;
/* el retorno de la funcion */
int fn_retorno;
/* flag que nos dice si estamos dentro de una función o no */
int es_funcion = 0;
/* numero de etiquetas para nasm */
int etiqueta = 1;
/* identificador string de la funcion */
char nombre_funcion_actual[MAX_LON_ID];
/* define el tipo de retorno de la funcion (int o bool)*/
TIPO tipo_retorno_funcion;

%}

%union
{
	tipo_atributos atributos;
}

%token TOK_MAIN
%token TOK_LLAVEIZQUIERDA
%token TOK_LLAVEDERECHA
%token TOK_PUNTOYCOMA
%token TOK_INT
%token TOK_BOOLEAN
%token TOK_ARRAY
%token TOK_CORCHETEIZQUIERDO
%token TOK_CORCHETEDERECHO
%token TOK_COMA
%token TOK_FUNCTION
%token TOK_PARENTESISIZQUIERDO
%token TOK_PARENTESISDERECHO
%token TOK_ASIGNACION
%token TOK_IF
%token TOK_ELSE
%token TOK_WHILE
%token TOK_SCANF
%token TOK_PRINTF

%token TOK_RETURN

%token TOK_MAS
%token TOK_MENOS
%token TOK_DIVISION
%token TOK_ASTERISCO
%token TOK_AND
%token TOK_OR
%token TOK_NOT

%token TOK_IGUAL
%token TOK_DISTINTO
%token TOK_MENORIGUAL
%token TOK_MAYORIGUAL
%token TOK_MENOR
%token TOK_MAYOR

%token TOK_TRUE
%token TOK_FALSE

%token <atributos> TOK_CONSTANTE_ENTERA
%token <atributos> TOK_IDENTIFICADOR

%token TOK_ERROR

%type <atributos> elemento_vector
%type <atributos> lectura
%type <atributos> identificador
%type <atributos> constante_entera
%type <atributos> constante_logica
%type <atributos> constante

%type <atributos> asignacion
%type <atributos> exp
%type <atributos> comparacion
%type <atributos> if_exp


%type <atributos> funcion
%type <atributos> fn_declaracion
%type <atributos> fn_name
%type <atributos> idf_llamada_funcion


%type <atributos> condicional
%type <atributos> if_exp_sentencias
%type <atributos> bucle
%type <atributos> while
%type <atributos> while_exp

/* definimos la asociatividad */

%left TOK_MAS TOK_MENOS TOK_ASTERISCO TOK_DIVISION
%left TOK_OR TOK_AND

%right TOK_NOT
%right NEG


%start programa

%%
programa: abrir_ambitos TOK_MAIN TOK_LLAVEIZQUIERDA declaraciones funciones sentencias TOK_LLAVEDERECHA {fprintf(yyout, ";R1:\t<programa> ::= main { <declaraciones> <funciones> <sentencias> } \n");};

abrir_ambitos: {

	tabla_global = crear_tabla(TAM_MAX_TABLA);
	tabla_local = crear_tabla(TAM_MAX_TABLA);

	escribir_subseccion_data(fpasm);
	escribir_cabecera_bss(fpasm);
}

declaraciones: declaracion {fprintf(yyout, ";R2:\t<declaraciones> ::= <declaracion> \n");};
	| declaracion declaraciones {fprintf(yyout, ";R3:\t<declaraciones> ::= <declaracion> <declaraciones> \n");};

declaracion: clase identificadores TOK_PUNTOYCOMA {fprintf(yyout, ";R4:\t<declaracion> ::= <clase> <identificadores> ; \n");};

clase: clase_escalar {

		tamano_vector_actual = 1;
		clase_actual = ESCALAR;

		fprintf(yyout, ";R5:\t<clase> ::= <clase_escalar> \n");
	}
	| clase_vector {

		clase_actual = VECTOR;
		fprintf(yyout, ";R7:\t<clase> ::= <clase_vector> \n");
	};

clase_escalar: tipo {fprintf(yyout, ";R9:\t<clase_escalar> ::= <tipo> \n");};

tipo: TOK_INT {fprintf(yyout, ";R10:\t<tipo> ::= int \n");};
	| TOK_BOOLEAN {fprintf(yyout, ";R11:\t<tipo> ::= boolean \n");};

clase_vector: TOK_ARRAY tipo TOK_CORCHETEIZQUIERDO constante_entera TOK_CORCHETEDERECHO {fprintf(yyout, ";R15:\tarray <tipo> [ <constante_entera> ] \n");};

identificadores: identificador {fprintf(yyout, ";R18:\t<identificadores> ::= <identificador> \n");};
	| identificador TOK_COMA identificadores {fprintf(yyout, ";R19:\t<identificadores> ::= <identificador> , <identificadores> \n");};

funciones: funcion funciones {fprintf(yyout, ";R20:\t<funciones> ::= <funcion> <funciones> \n");};
	| {fprintf(yyout, ";R21:\t<funciones> ::= \n");};

funcion: TOK_FUNCTION tipo identificador TOK_PARENTESISIZQUIERDO parametros_funcion TOK_PARENTESISDERECHO TOK_LLAVEIZQUIERDA declaraciones_funcion sentencias TOK_LLAVEDERECHA {fprintf(yyout, ";R22:\t<funcion> ::= function <tipo> <identificador> ( <parametros_funcion> ) { <declaraciones_funcion> <sentencias> } \n");};

parametros_funcion: parametro_funcion resto_parametros_funcion {fprintf(yyout, ";R23:\t<parametros_funcion> ::= <parametro_funcion> <resto_parametros_funcion> \n");};
	| {fprintf(yyout, ";R24:\t<parametros_funcion> ::= \n");};

resto_parametros_funcion: TOK_PUNTOYCOMA parametro_funcion resto_parametros_funcion {fprintf(yyout, ";R25:\t<resto_parametros_funcion> ::= ; <parametro_funcion> <resto_parametros_funcion> \n");};
	| {fprintf(yyout, ";R26:\t<resto_parametros_funcion> ::= \n");};

parametro_funcion: tipo identificador {fprintf(yyout, ";R27:\t<parametro_funcion> ::= <tipo> <identificador> \n");};

declaraciones_funcion: declaraciones {fprintf(yyout, ";R28:\t<declaraciones_funcion> ::= <declaraciones> \n");};
	| {fprintf(yyout, ";R29:\t<declaraciones_funcion> ::= \n");};

sentencias: sentencia {fprintf(yyout, ";R30:\t<sentencias> ::= <sentencia> \n");};
	| sentencia sentencias {fprintf(yyout, ";R31:\t<sentencias> ::= <sentencia> <sentencias> \n");};

sentencia: sentencia_simple TOK_PUNTOYCOMA {fprintf(yyout, ";R32:\t<sentencia> ::= <sentencia_simple> ; \n");};
	| bloque {fprintf(yyout, ";R33:\t<sentencia> ::= <bloque> \n");};

sentencia_simple: asignacion {fprintf(yyout, ";R34:\t<sentencia_simple> ::= <asignacion> \n");};
	| lectura {fprintf(yyout, ";R35:\t<sentencia_simple> ::= <lectura> \n");};
	| escritura {fprintf(yyout, ";R36:\t<sentencia_simple> ::= <escritura> \n");};
	| retorno_funcion {fprintf(yyout, ";R38:\t<sentencia_simple> ::= <retorno_funcion> \n");};

bloque: condicional {fprintf(yyout, ";R40:\t<bloque> ::= <condicional> \n");};
	| bucle {fprintf(yyout, ";R41:\t<bloque> ::= <bucle> \n");};

asignacion: identificador TOK_ASIGNACION exp {fprintf(yyout, ";R43:\t<asignacion> ::= <identificador> = <exp> \n");};
 | elemento_vector TOK_ASIGNACION exp {fprintf(yyout, ";R44:\t<asignacion> ::= <elemento_vector> = <exp> \n");};

elemento_vector: identificador TOK_CORCHETEIZQUIERDO exp TOK_CORCHETEDERECHO {fprintf(yyout, ";R48:\t<elemento_vector> ::= <identificador> [ <exp> ] \n");};

condicional: TOK_IF TOK_PARENTESISIZQUIERDO exp TOK_PARENTESISDERECHO TOK_LLAVEIZQUIERDA sentencias TOK_LLAVEDERECHA {fprintf(yyout, ";R50:\t<condicional> ::= if ( <exp> ) { <sentencias> } \n");};
	| TOK_IF TOK_PARENTESISIZQUIERDO exp TOK_PARENTESISDERECHO TOK_LLAVEIZQUIERDA sentencias TOK_LLAVEDERECHA TOK_ELSE TOK_LLAVEIZQUIERDA sentencias TOK_LLAVEDERECHA {fprintf(yyout, ";R51:\t<condicional> ::= if ( <exp> ) { <sentencias> } else { <sentencias> } \n");};

bucle: TOK_WHILE TOK_PARENTESISIZQUIERDO exp TOK_PARENTESISDERECHO TOK_LLAVEIZQUIERDA sentencias TOK_LLAVEDERECHA {fprintf(yyout, ";R52:\t<bucle> ::= while ( <exp> ) { <sentencias> } \n");};

lectura: TOK_SCANF identificador {fprintf(yyout, ";R54:\t<lectura> ::= scanf <identificador> \n");};

escritura: TOK_PRINTF exp {fprintf(yyout, ";R56:\t<escritura> ::= printf <exp> \n");};

retorno_funcion: TOK_RETURN exp {fprintf(yyout, ";R61:\t<retorno_funcion> ::= return <exp> \n");};

exp: exp TOK_MAS exp {fprintf(yyout, ";R72:\t<exp> ::= <exp> + <exp> \n");};
	| exp TOK_MENOS exp {fprintf(yyout, ";R73:\t<exp> ::= <exp> - <exp> \n");};
	| exp TOK_DIVISION exp {fprintf(yyout, ";R74:\t<exp> ::= <exp> / <exp> \n");};
	| exp TOK_ASTERISCO exp {fprintf(yyout, ";R75:\t<exp> ::= <exp> * <exp> \n");};
	| TOK_MENOS exp %prec NEG {fprintf(yyout, ";R76:\t<exp> ::= - <exp> \n");};
	| exp TOK_AND exp {fprintf(yyout, ";R77:\t<exp> ::= <exp> && <exp> \n");};
	| exp TOK_OR exp {fprintf(yyout, ";R78:\t<exp> ::= <exp> || <exp> \n");};
	| TOK_NOT exp {fprintf(yyout, ";R79:\t<exp> ::= ! <exp> \n");};
	| identificador {fprintf(yyout, ";R80:\t<exp> ::= <identificador> \n");};
	| constante {fprintf(yyout, ";R81:\t<exp> ::= <constante> \n");};
	| TOK_PARENTESISIZQUIERDO exp TOK_PARENTESISDERECHO {fprintf(yyout, ";R82:\t<exp> ::= ( <exp> ) \n");};
	| TOK_PARENTESISIZQUIERDO comparacion TOK_PARENTESISDERECHO {fprintf(yyout, ";R83:\t<exp> ::= ( <comparacion> ) \n");};
	| elemento_vector {fprintf(yyout, ";R85:\t<exp> ::= <elemento_vector> \n");};
	| identificador TOK_PARENTESISIZQUIERDO lista_expresiones TOK_PARENTESISDERECHO  {fprintf(yyout, ";R88:\t<exp> ::= <identificador> ( <lista_expresiones> ) \n");};

lista_expresiones: exp resto_lista_expresiones {fprintf(yyout, ";R89:\t<lista_expresiones> ::= <exp> <resto_lista_expresiones> \n");};
	| {fprintf(yyout, ";R90:\t<lista_expresiones> ::=  \n");};

resto_lista_expresiones: TOK_COMA exp resto_lista_expresiones {fprintf(yyout, ";R91\t<resto_lista_expresiones> ::= , <exp> <resto_lista_expresiones> \n");};
	| {fprintf(yyout, ";R92:\t<resto_lista_expresiones> ::=  \n");};

comparacion: exp TOK_IGUAL exp {fprintf(yyout, ";R93:\t<comparacion> ::= <exp> == <exp> \n");};
	| exp TOK_DISTINTO exp {fprintf(yyout, ";R94:\t<comparacion> ::= <exp> != <exp> \n");};
	| exp TOK_MENORIGUAL exp {fprintf(yyout, ";R95:\t<comparacion> ::= <exp> <= <exp> \n");};
	| exp TOK_MAYORIGUAL exp {fprintf(yyout, ";R96:\t<comparacion> ::= <exp> >= <exp> \n");};
	| exp TOK_MENOR exp {fprintf(yyout, ";R97:\t<comparacion> ::= <exp> < <exp> \n");};
	| exp TOK_MAYOR exp {fprintf(yyout, ";R98:\t<comparacion> ::= <exp> > <exp> \n");};

constante: constante_logica {fprintf(yyout, ";R99:\t<constante> ::= <constante_logica> \n");};
	| constante_entera {fprintf(yyout, ";R100:\t<constante> ::= <constante_entera> \n");};

constante_logica: TOK_TRUE {fprintf(yyout, ";R102:\t<constante_logica> ::= true \n");};
	| TOK_FALSE {fprintf(yyout, ";R103:\t<constante_logica> ::= false \n");};

/* Hemos implementado constante entera de esta forma, ya que es mucho mas sencillo
que desarrollar todas las reglas que nos viene en la gramatica de alfa propuesta */
constante_entera: TOK_CONSTANTE_ENTERA {fprintf(yyout, ";R104:\t<constante_entera> ::= TOK_CONSTANTE_ENTERA \n");};

/* Hemos implementado identificador de esta forma, ya que es mucho mas sencillo
que desarrollar todas las reglas que nos viene en la gramatica de alfa propuesta */
identificador: TOK_IDENTIFICADOR {fprintf(yyout, ";R108:\t<identificador> ::= TOK_IDENTIFICADOR \n");};

%%

void yyerror(char* s){
	if(error == 0){
		fprintf(stdout,"**** Error sintáctico en [lin %d, col %d]\n",linea, (columna-yyleng));
	}
	error = 0;
}
