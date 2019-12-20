%{
#include <stdio.h>
#include <string.h>

#include "alfa.h"
#include "tablaHash.h"
#include "tablaSimbolos.h"
#include "generacion.h"
#include "y.tab.h"

INFO_SIMBOLO* dato, *dato1, *dato2;

extern FILE * yyout;
extern FILE * fpasm;
extern int yylex();
extern int yyleng;
extern int linea, columna, error;
void yyerror(char* s);

TABLA_HASH * tablaGlobal = NULL;
TABLA_HASH * tablaLocal = NULL;

/*GENERAL (identificadores)*/
AMBITO ambito_actual;
CLASE clase_actual;
TIPO tipo_actual;
CATEGORIA categoria_actual;


/*	- num parametros si funcion
 	- valor si escalar
  	- longitud si vector
*/
int adic1; /*desc_id*/
int declarar;
int en_explist; /*lista de parametros de la funcion*/
int tipo_return;

/*VECTORES*/
int tamanio_vector_actual = 1;
char nombre_vector_actual[MAX_LONG_ID]; /*identificador del vector*/


/*FUNCIONES*/
int num_variables_locales_actual; /*Numero de variables locales*/
int pos_variable_local_actual; /*Posicion de la variable local*/
int num_parametros_actual; /*Num parametros*/
int num_parametros_llamada_actual;/*Numero de parametros que se llama*/
int pos_parametros_actual; /*Posicion del parametro*/
int pos_parametros_llamada_actual;/*Posicion de la llamada del parametro*/
int fn_return;
int es_funcion = 0; /*Flag que nos dice si estamos dentro de una función o no*/
int etiqueta = 1;
char nombre_funcion_actual[MAX_LONG_ID]; /*identificador de la funcion*/
TIPO tipo_retorno_funcion; /*Tipo de retorno de la funcion (entero/booleano)*/

%}
%union {
	tipo_atributos atributos;
}
%token TOK_TRUE
%token TOK_FALSE

%token TOK_MAIN
%token TOK_INT
%token TOK_BOOLEAN
%token TOK_ARRAY
%token TOK_FUNCTION
%token TOK_IF
%token TOK_ELSE
%token TOK_WHILE
%token TOK_SCANF
%token TOK_PRINTF
%token TOK_RETURN
%token TOK_PUNTOYCOMA
%token TOK_COMA
%token TOK_PARENTESISIZQUIERDO
%token TOK_PARENTESISDERECHO
%token TOK_CORCHETEIZQUIERDO
%token TOK_CORCHETEDERECHO
%token TOK_LLAVEIZQUIERDA
%token TOK_LLAVEDERECHA
%token TOK_ASIGNACION
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
%token TOK_ERROR

%token <atributos> TOK_IDENTIFICADOR
%token <atributos> TOK_CONSTANTE_ENTERA

%type <atributos> asignacion
%type <atributos> elemento_vector
%type <atributos> lectura
%type <atributos> identificador
%type <atributos> constante_entera
%type <atributos> constante_logica
%type <atributos> constante
%type <atributos> exp
%type <atributos> comparacion
%type <atributos> if_exp

%type <atributos> condicional
%type <atributos> if_exp_sentencias
%type <atributos> bucle
%type <atributos> while
%type <atributos> while_exp

%type <atributos> funcion
%type <atributos> fn_declaracion
%type <atributos> fn_name
%type <atributos> idf_llamada_funcion



%left TOK_MAS TOK_MENOS TOK_OR
%left TOK_ASTERISCO TOK_DIVISION TOK_AND
%right NEGATIVO TOK_NOT
%start programa



%%
programa: abrir_ambitos TOK_MAIN TOK_LLAVEIZQUIERDA declaraciones escrituraTS funciones escritura_inicio_main sentencias TOK_LLAVEDERECHA cerrar_ambitos {fprintf(yyout, ";R1:\t<programa> ::= main { <declaraciones> <funciones> <sentencias> } \n");};

abrir_ambitos: {
	tablaGlobal = crear_tabla(TAM_TABLA_MAX);
	tablaLocal = crear_tabla(TAM_TABLA_MAX);
	escribir_subseccion_data(fpasm);
	escribir_cabecera_bss(fpasm);
};

escrituraTS:{
  escribir_segmento_codigo(fpasm);};

escritura_inicio_main:{escribir_inicio_main(fpasm);};

