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
programa: abrir_ambitos TOK_MAIN TOK_LLAVEIZQUIERDA declaraciones escrituraTS funciones escritura_inicio_main sentencias TOK_LLAVEDERECHA cerrar_ambitos {fprintf(yyout, ";R1:\t<programa> ::= main { <declaraciones> <funciones> <sentencias> } \n");};

abrir_ambitos: {

	tabla_global = crear_tabla(TAM_MAX_TABLA);
	tabla_local = crear_tabla(TAM_MAX_TABLA);

	escribir_subseccion_data(fpasm);
	escribir_cabecera_bss(fpasm);
}

escrituraTS:{
  escribir_segmento_codigo(fpasm);};

escritura_inicio_main:{escribir_inicio_main(fpasm);};

cerrar_ambitos:{
	if(tabla_local){
		liberar_tabla(tabla_local);
	}
	liberar_tabla(tabla_global);
	escribir_fin(fpasm);
};

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

tipo: TOK_INT {

    tipo_actual=ENTERO;
    fprintf(yyout, ";R10:\t<tipo> ::= int \n");
  }
	|TOK_BOOLEAN {

    tipo_actual=BOOLEANO;
    fprintf(yyout, ";R11:\t<tipo> ::= boolean \n");
  };


######################################################### ANDARSE CON OJO CON CLASE VECTOR #############################################################


clase_vector: TOK_ARRAY tipo TOK_CORCHETEIZQUIERDO TOK_CONSTANTE_ENTERA TOK_CORCHETEDERECHO {

    tamano_vector_actual = $4.valor_entero;

    if(tamano_vector_actual>MAX_TAMANIO_VECTOR || tamano_vector_actual < 1){
      printf("****Error semantico en lin %d: El tamano del vector <%s> excede los limites permitidos (1,64).\n",linea, nombre_vector_actual);
      return 0;
    }

    fprintf(yyout, ";R15:\t<clase_vector> ::= array <tipo> [ <constante_entera> ] \n");
  };


######################################################### ANDARSE CON OJO CON CLASE VECTOR #############################################################


identificadores: identificador {fprintf(yyout, ";R18:\t<identificadores> ::= <identificador> \n");};
	| identificador TOK_COMA identificadores {fprintf(yyout, ";R19:\t<identificadores> ::= <identificador> , <identificadores> \n");};

funciones: funcion funciones {fprintf(yyout, ";R20:\t<funciones> ::= <funcion> <funciones> \n");};
	| {fprintf(yyout, ";R21:\t<funciones> ::= \n");};

  ######################################################### MIRAR SI HAY QUE CAMBIAR LOS PRINTF #############################################################

funcion: fn_declaracion sentencias TOK_LLAVEDERECHA {

  ambito_actual=GLOBAL;
  valor = busquedaGlobal($1.lexema, tabla_global);
  valor->adicional1 = n_parametros_actual;

  if(fn_return==0){
    printf("****Error semantico en lin %d: Funcion %s sin sentencia de retorno\n", linea, $1.lexema);
    return 0;
  }
  fprintf(yyout, ";R22:\t<funcion> ::= function <tipo> <identificador> ( <parametros_funcion> ) { <declaraciones_funcion> <sentencias> } \n");
  };

fn_declaracion: fn_name TOK_PARENTESISIZQUIERDO parametros_funcion TOK_PARENTESISDERECHO TOK_LLAVEIZQUIERDA declaraciones_funcion{

  valor = busquedaGlobal($1.lexema, tabla_global);
  valor->adicional1=n_parametros_actual;
  strcpy($$.lexema, $1.lexema);

  fprintf(fpasm, "\n_%s:\n", $1.lexema);
  fprintf(fpasm, "\tpush ebp\n");
  fprintf(fpasm, "\tmov ebp, esp\n");
  fprintf(fpasm, "\tsub esp, 4*%d\n", num_variables_locales_actual);

 };

fn_name: TOK_FUNCTION tipo TOK_IDENTIFICADOR {

  valor = busquedaGlobal($3.lexema, tabla_global);

  if(valor){
    printf("****Error semantico en lin %d: Declaracion dupliacada", linea);
    return 0;
  }

  if(DeclararFuncion(tabla_global, tabla_local, $3.lexema, FUNCION, tipo_actual, ESCALAR, adicional1, 0)==OK){
    ambito_actual=LOCAL;
  }

  adicional1++;

  n_variables_locales_actual = 0;
  pos_variable_local_actual = 1;
  n_parametros_actual = 0;
  pos_parametros_actual = 0;
  fn_return = 0;

  strcpy($$.lexema, $3.lexema);
  es_funcion=1;

  tipo_return=tipo_actual;

  strcpy(nombre_funcion_actual, $3.lexema);
};


