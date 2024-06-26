%{
#include <stdio.h>
#include <string.h>

#include "alfa.h"
#include "tabla_hash.h"
#include "tabla_simbolos.h"
#include "generacion.h"
#include "y.tab.h"

extern FILE * fpasm;
extern FILE * yyout;
extern int yylex();
extern int yyleng;
extern int linea, columna, error;
void yyerror(char* s);

TABLA_HASH * tabla_global = NULL;
TABLA_HASH * tabla_local = NULL;

INFO_SIMBOLO* valor;

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
char nombre_vector_actual[MAX_LON_ID];


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
/* el retorno de la funcion */
int fn_retorno;
/* flag que nos dice si estamos dentro de una función o no */
int es_funcion = 0;
/* numero de etiquetas para nasm */
int etiqueta = 1;
/* identificador string de la funcion */
char nombre_funcion_actual[MAX_LON_ID];


%}
%union{
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

%token TOK_ERROR

%token <atributos> TOK_IDENTIFICADOR
%token <atributos> TOK_CONSTANTE_ENTERA

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
programa: abrir_ambitos TOK_MAIN TOK_LLAVEIZQUIERDA declaraciones escrituraTS funciones escritura_inicio_main sentencias TOK_LLAVEDERECHA cerrar_ambitos {
	fprintf(fpasm, ";R1:\t<programa> ::= main { <declaraciones> <funciones> <sentencias> } \n");
	fprintf(yyout, ";R1:\t<programa> ::= main { <declaraciones> <funciones> <sentencias> } \n");
};

abrir_ambitos: {

	tabla_global = crear_tabla(TAM_MAX_TABLA);
	tabla_local = crear_tabla(TAM_MAX_TABLA);

	escribir_subseccion_data(fpasm);
	escribir_cabecera_bss(fpasm);
};

escrituraTS:{
  escribir_segmento_codigo(fpasm);
};

escritura_inicio_main:{
	escribir_inicio_main(fpasm);
};

cerrar_ambitos:{
	if(tabla_local){
		liberar_tabla(tabla_local);
	}
	liberar_tabla(tabla_global);
	escribir_fin(fpasm);
};

declaraciones: declaracion {
	fprintf(fpasm, ";R2:\t<declaraciones> ::= <declaracion> \n");
	fprintf(yyout, ";R2:\t<declaraciones> ::= <declaracion> \n");
};
	| declaracion declaraciones {
		fprintf(fpasm, ";R3:\t<declaraciones> ::= <declaracion> <declaraciones> \n");
		fprintf(yyout, ";R3:\t<declaraciones> ::= <declaracion> <declaraciones> \n");
	};

declaracion: clase identificadores TOK_PUNTOYCOMA {
	fprintf(fpasm, ";R4:\t<declaracion> ::= <clase> <identificadores> ; \n");
	fprintf(yyout, ";R4:\t<declaracion> ::= <clase> <identificadores> ; \n");
};

clase: clase_escalar {

		tamano_vector_actual = 1;
		clase_actual = ESCALAR;

		fprintf(fpasm, ";R5:\t<clase> ::= <clase_escalar> \n");
		fprintf(yyout, ";R5:\t<clase> ::= <clase_escalar> \n");
	}
	| clase_vector {

		clase_actual = VECTOR;
		fprintf(fpasm, ";R7:\t<clase> ::= <clase_vector> \n");
		fprintf(yyout, ";R7:\t<clase> ::= <clase_vector> \n");
	};

clase_escalar: tipo {
	fprintf(fpasm, ";R9:\t<clase_escalar> ::= <tipo> \n");
	fprintf(yyout, ";R9:\t<clase_escalar> ::= <tipo> \n");
};

tipo: TOK_INT {

    tipo_actual=ENTERO;

    fprintf(fpasm, ";R10:\t<tipo> ::= int \n");
		fprintf(yyout, ";R10:\t<tipo> ::= int \n");

  }
	|TOK_BOOLEAN {

    tipo_actual=BOOLEANO;
    fprintf(fpasm, ";R11:\t<tipo> ::= boolean \n");
		fprintf(yyout, ";R11:\t<tipo> ::= boolean \n");
  };

/* ANDARSE CON OJO CON CLASE VECTOR */


clase_vector: TOK_ARRAY tipo TOK_CORCHETEIZQUIERDO TOK_CONSTANTE_ENTERA TOK_CORCHETEDERECHO {

    tamano_vector_actual = $4.valor_entero;

		if(tamano_vector_actual < 1 || tamano_vector_actual > MAX_TAM_VECTOR){
			printf("****Error semantico en lin %d: El tamanio del vector <%s> excede los limites permitidos (1,64).\n",linea, nombre_vector_actual);
			return 0;
		}

    fprintf(yyout, ";R15:\t<clase_vector> ::= array <tipo> [ <constante_entera> ] \n");
		fprintf(fpasm, ";R15:\t<clase_vector> ::= array <tipo> [ <constante_entera> ] \n");
  };


/* ANDARSE CON OJO CON CLASE VECTOR */


identificadores: identificador {
	fprintf(fpasm, ";R18:\t<identificadores> ::= <identificador> \n");
	fprintf(yyout, ";R18:\t<identificadores> ::= <identificador> \n");
}
	| identificador TOK_COMA identificadores {
		fprintf(fpasm, ";R19:\t<identificadores> ::= <identificador> , <identificadores> \n");
		fprintf(yyout, ";R19:\t<identificadores> ::= <identificador> , <identificadores> \n");
	};

funciones: funcion funciones {
	fprintf(fpasm, ";R20:\t<funciones> ::= <funcion> <funciones> \n");
	fprintf(yyout, ";R20:\t<funciones> ::= <funcion> <funciones> \n");
}
	| {
		fprintf(fpasm, ";R21:\t<funciones> ::= \n");
		fprintf(yyout, ";R21:\t<funciones> ::= \n");
};

funcion: fn_declaracion sentencias TOK_LLAVEDERECHA {

  ambito_actual=GLOBAL;
  valor = busqueda_global($1.lexema, tabla_global);
  valor->adicional1 = n_parametros_actual;

  if(fn_retorno==0){
    printf("****Error semantico en lin %d: Funcion %s sin sentencia de retorno\n", linea, $1.lexema);
    return 0;
  }
  fprintf(fpasm, ";R22:\t<funcion> ::= function <tipo> <identificador> ( <parametros_funcion> ) { <declaraciones_funcion> <sentencias> } \n");
	fprintf(yyout, ";R22:\t<funcion> ::= function <tipo> <identificador> ( <parametros_funcion> ) { <declaraciones_funcion> <sentencias> } \n");
  };

fn_declaracion: fn_name TOK_PARENTESISIZQUIERDO parametros_funcion TOK_PARENTESISDERECHO TOK_LLAVEIZQUIERDA declaraciones_funcion{

  valor = busqueda_global($1.lexema, tabla_global);
  valor->adicional1=n_parametros_actual;
  strcpy($$.lexema, $1.lexema);

	/* llamamos a declararFuncion (GC) */
	declararFuncion(fpasm, $1.lexema, n_variables_locales_actual);

 };

fn_name: TOK_FUNCTION tipo TOK_IDENTIFICADOR {

  valor = busqueda_global($3.lexema, tabla_global);

  if(valor){
    printf("****Error semantico en lin %d: Declaracion dupliacada", linea);
    return 0;
  }


  if(declarar_funcion(tabla_global, tabla_local, $3.lexema, FUNCION, tipo_actual, ESCALAR, adicional1, 0)==OK){
    ambito_actual=LOCAL;
  }

  adicional1++;

  n_variables_locales_actual = 0;
  pos_variable_local_actual = 1;
  n_parametros_actual = 0;
  pos_parametros_actual = 0;
  fn_retorno = 0;

  strcpy($$.lexema, $3.lexema);
  es_funcion=1;

  tipo_retorno=tipo_actual;

  strcpy(nombre_funcion_actual, $3.lexema);
};


parametros_funcion: parametro_funcion resto_parametros_funcion {
fprintf(fpasm, ";R23:\t<parametros_funcion> ::= <parametro_funcion> <resto_parametros_funcion> \n");
fprintf(yyout, ";R23:\t<parametros_funcion> ::= <parametro_funcion> <resto_parametros_funcion> \n");
}
	| {
		fprintf(yyout, ";R24:\t<parametros_funcion> ::= \n");
		fprintf(fpasm, ";R24:\t<parametros_funcion> ::= \n");
	};

resto_parametros_funcion: TOK_PUNTOYCOMA parametro_funcion resto_parametros_funcion {
	fprintf(fpasm, ";R25:\t<resto_parametros_funcion> ::= ; <parametro_funcion> <resto_parametros_funcion> \n");
	fprintf(yyout, ";R25:\t<resto_parametros_funcion> ::= ; <parametro_funcion> <resto_parametros_funcion> \n");
}
	| {
		fprintf(fpasm, ";R26:\t<resto_parametros_funcion> ::= \n");
		fprintf(yyout, ";R26:\t<resto_parametros_funcion> ::= \n");
	};

parametro_funcion: tipo idpf {
fprintf(fpasm, ";R27:\t<parametro_funcion> ::= <tipo> <identificador> \n");
fprintf(yyout, ";R27:\t<parametro_funcion> ::= <tipo> <identificador> \n");
};

idpf: TOK_IDENTIFICADOR {
if (declarar_variable_local(tabla_local, $1.lexema,PARAMETRO, tipo_actual, ESCALAR, adicional1, pos_parametros_actual) == ERR) {
	printf("****Error semantico en lin %d: Declaracion dupliacada", linea);
	return 0;
}

  adicional1++;
  pos_parametros_actual++;
  n_parametros_actual++;
};

declaraciones_funcion: declaraciones {
	fprintf(fpasm, ";R28:\t<declaraciones_funcion> ::= <declaraciones> \n");
	fprintf(yyout, ";R28:\t<declaraciones_funcion> ::= <declaraciones> \n");
}
	| {
		fprintf(fpasm, ";R29:\t<declaraciones_funcion> ::= \n");
		fprintf(yyout, ";R29:\t<declaraciones_funcion> ::= \n");
};

sentencias: sentencia {
	fprintf(fpasm, ";R30:\t<sentencias> ::= <sentencia> \n");
	fprintf(yyout, ";R30:\t<sentencias> ::= <sentencia> \n");
}
	| sentencia sentencias {
		fprintf(fpasm, ";R31:\t<sentencias> ::= <sentencia> <sentencias> \n");
		fprintf(yyout, ";R31:\t<sentencias> ::= <sentencia> <sentencias> \n");
	};

sentencia: sentencia_simple TOK_PUNTOYCOMA {
	fprintf(fpasm, ";R32:\t<sentencia> ::= <sentencia_simple> ; \n");
	fprintf(yyout, ";R32:\t<sentencia> ::= <sentencia_simple> ; \n");
}
	| bloque {
		fprintf(fpasm, ";R33:\t<sentencia> ::= <bloque> \n");
		fprintf(yyout, ";R33:\t<sentencia> ::= <bloque> \n");
	};

sentencia_simple: asignacion {
	fprintf(fpasm, ";R34:\t<sentencia_simple> ::= <asignacion> \n");
	fprintf(yyout, ";R34:\t<sentencia_simple> ::= <asignacion> \n");
}
	| lectura {
		fprintf(fpasm, ";R35:\t<sentencia_simple> ::= <lectura> \n");
		fprintf(yyout, ";R35:\t<sentencia_simple> ::= <lectura> \n");
}
	| escritura {
		fprintf(fpasm, ";R36:\t<sentencia_simple> ::= <escritura> \n");
		fprintf(yyout, ";R36:\t<sentencia_simple> ::= <escritura> \n");
	}
	| retorno_funcion {
		fprintf(fpasm, ";R38:\t<sentencia_simple> ::= <retorno_funcion> \n");
		fprintf(yyout, ";R38:\t<sentencia_simple> ::= <retorno_funcion> \n");
	};

bloque: condicional {
	fprintf(fpasm, ";R40:\t<bloque> ::= <condicional> \n");
	fprintf(yyout, ";R40:\t<bloque> ::= <condicional> \n");
}
	| bucle {
		fprintf(fpasm, ";R41:\t<bloque> ::= <bucle> \n");
		fprintf(yyout, ";R41:\t<bloque> ::= <bucle> \n");
	};

asignacion: TOK_IDENTIFICADOR TOK_ASIGNACION exp {
  if (ambito_actual == GLOBAL) {
	valor = busqueda_global($1.lexema, tabla_global);
  }else {
	valor = busqueda_local($1.lexema, tabla_global,tabla_local);
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
	escribirParametro(fpasm, valor->adicional2, n_parametros_actual);
}
else if(valor->adicional2 == 0){
	asignar(fpasm, $1.lexema, $3.es_direccion);
}
else {
	escribirVariableLocal(fpasm, valor->adicional2);
}

  fprintf(fpasm, ";R43:\t<asignacion> ::= <identificador> = <exp> \n");
	fprintf(yyout, ";R43:\t<asignacion> ::= <identificador> = <exp> \n");
}
  | elemento_vector TOK_ASIGNACION exp {

  if($1.tipo != $3.tipo){
	printf("****Error semantico en lin %d: Asignacion no compatible\n", linea);
	return 0;
  }

  asignarVector(fpasm, $3.es_direccion);
  fprintf(fpasm, ";R44:\t<asignacion> ::= <elemento_vector> = <exp> \n");
	fprintf(yyout, ";R44:\t<asignacion> ::= <elemento_vector> = <exp> \n");
};

elemento_vector: TOK_IDENTIFICADOR TOK_CORCHETEIZQUIERDO exp TOK_CORCHETEDERECHO {
  if (ambito_actual == GLOBAL) {
	valor = busqueda_global($1.lexema, tabla_global);
  }else {
	valor = busqueda_local($1.lexema, tabla_global,tabla_local);
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

	escribir_elemento_vector(fpasm, $1.lexema, valor->adicional1, $3.es_direccion);
  fprintf(fpasm, ";R48:\t<elemento_vector> ::= <identificador> [ <exp> ] \n");
	fprintf(yyout, ";R48:\t<elemento_vector> ::= <identificador> [ <exp> ] \n");
};

condicional:  if_exp sentencias TOK_LLAVEDERECHA {

	ifthen_fin(fpasm, $1.etiqueta);

  fprintf(fpasm, ";R50:\t<condicional> ::= if ( <exp> ) { <sentencias> } \n");
	fprintf(yyout, ";R50:\t<condicional> ::= if ( <exp> ) { <sentencias> } \n");
}
  | if_exp_sentencias TOK_ELSE TOK_LLAVEIZQUIERDA sentencias TOK_LLAVEDERECHA {
	  ifthenelse_fin(fpasm, $1.etiqueta);
    fprintf(fpasm, ";R51:\t<condicional> ::= if ( <exp> ) { <sentencias> } else { <sentencias> } \n");
		fprintf(yyout, ";R51:\t<condicional> ::= if ( <exp> ) { <sentencias> } else { <sentencias> } \n");
  };

if_exp: TOK_IF TOK_PARENTESISIZQUIERDO exp TOK_PARENTESISDERECHO TOK_LLAVEIZQUIERDA {
  if($3.tipo != BOOLEANO){
    printf("****Error semantico en lin %d: Condicional con condicion de tipo int\n", linea);
    return 0;
  }
  $$.etiqueta = etiqueta ++;

	ifthen_inicio(fpasm, $3.es_direccion, $$.etiqueta);

};


if_exp_sentencias: if_exp sentencias TOK_LLAVEDERECHA {

  $$.etiqueta = $1.etiqueta;
	ifthenelse_fin_then(fpasm, $1.etiqueta);
};

bucle: while_exp sentencias TOK_LLAVEDERECHA {

	while_fin(fpasm, $1.etiqueta);
  fprintf(fpasm, ";R52:\t<bucle> ::= while ( <exp> ) { <sentencias> } \n");
	fprintf(yyout, ";R52:\t<bucle> ::= while ( <exp> ) { <sentencias> } \n");
};

while_exp: while exp TOK_PARENTESISDERECHO TOK_LLAVEIZQUIERDA {

  if($2.tipo != BOOLEANO){
    printf("****Error semantico en lin %d: Bucle con condicion de tipo int\n", linea);
    return 0;
  }
  $$.etiqueta = $1.etiqueta;

	while_exp_pila (fpasm, $2.es_direccion, $$.etiqueta);
};

while: TOK_WHILE TOK_PARENTESISIZQUIERDO {

  $$.etiqueta = etiqueta++;

	while_inicio(fpasm, $$.etiqueta);
};

lectura: TOK_SCANF TOK_IDENTIFICADOR {

  if(ambito_actual == GLOBAL){
    valor = busqueda_global($2.lexema, tabla_global);
  }else{
    valor = busqueda_local($2.lexema, tabla_global, tabla_local);
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
		leerParametro(fpasm, valor->tipo, n_parametros_actual, valor->adicional2);
	} else if(valor->adicional2 == 0){
		leer(fpasm, valor->lexema, valor->tipo);
	} else{
		leerLocal(fpasm, valor->tipo, valor->adicional2);
	}

  fprintf(fpasm, ";R54:\t<lectura> ::= scanf <identificador> \n");
	fprintf(yyout, ";R54:\t<lectura> ::= scanf <identificador> \n");
};

escritura: TOK_PRINTF exp {

  escribir(fpasm, $2.es_direccion, $2.tipo);
  fprintf(fpasm, ";R56:\t<escritura> ::= printf <exp> \n");
	fprintf(yyout, ";R56:\t<escritura> ::= printf <exp> \n");
};

retorno_funcion: TOK_RETURN exp {

  if((($2.es_direccion != 1) && ($2.es_direccion != 0)) || $2.tipo != tipo_retorno){
  	printf("****Error semantico en lin %d: Sentencia de retorno fuera de una función.\n", linea);
  	return 0;
  }

  retornarFuncion(fpasm, $2.es_direccion);
  fn_retorno++;
  fprintf(fpasm, ";R61:\t<retorno_funcion> ::= return <exp> \n");
	fprintf(yyout, ";R61:\t<retorno_funcion> ::= return <exp> \n");
};


exp: exp TOK_MAS exp {

		if($1.tipo !=  ENTERO || $3.tipo !=  ENTERO){
	    printf("****Error semantico en lin %d: Operacion aritmetica con operandos boolean.\n", linea);
	    return 0;
	  }
	  $$.tipo = ENTERO;
	  $$.es_direccion = 0;

	  sumar(fpasm, $1.es_direccion, $3.es_direccion);

		fprintf(fpasm, ";R72:\t<exp> ::= <exp> + <exp> \n");
		fprintf(yyout, ";R72:\t<exp> ::= <exp> + <exp> \n");
	}
	| exp TOK_MENOS exp {

		if($1.tipo !=  ENTERO || $3.tipo !=  ENTERO){
	    printf("****Error semantico en lin %d: Operacion aritmetica con operandos boolean.\n", linea);
	    return 0;
	  }
	  $$.tipo = ENTERO;
	  $$.es_direccion = 0;

	  restar(fpasm, $1.es_direccion, $3.es_direccion);

		fprintf(fpasm, ";R73:\t<exp> ::= <exp> - <exp> \n");
		fprintf(yyout, ";R73:\t<exp> ::= <exp> - <exp> \n");
	}
	| exp TOK_DIVISION exp {

		if($1.tipo !=  ENTERO || $3.tipo !=  ENTERO){
	    printf("****Error semantico en lin %d: Operacion aritmetica con operandos boolean.\n", linea);
	    return 0;
	  }
	  $$.tipo = ENTERO;
	  $$.es_direccion = 0;

	  dividir(fpasm, $1.es_direccion, $3.es_direccion);

		fprintf(fpasm, ";R74:\t<exp> ::= <exp> / <exp> \n");
		fprintf(yyout, ";R74:\t<exp> ::= <exp> / <exp> \n");
	}
	| exp TOK_ASTERISCO exp {

		if($1.tipo !=  ENTERO || $3.tipo !=  ENTERO){
	    printf("****Error semantico en lin %d: Operacion aritmetica con operandos boolean.\n", linea);
	    return 0;
	  }
	  $$.tipo = ENTERO;
	  $$.es_direccion = 0;

	  multiplicar(fpasm, $1.es_direccion, $3.es_direccion);

		fprintf(fpasm, ";R75:\t<exp> ::= <exp> * <exp> \n");
		fprintf(yyout, ";R75:\t<exp> ::= <exp> * <exp> \n");
	}
	| TOK_MENOS exp %prec NEG {

		if($2.tipo !=  ENTERO){
	    printf("****Error semantico en lin %d: Operacion aritmetica con operandos boolean.\n", linea);
	    return 0;
	  }
	  $$.tipo = ENTERO;
	  $$.es_direccion = 0;

	  cambiar_signo(fpasm, $2.es_direccion);

		fprintf(fpasm, ";R76:\t<exp> ::= - <exp> \n");
		fprintf(yyout, ";R76:\t<exp> ::= - <exp> \n");
	}
	| exp TOK_AND exp {

		if($1.tipo !=  BOOLEANO || $3.tipo !=  BOOLEANO){
	    printf("****Error semantico en lin %d: Operacion logica con operandos int.\n", linea);
	    return 0;
	  }
	  $$.tipo = BOOLEANO;
	  $$.es_direccion = 0;

	  y(fpasm, $1.es_direccion, $3.es_direccion);

		fprintf(fpasm, ";R77:\t<exp> ::= <exp> && <exp> \n");
		fprintf(yyout, ";R77:\t<exp> ::= <exp> && <exp> \n");
		}
	| exp TOK_OR exp {

		if($1.tipo !=  BOOLEANO || $3.tipo !=  BOOLEANO){
		 printf("****Error semantico en lin %d: Operacion logica con operandos int.\n", linea);
		 return 0;
	 	}
		 $$.tipo = BOOLEANO;
		 $$.es_direccion = 0;

		 o(fpasm, $1.es_direccion,$3.es_direccion);

		fprintf(fpasm, ";R78:\t<exp> ::= <exp> || <exp> \n");
		fprintf(yyout, ";R78:\t<exp> ::= <exp> || <exp> \n");
	}
	| TOK_NOT exp {

		if($2.tipo !=  BOOLEANO){
	    printf("****Error semantico en lin %d: Operacion logica con operandos int.\n", linea);
	    return 0;
	  }
	  $$.tipo = BOOLEANO;
	  $$.es_direccion = 0;

	  no(fpasm, $2.es_direccion, etiqueta);
	  etiqueta++;

		fprintf(fpasm, ";R79:\t<exp> ::= ! <exp> \n");
		fprintf(yyout, ";R79:\t<exp> ::= ! <exp> \n");
	}
	| TOK_IDENTIFICADOR {
	      /*Se comprueba que el identificador no exista en el ambito actual. Si existiera, se genera un
	      mensaje de error semantico y se termina el proceso de compilacion con error.*/
	    if(ambito_actual == GLOBAL){
	      valor = busqueda_global($1.lexema, tabla_global);
	    }else{
	      valor = busqueda_local($1.lexema, tabla_global, tabla_local);
	    }
	    if(valor == NULL){
	      printf("****Error semantico en lin %d: Acceso a variable no declarada (%s).\n", linea, $1.lexema);
	      return 0;
	    }

	    if(valor->clase == VECTOR || valor->categoria == FUNCION){
	    	printf("****Error semantico en lin %d: Asignacion incompatible\n", linea);
	    	return 0;
	    }
	    $$.tipo = valor->tipo;
	    $$.es_direccion=1;

		/*GENERACION DE CODIGO*/
		if(valor->categoria == PARAMETRO){
			$$.es_direccion = 0;
			/* TODO puede que haya que revisar escribirParametro */
			escribirParametro(fpasm, valor->adicional2, n_parametros_actual);
		}else if(valor->adicional2 == 0){
			if(en_exp_list == 0){/*si no es una direccion en la lista de parametros d la fn en_exp_list = 1*/
				$$.es_direccion = 1;
				/*TODO: escribir operando a lo mejor deber revisarse*/
				/* TODO: a lo mejor está al reves el 0 y el 1 */
				escribir_operando(fpasm, $1.lexema, 0);
			}else{
				$$.es_direccion = 0;
				escribir_operando(fpasm, $1.lexema, 1);
			}
		}else{
			$$.es_direccion = 0;
			/* puede que haya que revisar escribirVariableLocal */
			escribirVariableLocal(fpasm, valor->adicional2);
		}

		fprintf(fpasm, ";R80:\t<exp> ::= <identificador> \n");
		fprintf(yyout, ";R80:\t<exp> ::= <identificador> \n");
	}
	| constante {

		$$.tipo = $1.tipo;
	  $$.es_direccion = $1.es_direccion;

		fprintf(fpasm, ";R81:\t<exp> ::= <constante> \n");
		fprintf(yyout, ";R81:\t<exp> ::= <constante> \n");
	}
	| TOK_PARENTESISIZQUIERDO exp TOK_PARENTESISDERECHO {

		$$.tipo = $2.tipo;
	  $$.es_direccion = $2.es_direccion;

		fprintf(fpasm, ";R82:\t<exp> ::= ( <exp> ) \n");
		fprintf(yyout, ";R82:\t<exp> ::= ( <exp> ) \n");
	}
	| TOK_PARENTESISIZQUIERDO comparacion TOK_PARENTESISDERECHO {

		$$.tipo = $2.tipo;
	  $$.es_direccion = $2.es_direccion;

		fprintf(fpasm, ";R83:\t<exp> ::= ( <comparacion> ) \n");
		fprintf(yyout, ";R83:\t<exp> ::= ( <comparacion> ) \n");
	}
	| elemento_vector {

		$$.tipo = $1.tipo;

		if(en_exp_list == 0){
			$$.es_direccion = $1.es_direccion;
		}else{
			$$.es_direccion = 0;
		}

		fprintf(fpasm, ";R85:\t<exp> ::= <elemento_vector> \n");
		fprintf(yyout, ";R85:\t<exp> ::= <elemento_vector> \n");
	}
	| idf_llamada_funcion TOK_PARENTESISIZQUIERDO lista_expresiones TOK_PARENTESISDERECHO {

		valor = busqueda_global($1.lexema, tabla_global);
		if (valor == NULL) {
			printf("****Error semantico en lin %d: Acceso a variable no declarada (%s)\n", linea, $1.lexema);
			return 0;
		}
		if(valor->adicional1 != n_parametros_llamada_actual){
			printf("****Error semantico en lin %d: Numero incorrecto de parametros en llamada a funcion (%s)\n", linea, $1.lexema);
			return 0;
		}

	llamarFuncion(fpasm, $1.lexema, n_parametros_llamada_actual);

	en_exp_list = 0;
	$$.tipo = valor->tipo;
	$$.es_direccion = 0;

	fprintf(fpasm, ";R88:\t<exp> ::= <identificador> ( <lista_expresiones> ) \n");
	fprintf(yyout, ";R88:\t<exp> ::= <identificador> ( <lista_expresiones> ) \n");
};

idf_llamada_funcion: TOK_IDENTIFICADOR {
	valor = busqueda_global($1.lexema, tabla_global);
	if (valor == NULL) {
		printf("****Error semantico en lin %d: Acceso a variable no declarada (%s)\n", linea, $1.lexema);
		return 0;
	}
	if(valor->categoria != FUNCION){
		printf("****Error semantico en lin %d: Asignacion incompatible\n", linea);
		return 0;
	}
	/*no podemos pasar una funcion por parametro a otra funcion*/
	if(en_exp_list == 1){
		printf("****Error semantico en lin %d: No esta permitido el uso de llamadas a funciones como parametros de otras funciones\n", linea);
		return 0;
	}
	n_parametros_llamada_actual = 0;
	en_exp_list = 1;
	strcpy($$.lexema, $1.lexema);
};



lista_expresiones: exp resto_lista_expresiones {

	n_parametros_llamada_actual++;

	fprintf(fpasm, ";R89:\t<lista_expresiones> ::= <exp> <resto_lista_expresiones> \n");
	fprintf(yyout, ";R89:\t<lista_expresiones> ::= <exp> <resto_lista_expresiones> \n");
	}
	| {
		fprintf(fpasm, ";R90:\t<lista_expresiones> ::=  \n");
		fprintf(yyout, ";R90:\t<lista_expresiones> ::=  \n");
};

resto_lista_expresiones: TOK_COMA exp resto_lista_expresiones {

	n_parametros_llamada_actual++;

	fprintf(fpasm, ";R91\t<resto_lista_expresiones> ::= , <exp> <resto_lista_expresiones> \n");
	fprintf(yyout, ";R91\t<resto_lista_expresiones> ::= , <exp> <resto_lista_expresiones> \n");
	}
	| {
		fprintf(fpasm, ";R92:\t<resto_lista_expresiones> ::=  \n");
		fprintf(yyout, ";R92:\t<resto_lista_expresiones> ::=  \n");
};


comparacion: exp TOK_IGUAL exp {

	if($1.tipo !=  ENTERO || $3.tipo !=  ENTERO){
      printf("****Error semantico en lin %d: Comparacion con operandos boolean.\n", linea);
      return 0;
    }
    $$.tipo = BOOLEANO;
    $$.es_direccion = 0;

    igual(fpasm, $1.es_direccion, $3.es_direccion, etiqueta);
    etiqueta++;

	fprintf(fpasm, ";R93:\t<comparacion> ::= <exp> == <exp> \n");
	fprintf(yyout, ";R93:\t<comparacion> ::= <exp> == <exp> \n");
	}
	| exp TOK_DISTINTO exp {

		if($1.tipo !=  ENTERO || $3.tipo !=  ENTERO){
      printf("****Error semantico en lin %d: Comparacion con operandos boolean.\n", linea);
      return 0;
    }
    $$.tipo = BOOLEANO;
    $$.es_direccion = 0;

    distinto(fpasm, $1.es_direccion, $3.es_direccion, etiqueta);
    etiqueta++;

		fprintf(fpasm, ";R94:\t<comparacion> ::= <exp> != <exp> \n");
		fprintf(yyout, ";R94:\t<comparacion> ::= <exp> != <exp> \n");
	}
	| exp TOK_MENORIGUAL exp {

		if($1.tipo !=  ENTERO || $3.tipo !=  ENTERO){
      printf("****Error semantico en lin %d: Comparacion con operandos boolean.\n", linea);
      return 0;
    }
    $$.tipo = BOOLEANO;
    $$.es_direccion = 0;

    menor_igual(fpasm, $1.es_direccion, $3.es_direccion, etiqueta);
    etiqueta++;

		fprintf(fpasm, ";R95:\t<comparacion> ::= <exp> <= <exp> \n");
		fprintf(yyout, ";R95:\t<comparacion> ::= <exp> <= <exp> \n");
	}
	| exp TOK_MAYORIGUAL exp {

		if($1.tipo !=  ENTERO || $3.tipo !=  ENTERO){
      printf("****Error semantico en lin %d: Comparacion con operandos boolean.\n", linea);
      return 0;
    }
    $$.tipo = BOOLEANO;
    $$.es_direccion = 0;

    mayor_igual(fpasm, $1.es_direccion, $3.es_direccion, etiqueta);
    etiqueta++;

		fprintf(fpasm, ";R96:\t<comparacion> ::= <exp> >= <exp> \n");
		fprintf(yyout, ";R96:\t<comparacion> ::= <exp> >= <exp> \n");
	}
	| exp TOK_MENOR exp {

		if($1.tipo !=  ENTERO || $3.tipo !=  ENTERO){
      printf("****Error semantico en lin %d: Comparacion con operandos boolean.\n", linea);
      return 0;
    }
    $$.tipo = BOOLEANO;
    $$.es_direccion = 0;

    menor(fpasm, $1.es_direccion, $3.es_direccion, etiqueta);
    etiqueta++;

		fprintf(fpasm, ";R97:\t<comparacion> ::= <exp> < <exp> \n");
		fprintf(yyout, ";R97:\t<comparacion> ::= <exp> < <exp> \n");
	}
	| exp TOK_MAYOR exp {

		if($1.tipo !=  ENTERO || $3.tipo !=  ENTERO){
      printf("****Error semantico en lin %d: Comparacion con operandos boolean.\n", linea);
      return 0;
    }
    $$.tipo = BOOLEANO;
    $$.es_direccion = 0;

    mayor(fpasm, $1.es_direccion, $3.es_direccion, etiqueta);
    etiqueta++;

		fprintf(fpasm, ";R98:\t<comparacion> ::= <exp> > <exp> \n");
		fprintf(yyout, ";R98:\t<comparacion> ::= <exp> > <exp> \n");
	}

constante: constante_logica {

	$$.tipo = $1.tipo;
  $$.es_direccion = $1.es_direccion;

	fprintf(fpasm, ";R99:\t<constante> ::= <constante_logica> \n");
	fprintf(yyout, ";R99:\t<constante> ::= <constante_logica> \n");
	}
	| constante_entera {

		$$.tipo = $1.tipo;
  	$$.es_direccion = $1.es_direccion;

		fprintf(fpasm, ";R100:\t<constante> ::= <constante_entera> \n");
		fprintf(yyout, ";R100:\t<constante> ::= <constante_entera> \n");
	}

constante_logica: TOK_TRUE {

		$$.tipo = BOOLEANO;
    $$.es_direccion = 0;

    /* generacion de codigo */
    fprintf(fpasm, "; escribir_operando:\n");
    fprintf(fpasm, "\tpush dword 1\n");

	fprintf(yyout, ";R102:\t<constante_logica> ::= true \n");
	fprintf(fpasm, ";R102:\t<constante_logica> ::= true \n");

	}
	| TOK_FALSE {

		$$.tipo = BOOLEANO;
    $$.es_direccion = 0;

    /* generacion de codigo */
    fprintf(fpasm, "; escribir_operando:\n");
    fprintf(fpasm, "\tpush dword 0\n");


		fprintf(fpasm, ";R103:\t<constante_logica> ::= false \n");
		fprintf(yyout, ";R103:\t<constante_logica> ::= false \n");
	};

/* Hemos implementado constante entera de esta forma, ya que es mucho mas sencillo
que desarrollar todas las reglas que nos viene en la gramatica de alfa propuesta */
constante_entera: TOK_CONSTANTE_ENTERA {

		$$.tipo = ENTERO;
    $$.es_direccion = 0;

    /* generacion de codigo */
    fprintf(fpasm, "; escribir_operando:\n");
    fprintf(fpasm, "\tpush dword %d\n", $1.valor_entero);

	fprintf(fpasm, ";R104:\t<constante_entera> ::= TOK_CONSTANTE_ENTERA \n");
	fprintf(yyout, ";R104:\t<constante_entera> ::= TOK_CONSTANTE_ENTERA \n");

};

/* Hemos implementado identificador de esta forma, ya que es mucho mas sencillo
que desarrollar todas las reglas que nos viene en la gramatica de alfa propuesta */
identificador: TOK_IDENTIFICADOR {

		if (ambito_actual == GLOBAL){
	 		declarar = declarar_variable_global(tabla_global, $1.lexema, categoria_actual, tipo_actual, clase_actual, 0, 0);
		}else{
			declarar = declarar_variable_local(tabla_local, $1.lexema, categoria_actual, tipo_actual, clase_actual, 0, 0);
		}
		if(declarar == ERR){
			printf("****Error semantico en lin %d: Declaracion duplicada.\n", linea);
			return 0;
		}else{
			adicional1 ++;
		}
		if (ambito_actual == GLOBAL){
			valor = busqueda_global($1.lexema, tabla_global);
		}else{
			valor = busqueda_local($1.lexema, tabla_global, tabla_local);
		}
		if (!valor) {
			printf("****Error semantico en lin %d: IAcceso a variable no declarada (%s)\n", linea, $1.lexema);
			return 0;
		}

		/* generacion de codigo */

		if(es_funcion == 0){
			declarar_variable(fpasm, $1.lexema, clase_actual, tamano_vector_actual);
			valor->clase = clase_actual;
			valor->tipo = tipo_actual;
			/*vectores*/
			if(valor->clase == VECTOR){
				valor->adicional1 = tamano_vector_actual;
				strcpy(nombre_vector_actual, $1.lexema);
			}
		}else{
			if(clase_actual == VECTOR){
				printf("****Error semantico en lin %d: Variable local de tipo no escalar.\n", linea);
				return 0;
			}

			valor->tipo = tipo_actual;
			valor->clase = clase_actual;
			valor->adicional2 = pos_variable_local_actual;
			n_variables_locales_actual++;
			pos_variable_local_actual++;
	}

	fprintf(fpasm, ";R108:\t<identificador> ::= TOK_IDENTIFICADOR \n");
	fprintf(yyout, ";R108:\t<identificador> ::= TOK_IDENTIFICADOR \n");
};

%%

void yyerror(char* s){
	if(error == 0){
		fprintf(stdout,"**** Error sintáctico en [lin %d, col %d]\n",linea, (columna-yyleng));
	}
	error = 0;
}