cerrar_ambitos:{
	if(tablaLocal){
		liberar_tabla(tablaLocal);
	}
	liberar_tabla(tablaGlobal);
	escribir_fin(fpasm);
};

declaraciones: declaracion {fprintf(yyout, ";R2:\t<declaraciones> ::= <declaracion>\n");}
	|declaracion declaraciones {fprintf(yyout, ";R3:\t<declaraciones> ::= <declaracion> <declaraciones> \n");};

declaracion: clase identificadores TOK_PUNTOYCOMA {fprintf(yyout, ";R4:\t<declaracion> ::= <clase> <identificadores> ; \n");};

clase: clase_escalar {
		tamanio_vector_actual = 1;
		clase_actual = ESCALAR;
		fprintf(yyout, ";R5:\t<clase> ::= <clase_escalar> \n");
	}
	|clase_vector {
		clase_actual = VECTOR;
		fprintf(yyout, ";R7:\t<clase> ::= <clase_vector> \n");
	};

clase_escalar: tipo {fprintf(yyout, ";R9:\t<clase_escalar> ::= <tipo> \n");};

tipo: TOK_INT {
		tipo_actual = ENTERO;
		fprintf(yyout, ";R10:\t<tipo> ::= int \n");
	}
	|TOK_BOOLEAN {
		tipo_actual = BOOLEANO;
		fprintf(yyout, ";R11:\t<tipo> ::= boolean \n");
	};

clase_vector: TOK_ARRAY tipo TOK_CORCHETEIZQUIERDO TOK_CONSTANTE_ENTERA TOK_CORCHETEDERECHO {
		tamanio_vector_actual = $4.valor_entero;
		if(tamanio_vector_actual < 1 || tamanio_vector_actual > MAX_TAMANIO_VECTOR){
			printf("****Error semantico en lin %d: El tamanio del vector <%s> excede los limites permitidos (1,64).\n",linea, nombre_vector_actual);
			return 0;
		}
		fprintf(yyout, ";R15:\t<clase_vector> ::= array <tipo> [ <constante_entera> ] \n");
	};

identificadores: identificador {fprintf(yyout, ";R18:\t<identificadores> ::= <identificador>\n");}
	|identificador TOK_COMA identificadores {fprintf(yyout, ";R19:\t<identificadores> ::= <identificador> , <identificadores>\n");};

funciones: funcion funciones {fprintf(yyout, ";R20:\t<funciones> ::= <funcion> <funciones> \n");}
	| {fprintf(yyout, ";R21:\t<funciones> ::= \n");};


funcion: fn_declaracion sentencias TOK_LLAVEDERECHA {
  ambito_actual = GLOBAL;
  dato = busquedaGlobal($1.lexema, tablaGlobal);
  dato->adicional1 = num_parametros_actual;

  if(fn_return == 0){
    printf("****Error semantico en lin %d: Funcion %s sin sentencia de retorno\n", linea, $1.lexema);
    return 0;
  }
		fprintf(yyout, ";R22:\t<funcion> ::= function <tipo> <identificador> ( <parametros_funcion> ) { <declaraciones_funcion> <sentencias> } \n");
	};
fn_declaracion: fn_name TOK_PARENTESISIZQUIERDO parametros_funcion TOK_PARENTESISDERECHO TOK_LLAVEIZQUIERDA declaraciones_funcion
{

 dato = busquedaGlobal($1.lexema, tablaGlobal);
 dato->adicional1 = num_parametros_actual;
 strcpy($$.lexema,$1.lexema);


 /*Generacion de codigo */

 fprintf(fpasm, "\n_%s:\n", $1.lexema);
 fprintf(fpasm, "\tpush ebp\n");
 fprintf(fpasm, "\tmov ebp, esp\n");
 fprintf(fpasm, "\tsub esp, 4*%d\n", num_variables_locales_actual);


};