parametros_funcion: parametro_funcion resto_parametros_funcion {
fprintf(yyout, ";R23:\t<parametros_funcion> ::= <parametro_funcion> <resto_parametros_funcion> \n");};
	| {fprintf(yyout, ";R24:\t<parametros_funcion> ::= \n");};

resto_parametros_funcion: TOK_PUNTOYCOMA parametro_funcion resto_parametros_funcion {fprintf(yyout, ";R25:\t<resto_parametros_funcion> ::= ; <parametro_funcion> <resto_parametros_funcion> \n");};
	| {fprintf(yyout, ";R26:\t<resto_parametros_funcion> ::= \n");};

parametro_funcion: tipo idpf {
fprintf(yyout, ";R27:\t<parametro_funcion> ::= <tipo> <identificador> \n");};

idpf: TOK_IDENTIFICADOR {
if (DeclararVariableLocal(tabla_local, $1.lexema,PARAMETRO, tipo_actual, ESCALAR, adicional1, pos_parametros_actual) == ERR) {
	printf("****Error semantico en lin %d: Declaracion dupliacada", linea);
	return 0;
}

  adicional1++;
  pos_parametros_actual++;
  num_parametros_actual++;
};

declaraciones_funcion: declaraciones {fprintf(yyout, ";R28:\t<declaraciones_funcion> ::= <declaraciones> \n");}
	| {fprintf(yyout, ";R29:\t<declaraciones_funcion> ::= \n");};

sentencias: sentencia {fprintf(yyout, ";R30:\t<sentencias> ::= <sentencia> \n");}
	| sentencia sentencias {fprintf(yyout, ";R31:\t<sentencias> ::= <sentencia> <sentencias> \n");};

sentencia: sentencia_simple TOK_PUNTOYCOMA {fprintf(yyout, ";R32:\t<sentencia> ::= <sentencia_simple> ; \n");}
	| bloque {fprintf(yyout, ";R33:\t<sentencia> ::= <bloque> \n");};

sentencia_simple: asignacion {fprintf(yyout, ";R34:\t<sentencia_simple> ::= <asignacion> \n");}
	| lectura {fprintf(yyout, ";R35:\t<sentencia_simple> ::= <lectura> \n");}
	| escritura {fprintf(yyout, ";R36:\t<sentencia_simple> ::= <escritura> \n");}
	| retorno_funcion {fprintf(yyout, ";R38:\t<sentencia_simple> ::= <retorno_funcion> \n");};

bloque: condicional {fprintf(yyout, ";R40:\t<bloque> ::= <condicional> \n");}
	| bucle {fprintf(yyout, ";R41:\t<bloque> ::= <bucle> \n");};

asignacion: TOK_IDENTIFICADOR TOK_ASIGNACION exp {
  if (ambito_actual == GLOBAL) {
	valor = busquedaGlobal($1.lexema, tabla_global);
  }else {
	valor = busquedaLocal($1.lexema, tabla_global,tabla_local);
  }
  if(valor == NULL){
	printf("****Error semantico en lin %d: Acceso a variable no declarada (%s)\n", linea, $1.lexema);
	return 0;
  }
  if(valor->tipo != $3.tipo || valor->clase == VECTOR || valor->categoria == FUNCION ){
	printf("****Error semantico en lin %d: Asignacion incompatible\n", linea);
	return 0;
  }


if(valor->categoria == PARAMETRO){
	asignar_parametro(fpasm, num_parametros_actual, valor->adicional2, $3.es_direccion);
}
else if(valor->adicional2 == 0){
	asignar_ident(fpasm, $1.lexema, $3.es_direccion);
}
else {
	asignar_local(fpasm, valor->adicional2, $3.es_direccion);
}

  fprintf(yyout, ";R43:\t<asignacion> ::= <identificador> = <exp> \n");}
  | elemento_vector TOK_ASIGNACION exp {

  if($1.tipo != $3.tipo){
	printf("****Error semantico en lin %d: Asignacion no compatible\n", linea);
	return 0;
  }

  asignar_vector(fpasm, $3.es_direccion);
  fprintf(yyout, ";R44:\t<asignacion> ::= <elemento_vector> = <exp> \n");};