fn_name: TOK_FUNCTION tipo TOK_IDENTIFICADOR {

  dato = busquedaGlobal($3.lexema, tablaGlobal);

  if(dato){
    printf("****Error semantico en lin %d: Declaracion dupliacada", linea);
    return 0;
  }
  if(DeclararFuncion(tablaGlobal, tablaLocal,$3.lexema, FUNCION, tipo_actual, ESCALAR, adic1, 0)==OK){
	ambito_actual = LOCAL;
  }
   /*el ultimo parametro es el numero de variables locales dentro de la funcion*/
   adic1++;

   num_variables_locales_actual = 0;
   pos_variable_local_actual = 1;
   num_parametros_actual = 0;
   pos_parametros_actual = 0;

   fn_return = 0;

   strcpy($$.lexema, $3.lexema);
   es_funcion = 1;

   tipo_return = tipo_actual;

   strcpy(nombre_funcion_actual, $3.lexema);


};
parametros_funcion: parametro_funcion resto_parametros_funcion {
fprintf(yyout, ";R23:\t<parametros_funcion> ::= <parametro_funcion> <resto_parametros_funcion> \n");}
	| {fprintf(yyout, ";R24:\t<parametros_funcion> ::= \n");};

resto_parametros_funcion: TOK_PUNTOYCOMA parametro_funcion resto_parametros_funcion {fprintf(yyout, ";R25:\t<resto_parametros_funcion> ::= ; <parametro_funcion> <resto_parametros_funcion>\n");}
	| {fprintf(yyout, ";R26:\t<resto_parametros_funcion> ::= \n");};

parametro_funcion: tipo idpf {
/*insertar simbolo en local
actualixar numero parametros
actualizar posicion variable local (tabla)*/
/*EL RESULTADO DE LA FUNCION SE DEJA EN EAX*/
fprintf(yyout, ";R27:\t<parametro_funcion> ::= <tipo> <identificador> \n");};

idpf: TOK_IDENTIFICADOR {
if (DeclararVariableLocal(tablaLocal, $1.lexema,PARAMETRO, tipo_actual, ESCALAR, adic1, pos_parametros_actual) == ERR) {
	printf("****Error semantico en lin %d: Declaracion dupliacada", linea);
	return 0;
}

  adic1++;/*aumentamos num_parametros*/
  pos_parametros_actual++;
  num_parametros_actual++;

};
declaraciones_funcion: declaraciones {fprintf(yyout, ";R28:\t<declaraciones_funcion> ::= <declaraciones> \n");}
  |  {fprintf(yyout, ";R29:\t<declaraciones_funcion> ::= \n");};

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
	dato = busquedaGlobal($1.lexema, tablaGlobal);
  }else {
	dato = busquedaLocal($1.lexema, tablaGlobal,tablaLocal);
  }
  if(dato == NULL){
	printf("****Error semantico en lin %d: Acceso a variable no declarada (%s)\n", linea, $1.lexema);
	return 0;
  }
  if(dato->tipo != $3.tipo || dato->clase == VECTOR || dato->categoria == FUNCION ){
	printf("****Error semantico en lin %d: Asignacion incompatible\n", linea);
	return 0;
  }

  /*GENERACION DE CODIGO*/

if(dato->categoria == PARAMETRO){
	asignar_parametro(fpasm, num_parametros_actual, dato->adicional2, $3.es_direccion);

}else if(dato->adicional2 == 0){ /*Es que no estamos en funcion*/

	asignar_ident(fpasm, $1.lexema, $3.es_direccion);
}else {
	asignar_local(fpasm, dato->adicional2, $3.es_direccion);
}
 // asignar(fpasm, $1.lexema, $3.es_direccion);

  fprintf(yyout, ";R43:\t<asignacion> ::= <identificador> = <exp> \n");}
  | elemento_vector TOK_ASIGNACION exp {

  if($1.tipo != $3.tipo){
	printf("****Error semantico en lin %d: Asignacion incompatible\n", linea);
	return 0;
  }

  /* generacion de codigo */

  asignar_vector(fpasm, $3.es_direccion);
  fprintf(yyout, ";R44:\t<asignacion> ::= <elemento_vector> = <exp> \n");};

elemento_vector: TOK_IDENTIFICADOR TOK_CORCHETEIZQUIERDO exp TOK_CORCHETEDERECHO {
  if (ambito_actual == GLOBAL) {
	dato = busquedaGlobal($1.lexema, tablaGlobal);
  }else {
	dato = busquedaLocal($1.lexema, tablaGlobal,tablaLocal);
  }
  if(dato == NULL){
	printf("****Error semantico en lin %d: Acceso a variable no declarada (%s)\n", linea, $1.lexema);
	return 0;
  }
  if(dato->clase != VECTOR){
	printf("****Error semantico en lin %d: Intento de indexacion de una variable que no es de tipo vector (%s)\n", linea, $1.lexema);
	return 0;
  }
  if($3.tipo != ENTERO){
	printf("****Error semantico en lin %d: El indice en una operacion de indexacion tiene que ser de tipo entero (%s)\n", linea, $1.lexema);
	return 0;
  }
  $$.es_direccion = 1;
  $$.tipo = dato->tipo;


  /* GENERACION DE CODIGO */
  control_errores_vector(fpasm, $1.lexema, $3.es_direccion , dato->adicional1);
  fprintf(yyout, ";R48:\t<elemento_vector> ::= <identificador> [ <exp> ] \n");};

condicional:  if_exp sentencias TOK_LLAVEDERECHA {

  fprintf(fpasm, "\nfin_si%d:\n", $1.etiqueta);
  fprintf(yyout, ";R50:\t<condicional> ::= if ( <exp> ) { <sentencias> } \n");}

  | if_exp_sentencias TOK_ELSE TOK_LLAVEIZQUIERDA sentencias TOK_LLAVEDERECHA {
    fprintf(fpasm, "\nfin_sino%d:\n", $1.etiqueta);
    fprintf(yyout, ";R51:\t<condicional> ::= if ( <exp> ) { <sentencias> } else { <sentencias> } \n");};

/*if_exp nuevo condicional*/
if_exp: TOK_IF TOK_PARENTESISIZQUIERDO exp TOK_PARENTESISDERECHO TOK_LLAVEIZQUIERDA {
  if($3.tipo != BOOLEANO){
    printf("****Error semantico en lin %d: Condicional con condicion de tipo int\n", linea);
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

bucle: while_exp sentencias TOK_LLAVEDERECHA {

  fprintf(fpasm, "\n\n\tjmp near inicio_while%d\n", $1.etiqueta);
  fprintf(fpasm, "\nfin_while%d:\n", $1.etiqueta);

  fprintf(yyout, ";R52:\t<bucle> ::= while ( <exp> ) { <sentencias> } \n");};

while_exp: while exp TOK_PARENTESISDERECHO TOK_LLAVEIZQUIERDA {

  if($2.tipo != BOOLEANO){
    printf("****Error semantico en lin %d: Bucle con condicion de tipo int\n", linea);
    return 0;
  }
  $$.etiqueta = $1.etiqueta;

  abrir_while(fpasm, $$.etiqueta, $2.es_direccion);};

while: TOK_WHILE TOK_PARENTESISIZQUIERDO {

  $$.etiqueta = etiqueta++;

  fprintf(fpasm,"\ninicio_while%d:\n", $$.etiqueta);};
lectura: TOK_SCANF TOK_IDENTIFICADOR {

  if(ambito_actual == GLOBAL){
    dato = busquedaGlobal($2.lexema, tablaGlobal);
  }else{
    dato = busquedaLocal($2.lexema, tablaGlobal, tablaLocal);
  }

  if(dato == NULL){
  		printf("****Error semantico en lin %d: Acceso a variable no declarada (%s).\n", linea, $2.lexema);
  		return 0;
  }

  /*Comprobaciones semanticas*/
  if(dato->categoria == FUNCION){
    printf("****Error semantico en lin %d: Asignacion incompatible.\n", linea);
    return 0;
  }
  if(dato->clase == VECTOR){
    printf("****Error semantico en lin %d: Asignacion incompatible.\n", linea);
    return 0;
  }
	/*GENERACION CODIGO*/
	if(dato->categoria == PARAMETRO){
		leer_parametro(fpasm, dato->tipo, num_parametros_actual, dato->adicional2);
	} else if(dato->adicional2 == 0){
		leer(fpasm, dato->lexema, dato->tipo);
	} else{
		leer_local(fpasm, dato->tipo, dato->adicional2);
	}

  fprintf(yyout, ";R54:\t<lectura> ::= scanf <identificador> \n");};

escritura: TOK_PRINTF exp {

  /*GENERACION DE CODIGO*/
  escribir(fpasm, $2.es_direccion, $2.tipo);

  fprintf(yyout, ";R56:\t<escritura> ::= printf <exp> \n");};

retorno_funcion: TOK_RETURN exp {

if((($2.es_direccion != 1) && ($2.es_direccion != 0)) || $2.tipo != tipo_return){
	printf("****Error semantico en lin %d: Sentencia de retorno fuera del cuerpo de una función.\n", linea);
	return 0;
}
/*GENERACION*/
retorno_funcion(fpasm, $2.es_direccion);
fn_return++;
fprintf(yyout, ";R61:\t<retorno_funcion> ::= return <exp> \n");};


exp: exp TOK_MAS exp {

	  if($1.tipo !=  ENTERO || $3.tipo !=  ENTERO){
	    printf("****Error semantico en lin %d: Operacion aritmetica con operandos boolean.\n", linea);
	    return 0;
	  }
	  $$.tipo = ENTERO;
	  $$.es_direccion = 0;

	  sumar(fpasm, $3.es_direccion, $1.es_direccion);

	  fprintf(yyout, ";R72:\t<exp> ::= <exp> + <exp> \n");}
  | exp TOK_MENOS exp {

	  if($1.tipo !=  ENTERO || $3.tipo !=  ENTERO){
	    printf("****Error semantico en lin %d: Operacion aritmetica con operandos boolean.\n", linea);
	    return 0;
	  }
	  $$.tipo = ENTERO;
	  $$.es_direccion = 0;

	  restar(fpasm, $3.es_direccion, $1.es_direccion);

	    fprintf(yyout, ";R73:\t<exp> ::= <exp> - <exp> \n");}
  | exp TOK_DIVISION exp {

	  if($1.tipo !=  ENTERO || $3.tipo !=  ENTERO){
	    printf("****Error semantico en lin %d: Operacion aritmetica con operandos boolean.\n", linea);
	    return 0;
	  }
	  $$.tipo = ENTERO;
	  $$.es_direccion = 0;

	  dividir(fpasm, $3.es_direccion, $1.es_direccion); /* Cambiada */

	    fprintf(yyout, ";R74:\t<exp> ::= <exp> / <exp> \n");}
  | exp TOK_ASTERISCO exp {

	  if($1.tipo !=  ENTERO || $3.tipo !=  ENTERO){
	    printf("****Error semantico en lin %d: Operacion aritmetica con operandos boolean.\n", linea);
	    return 0;
	  }
	  $$.tipo = ENTERO;
	  $$.es_direccion = 0;

	  multiplicar(fpasm, $3.es_direccion, $1.es_direccion); /* Cambiada */

	    fprintf(yyout, ";R75:\t<exp> ::= <exp> * <exp> \n");}
  | TOK_MENOS exp %prec NEGATIVO {

	  if($2.tipo !=  ENTERO){
	    printf("****Error semantico en lin %d: Operacion aritmetica con operandos boolean.\n", linea);
	    return 0;
	  }
	  $$.tipo = ENTERO;
	  $$.es_direccion = 0;

	  cambiar_signo(fpasm, $2.es_direccion); /*Cambiada*/

	    fprintf(yyout, ";R76:\t<exp> ::= - <exp> \n");}
 | exp TOK_AND exp {
	/*EXPRESIONES LOGICAS*/
	  if($1.tipo !=  BOOLEANO || $3.tipo !=  BOOLEANO){
	    printf("****Error semantico en lin %d: Operacion logica con operandos int.\n", linea);
	    return 0;
	  }
	  $$.tipo = BOOLEANO;
	  $$.es_direccion = 0;

	  y(fpasm, $3.es_direccion,$1.es_direccion);

	  fprintf(yyout, ";R77:\t<exp> ::= <exp> && <exp> \n");}

| exp TOK_OR exp {

	  if($1.tipo !=  BOOLEANO || $3.tipo !=  BOOLEANO){
	    printf("****Error semantico en lin %d: Operacion logica con operandos int.\n", linea);
	    return 0;
	  }
	  $$.tipo = BOOLEANO;
	  $$.es_direccion = 0;

	  o(fpasm, $3.es_direccion,$1.es_direccion);

	    fprintf(yyout, ";R78:\t<exp> ::= <exp> || <exp> \n");}
  | TOK_NOT exp {

	  if($2.tipo !=  BOOLEANO){
	    printf("****Error semantico en lin %d: Operacion logica con operandos int.\n", linea);
	    return 0;
	  }
	  $$.tipo = BOOLEANO;
	  $$.es_direccion = 0;

	  no(fpasm, $2.es_direccion, etiqueta);
	  etiqueta++;

	  fprintf(yyout, ";R79:\t<exp> ::= ! <exp> \n");}
  | TOK_IDENTIFICADOR {
	      /*Se comprueba que el identificador no exista en el ambito actual. Si existiera, se genera un
	      mensaje de error semantico y se termina el proceso de compilacion con error.*/
	    if(ambito_actual == GLOBAL){
	      dato = busquedaGlobal($1.lexema, tablaGlobal);
	    }else{
	      dato = busquedaLocal($1.lexema, tablaGlobal, tablaLocal);
	    }
	    if(dato == NULL){
	      printf("****Error semantico en lin %d: Acceso a variable no declarada (%s).\n", linea, $1.lexema);
	      return 0;
	    }

	    if(dato->clase == VECTOR || dato->categoria == FUNCION){
	    	printf("****Error semantico en lin %d: Asignacion incompatible\n", linea);
	    	return 0;
	    }
	    $$.tipo = dato->tipo;
	    $$.es_direccion=1;

		/*GENERACION DE CODIGO*/
		if(dato->categoria == PARAMETRO){
			$$.es_direccion = 0;
			exp_parametro(fpasm, num_parametros_actual, dato->adicional2);
		}else if(dato->adicional2 == 0){
			if(en_explist == 0){/*si no es una direccion en la lista de parametros d la fn en_explist = 1*/
				$$.es_direccion = 1;
				escribir_operando(fpasm, $1.lexema, 0);
			}else{
				$$.es_direccion = 0;
				escribir_operando(fpasm, $1.lexema, 1);
			}
		}else{
			$$.es_direccion = 0;
			exp_local(fpasm, dato->adicional2);
		}

	    fprintf(yyout, ";R80:\t<exp> ::= <identificador> \n");}
  | constante {

	    $$.tipo = $1.tipo;
	    $$.es_direccion = $1.es_direccion;

    	    fprintf(yyout, ";R81:\t<exp> ::= <constante> \n");}
  | TOK_PARENTESISIZQUIERDO exp TOK_PARENTESISDERECHO {

	    $$.tipo = $2.tipo;
	    $$.es_direccion = $2.es_direccion;

	    fprintf(yyout, ";R82:\t<exp> ::= ( <exp> ) \n");}
  | TOK_PARENTESISIZQUIERDO comparacion TOK_PARENTESISDERECHO {

	    $$.tipo = $2.tipo;
	    $$.es_direccion = $2.es_direccion;

	    fprintf(yyout, ";R83:\t<exp> ::= ( <comparacion> ) \n");}
  | elemento_vector {

	$$.tipo = $1.tipo;

	if(en_explist == 0){
		$$.es_direccion = $1.es_direccion;
	}else{
		$$.es_direccion = 0;
	}
	fprintf(yyout, ";R85:\t<exp> ::= <elemento_vector> \n");}

  | idf_llamada_funcion TOK_PARENTESISIZQUIERDO lista_expresiones TOK_PARENTESISDERECHO {
	dato = busquedaGlobal($1.lexema, tablaGlobal);
	if (dato == NULL) {
		printf("****Error semantico en lin %d: Acceso a variable no declarada (%s)\n", linea, $1.lexema);
		return 0;
	}
	if(dato->adicional1 != num_parametros_llamada_actual){
		printf("****Error semantico en lin %d: Numero incorrecto de parametros en llamada a funcion (%s)\n", linea, $1.lexema);
		return 0;
	}
	/*GENERACION*/
	fprintf(fpasm, "\n\tcall _%s\n", $1.lexema);
	fprintf(fpasm, "\tadd esp, 4*%d\n", num_parametros_llamada_actual);
	fprintf(fpasm, "\tpush dword eax\n");

	en_explist = 0;
	$$.tipo = dato->tipo;
	$$.es_direccion = 0;

	fprintf(yyout, ";R88:\t<exp> ::= <identificador> ( <lista_expresiones> ) \n");};
/*************************************/
idf_llamada_funcion:TOK_IDENTIFICADOR {
dato = busquedaGlobal($1.lexema, tablaGlobal);
if (dato == NULL) {
	printf("****Error semantico en lin %d: Acceso a variable no declarada (%s)\n", linea, $1.lexema);
	return 0;
}
if(dato->categoria != FUNCION){
	printf("****Error semantico en lin %d: Asignacion incompatible\n", linea);
	return 0;
}
/*no podemos pasar una funcion por parametro a otra funcion*/
if(en_explist == 1){
	printf("****Error semantico en lin %d: No esta permitido el uso de llamadas a funciones como parametros de otras funciones\n", linea);
	return 0;
}
num_parametros_llamada_actual = 0;
en_explist = 1;
strcpy($$.lexema, $1.lexema);

};
/******************************************/
lista_expresiones: exp resto_lista_expresiones {
/*Aumentamos el numero de parametros de la llamada a la funcion*/
num_parametros_llamada_actual++;
fprintf(yyout, ";R89:\t<lista_expresiones> ::= <exp> <resto_lista_expresiones> \n");}
  | {fprintf(yyout, ";R90:\t<lista_expresiones> ::=  \n");};

resto_lista_expresiones: TOK_COMA exp resto_lista_expresiones {
num_parametros_llamada_actual++;
fprintf(yyout, ";R91:\t<resto_lista_expresiones> ::= , <exp> <resto_lista_expresiones> \n");}
  | {fprintf(yyout, ";R92:\t<resto_lista_expresiones> ::= \n");};

  comparacion: exp TOK_IGUAL exp {

    if($1.tipo !=  ENTERO || $3.tipo !=  ENTERO){
      printf("****Error semantico en lin %d: Comparacion con operandos boolean.\n", linea);
      return 0;
    }
    $$.tipo = BOOLEANO;
    $$.es_direccion = 0;

    igual(fpasm, etiqueta, $3.es_direccion, $1.es_direccion);
    etiqueta++;

    fprintf(yyout, ";R93:\t<comparacion> ::= <exp> == <exp> \n");}
    | exp TOK_DISTINTO exp {

    if($1.tipo !=  ENTERO || $3.tipo !=  ENTERO){
      printf("****Error semantico en lin %d: Comparacion con operandos boolean.\n", linea);
      return 0;
    }
    $$.tipo = BOOLEANO;
    $$.es_direccion = 0;

    distinto(fpasm, etiqueta, $3.es_direccion, $1.es_direccion);
    etiqueta++;

    fprintf(yyout, ";R94:\t<comparacion> ::= <exp> != <exp> \n");}
    | exp TOK_MENORIGUAL exp {

    if($1.tipo !=  ENTERO || $3.tipo !=  ENTERO){
      printf("****Error semantico en lin %d: Comparacion con operandos boolean.\n", linea);
      return 0;
    }
    $$.tipo = BOOLEANO;
    $$.es_direccion = 0;

    menorigual(fpasm, etiqueta, $3.es_direccion, $1.es_direccion);
    etiqueta++;

    fprintf(yyout, ";R95:\t<comparacion> ::= <exp> <= <exp> \n");}
    | exp TOK_MAYORIGUAL exp {

    if($1.tipo !=  ENTERO || $3.tipo !=  ENTERO){
      printf("****Error semantico en lin %d: Comparacion con operandos boolean.\n", linea);
      return 0;
    }
    $$.tipo = BOOLEANO;
    $$.es_direccion = 0;

    mayorigual(fpasm, etiqueta, $3.es_direccion, $1.es_direccion);
    etiqueta++;

    fprintf(yyout, ";R96:\t<comparacion> ::= <exp> >= <exp> \n");}
    | exp TOK_MENOR exp {

    if($1.tipo !=  ENTERO || $3.tipo !=  ENTERO){
      printf("****Error semantico en lin %d: Comparacion con operandos boolean.\n", linea);
      return 0;
    }
    $$.tipo = BOOLEANO;
    $$.es_direccion = 0;

    menor(fpasm, etiqueta, $3.es_direccion, $1.es_direccion);
    etiqueta++;

    fprintf(yyout, ";R97:\t<comparacion> ::= <exp> < <exp> \n");}
    | exp TOK_MAYOR exp {

    if($1.tipo !=  ENTERO || $3.tipo !=  ENTERO){
      printf("****Error semantico en lin %d: Comparacion con operandos boolean.\n", linea);
      return 0;
    }
    $$.tipo = BOOLEANO;
    $$.es_direccion = 0;

    mayor(fpasm, etiqueta, $3.es_direccion, $1.es_direccion);
    etiqueta++;

    fprintf(yyout, ";R98:\t<comparacion> ::= <exp> > <exp> \n");};

constante: constante_logica {

  $$.tipo = $1.tipo;
  $$.es_direccion = $1.es_direccion;

  fprintf(yyout, ";R99:\t<constante> ::= <constante_logica> \n");}
  | constante_entera {

  $$.tipo = $1.tipo;
  $$.es_direccion = $1.es_direccion;

  fprintf(yyout, ";R100:\t<constante> ::= <constante_entera> \n");};
constante_logica: TOK_TRUE {

    $$.tipo = BOOLEANO;
    $$.es_direccion = 0;

    /* generacion de codigo */
    fprintf(fpasm, "; numero_linea: %d\n", linea);
    fprintf(fpasm, "\tpush dword 1\n");

    fprintf(yyout, ";R102:\t<constante_logica> ::= true \n");}
    | TOK_FALSE {

    $$.tipo = BOOLEANO;
    $$.es_direccion = 0;

    /* generacion de codigo */
    fprintf(fpasm, "; numero_linea: %d\n", linea);
    fprintf(fpasm, "\tpush dword 0\n");

    fprintf(yyout, ";R103:\t<constante_logica> ::= false \n");};

constante_entera: TOK_CONSTANTE_ENTERA {

    $$.tipo = ENTERO;
    $$.es_direccion = 0;

    /* generacion de codigo */
    fprintf(fpasm, "; numero_linea %d\n", linea);
    fprintf(fpasm, "\tpush dword %d\n", $1.valor_entero);

    fprintf(yyout, ";R104:\t<constante_entera> ::= TOK_CONSTANTE_ENTERA \n");};

identificador: TOK_IDENTIFICADOR {
	if (ambito_actual == GLOBAL){
 		declarar = DeclararVariableGlobal(tablaGlobal, $1.lexema, categoria_actual, tipo_actual, clase_actual, 0, 0);
	}else{
		declarar = DeclararVariableLocal(tablaLocal, $1.lexema, categoria_actual, tipo_actual, clase_actual, 0, 0);
	}
	if(declarar == ERR){
		printf("****Error semantico en lin %d: Declaracion duplicada.\n", linea);
		return 0;
	}else{
		adic1 ++;
	}
	if (ambito_actual == GLOBAL){
		dato = busquedaGlobal($1.lexema, tablaGlobal);
	}else{
		dato = busquedaLocal($1.lexema, tablaGlobal, tablaLocal);
	}
	if (!dato) {
		printf("****Error semantico en lin %d: IAcceso a variable no declarada (%s)\n", linea, $1.lexema);
		return 0;
	}
	/*GENERACION DE CODIGO*/

	if(es_funcion == 0){
		declarar_variable(fpasm, $1.lexema, clase_actual, tamanio_vector_actual);
		dato->clase = clase_actual;
		dato->tipo = tipo_actual;
		/*vectores*/
		if(dato->clase == VECTOR){
			dato->adicional1 = tamanio_vector_actual;
			strcpy(nombre_vector_actual, $1.lexema);
		}
	}else{
		if(clase_actual == VECTOR){
			printf("****Error semantico en lin %d: Variable local de tipo no escalar.\n", linea);
			return 0;
		}

		dato->tipo = tipo_actual;
		dato->clase = clase_actual;
		dato->adicional2 = pos_variable_local_actual;
		num_variables_locales_actual++;
		pos_variable_local_actual++;
	}



  fprintf(yyout, ";R108:\t<identificador> ::= TOK_IDENTIFICADOR \n");};

%%
void yyerror(char* s){
	if(error == 0){
		fprintf(stdout,"**** Error sintáctico en [lin %d, col %d]\n",linea, (columna-yyleng));
	}
	error = 0;
}
/*pila arriba-abajo mayor-menor*/

/*fallo trasp 85-> despues de mul edx-> mov eax, edx*/

/*FUNCIONES*/
/*llamada a la funcion*/
/*Parametros: controlar si al llamar a la funcion le ponemos todos los parámetros que tiene en su declaracion (lo comprobamos en la llamada de la funcion)*/
/*En eax tenemos el resultado de la funcion. Lo metemos en la pila y hacemos un call para sacarlo (llamada a la funcion)*/

/*EBP -> puntero de pila auxiliar [mov esp, ebp]
al encontrarnos con una llamada a una funcion apilamos el epb  (direccion de retorno) para despues de hacer la funcion volver al codigo main*/



/*************VECTORES***************/
/*- que el tamaño del vector sea un numero (y sea maximo 64 y minimo 1)
- que el tipo de dato sea entero o booleano*/
/* OPERACIONES
solo con elemntos de vectores:
- que sea de tipo entero la posicion de elemento del vector: elemento[NUMERO]
- comprobar en tiempo de EJECUCION: que el elemento acceda a una posicion menor que el tamaño del vector elemento[numero <= tamaño vector y > 0]
*/
/*GENERACION DE CODIGO*/
/*ERROR PAG 42 generacion codigo*/