elemento_vector: TOK_IDENTIFICADOR TOK_CORCHETEIZQUIERDO exp TOK_CORCHETEDERECHO {
  if (ambito_actual == GLOBAL) {
	valor = busquedaGlobal($1.lexema, tabla_global);
  }else {
	valor = busquedaLocal($1.lexema, tabla_global,tabla_local);
  }
  if(valor == NULL){
	printf("****Error semantico en lin %d: Acceso a variable sin declarar (%s)\n", linea, $1.lexema);
	return 0;
  }
  if(valor->clase != VECTOR){
	printf("****Error semantico en lin %d: Indexacion de una variable que no es de tipo vector (%s)\n", linea, $1.lexema);
	return 0;
  }
  if($3.tipo != ENTERO){
	printf("****Error semantico en lin %d: El indice en una indexacion debe ser de tipo entero (%s)\n", linea, $1.lexema);
	return 0;
  }
  $$.es_direccion = 1;
  $$.tipo = valor->tipo;

  control_errores_vector(fpasm, $1.lexema, $3.es_direccion , valor->adicional1);
  fprintf(yyout, ";R48:\t<elemento_vector> ::= <identificador> [ <exp> ] \n");};

condicional:  if_exp sentencias TOK_LLAVEDERECHA {

  fprintf(fpasm, "\nfin_si%d:\n", $1.etiqueta);
  fprintf(yyout, ";R50:\t<condicional> ::= if ( <exp> ) { <sentencias> } \n");}

  | if_exp_sentencias TOK_ELSE TOK_LLAVEIZQUIERDA sentencias TOK_LLAVEDERECHA {
    fprintf(fpasm, "\nfin_sino%d:\n", $1.etiqueta);
    fprintf(yyout, ";R51:\t<condicional> ::= if ( <exp> ) { <sentencias> } else { <sentencias> } \n");
  };

if_exp: TOK_IF TOK_PARENTESISIZQUIERDO exp TOK_PARENTESISDERECHO TOK_LLAVEIZQUIERDA {
  if($3.tipo != BOOLEANO){
    printf("****Error semantico en lin %d: Condicional sin elemento booleano\n", linea);
    return 0;
  }
  $$.etiqueta = etiqueta ++;

  abrir_if(fpasm, $$.etiqueta, $3.es_direccion);
};


if_exp_sentencias: if_exp sentencias TOK_LLAVEDERECHA {

  $$.etiqueta = $1.etiqueta;

  fprintf(fpasm, "\n\tjmp near fin_sino%d\n", $1.etiqueta);
  fprintf(fpasm, "\nfin_si%d:\n", $1.etiqueta);
};

##############################################################################################################################

bucle: while_exp sentencias TOK_LLAVEDERECHA {

  fprintf(fpasm, "\n\n\tjmp near inicio_while%d\n", $1.etiqueta);
  fprintf(fpasm, "\nfin_while%d:\n", $1.etiqueta);
  fprintf(yyout, ";R52:\t<bucle> ::= while ( <exp> ) { <sentencias> } \n");
};

lectura: TOK_SCANF TOK_IDENTIFICADOR {

  if(ambito_actual == GLOBAL){
    valor = busquedaGlobal($2.lexema, tabla_global);
  }else{
    valor = busquedaLocal($2.lexema, tabla_global, tabla_local);
  }

  if(valor == NULL){
  		printf("****Error semantico en lin %d: Acceso a variable sin declarar (%s).\n", linea, $2.lexema);
  		return 0;
  }

  /*Comprobaciones semanticas*/
  if(valor->categoria == FUNCION){
    printf("****Error semantico en lin %d: Asignacion no compatible.\n", linea);
    return 0;
  }
  if(valor->clase == VECTOR){
    printf("****Error semantico en lin %d: Asignacion no compatible.\n", linea);
    return 0;
  }

	if(valor->categoria == PARAMETRO){
		leer_parametro(fpasm, valor->tipo, num_parametros_actual, valor->adicional2);
	} else if(valor->adicional2 == 0){
		leer(fpasm, valor->lexema, valor->tipo);
	} else{
		leer_local(fpasm, valor->tipo, valor->adicional2);
	}

  fprintf(yyout, ";R54:\t<lectura> ::= scanf <identificador> \n");
};

escritura: TOK_PRINTF exp {

  escribir(fpasm, $2.es_direccion, $2.tipo);
  fprintf(yyout, ";R56:\t<escritura> ::= printf <exp> \n");
};

retorno_funcion: TOK_RETURN exp {

  if((($2.es_direccion != 1) && ($2.es_direccion != 0)) || $2.tipo != tipo_return){
  	printf("****Error semantico en lin %d: Sentencia de retorno fuera de una función.\n", linea);
  	return 0;
  }

  retorno_funcion(fpasm, $2.es_direccion);
  fn_return++;
  fprintf(yyout, ";R61:\t<retorno_funcion> ::= return <exp> \n");
};

############################################################## RETOMAR DESDE AQUI HASTA ABAJO ################################################################


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
