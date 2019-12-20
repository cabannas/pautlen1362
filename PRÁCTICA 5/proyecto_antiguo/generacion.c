
#include <stdio.h>
#include "generacion.h"

/* Declaraciones de tipos de datos del compilador */
#define ENTERO 0
#define BOOLEANO 1



/* OBSERVACIÓN GENERAL A TODAS LAS FUNCIONES:
   Todas ellas escriben el código NASM a un FILE* proporcionado como primer argumento.
*/

/*void escribir_cabecera_compatibilidad(FILE* fpasm){

}*/
/*
   Función para imprimir el código NASM necesario para que sea multiplataforma.
*/

void escribir_subseccion_data(FILE* fpasm){
   fprintf(fpasm, ";escribir_subseccion_data\n");
   fprintf(fpasm, "\nsegment .data\n\n");
   fprintf(fpasm, "\t_msg_fuera_rango db \"****Error de ejecucion: Indice fuera de rango.\", 0\n\n");
   fprintf(fpasm, "\t_msg_div_cero db \"Error de ejecucion: Division por cero\", 0\n\n");

}
/*
   Declaración (con directiva db) de las variables que contienen el texto de los mensajes para la identificación de errores en tiempo de ejecución.
   En este punto, al menos, debes ser capaz de detectar la división por 0.
*/

void escribir_cabecera_bss(FILE* fpasm){
   fprintf(fpasm, ";escribir_cabecera_bss\n");
   fprintf(fpasm, "\nsegment .bss\n\n");
   fprintf(fpasm, "__esp resd 1\n");
}
/*
   Código para el principio de la sección .bss.
   Con seguridad sabes que deberás reservar una variable entera para guardar el puntero de pila extendido (esp). Se te sugiere el nombre __esp para esta variable.
*/

void declarar_variable(FILE* fpasm, char * nombre, int clase, int tamano){
 	if(clase == ESCALAR){/*Si es un escalar, reservamos para tamaño 1*/
        fprintf(fpasm,"\t_%s resd 1\n", nombre);

    } else if(clase == VECTOR) {/*Si es un vector, reservamos el tamaño recibido de la estructura ELELIST*/
        fprintf(fpasm, "\t_%s resd %d \n", nombre, tamano);
    }
}
/*
   Para ser invocada en la sección .bss cada vez que se quiera declarar una variable:
El argumento nombre es el de la variable.
tipo puede ser ENTERO o BOOLEANO (observa la declaración de las constantes del principio del fichero).
Esta misma función se invocará cuando en el compilador se declaren vectores, por eso se adjunta un argumento final (tamano) que para esta primera práctica siempre recibirá el valor 1.
*/

void escribir_segmento_codigo(FILE* fpasm){
	fprintf(fpasm, ";escribir_segmento_codigo\n");
	fprintf(fpasm,"\nsegment .text\n\tglobal main\n\textern scan_int, print_int, scan_float, print_float,");
	fprintf(fpasm,"\n\textern scan_boolean, print_boolean\n\textern print_endofline, print_blank, print_string");
	fprintf(fpasm,"\n\textern alfa_malloc, alfa_free, ld_float\n\n\n");
}
/*
   Para escribir el comienzo del segmento .text, básicamente se indica que se exporta la etiqueta main y que se usarán las funciones declaradas en la librería alfalib.o
*/

void escribir_inicio_main(FILE* fpasm){
   fprintf(fpasm, ";escribir_inicio_main\n");
   fprintf(fpasm, "main: \n");
   fprintf(fpasm, "\tmov dword [__esp], esp\n\n");
}
/*
   En este punto se debe escribir, al menos, la etiqueta main y la sentencia que guarda el puntero de pila en su variable (se recomienda usar __esp).
*/

void escribir_fin(FILE* fpasm){

  /* Para no entrar en los errores*/
  fprintf(fpasm, "\tjmp near fin\n");

  /*Fuera de Rango*/
  fprintf(fpasm, "\nFUERA_RANGO:\n");
  fprintf(fpasm, "\tpush dword _msg_fuera_rango\n");
  fprintf(fpasm, "\tcall print_string\n");
  fprintf(fpasm, "\tadd esp, 4\n");
  fprintf(fpasm, "\tjmp near fin\n");

  /*Division por 0*/
  fprintf(fpasm, "\nDIV_CERO:\n");
  fprintf(fpasm, "\tpush dword _msg_div_cero\n");
  fprintf(fpasm, "\tcall print_string\n");
  fprintf(fpasm, "\tadd esp, 4\n");
  fprintf(fpasm, "\tjmp near fin\n");

  fprintf(fpasm, ";escribir_fin\n");
  fprintf(fpasm, "\tfin:\n");
  fprintf(fpasm, "\tmov dword esp, [__esp]\n");
  fprintf(fpasm, "\tret\n");

}
/*
   Al final del programa se escribe:
El código NASM para salir de manera controlada cuando se detecta un error en tiempo de ejecución (cada error saltará a una etiqueta situada en esta zona en la que se imprimirá el correspondiente mensaje y se saltará a la zona de finalización del programa).
En el final del programa se debe:
         ·Restaurar el valor del puntero de pila (a partir de su variable __esp)
         ·Salir del programa (ret).
*/

void escribir_operando(FILE* fpasm, char* nombre, int es_var){
   fprintf(fpasm, ";escribir_operando\n");
   if(es_var == 1){ /*Si es una variable*/
      fprintf(fpasm, "\tpush dword [_%s]\n", nombre);

   }else if(es_var == 0){
      fprintf(fpasm, "\tpush dword _%s\n", nombre);
   }
}
/*
   Función que debe ser invocada cuando se sabe un operando de una operación aritmético-lógica y se necesita introducirlo en la pila.
nombre es la cadena de caracteres del operando tal y como debería aparecer en el fuente NASM
es_var indica si este operando es una variable (como por ejemplo b1) con un 1 u otra cosa (como por ejemplo 34) con un 0.
 Recuerda que en el primer caso internamente se representará como _b1 y, sin embargo, en el segundo se representará tal y como esté en el argumento (34).
*/

void asignar(FILE* fpasm, char* lexema, int es_direccion){
	fprintf(fpasm, "; Cargar en eax la parte derecha de la asignacion\n");
	fprintf(fpasm, "\tpop dword eax\n");

	if(es_direccion == 1){/*direccion*/
		fprintf(fpasm, "\tmov dword eax , [eax]\n");
	}
  fprintf(fpasm, "; Hacer la asignacion efectiva\n");
  fprintf(fpasm, "\tmov dword [_%s] , eax\n", lexema);
}
/*
Genera el código para asignar valor a la variable de nombre nombre.
Se toma el valor de la cima de la pila.
El último argumento es el que indica si lo que hay en la cima de la pila es una referencia (1) o ya un valor explícito (0).
*/

/******************Asignar vector*********************/
void asignar_vector(FILE * fpasm, int es_direccion)
{
    fprintf(fpasm, "; Cargar en eax la parte derecha de la asignacion\n");
    fprintf(fpasm, "\tpop dword eax\n");
    if(es_direccion == 1){
    	fprintf(fpasm, "\tmov dword eax, [eax]\n");
    }
    fprintf(fpasm, "; Cargar en edx la parte izquierda de la asignacion\n");
	  fprintf(fpasm, "\tpop dword edx\n");
    fprintf(fpasm, "; Hacer la asignacion efectiva\n");
    fprintf(fpasm, "\tmov dword [edx] , eax\n");
}
/*****************************************************/

/* FUNCIONES ARITMÉTICO-LÓGICAS BINARIAS */
/*
  En todas ellas se realiza la operación como se ha resumido anteriormente:
Se extrae de la pila los operandos
Se realiza la operación
Se guarda el resultado en la pila
   Los dos últimos argumentos indican respectivamente si lo que hay en la pila es una referencia a un valor o un valor explícito.
   Deben tenerse en cuenta las peculiaridades de cada operación. En este sentido sí hay que mencionar explícitamente que, en el caso de la división, se debe controlar si el divisor es “0” y en ese caso se debe saltar a la rutina de error controlado (restaurando el puntero de pila en ese caso y comprobando en el retorno que no se produce “Segmentation Fault”)
*/
void sumar(FILE* fpasm, int es_direccion3, int es_direccion1){

	fprintf(fpasm, ";sumar\n");

  fprintf(fpasm, "; cargar el segundo operando en edx\n");
  fprintf(fpasm, "\tpop dword edx\n");

	if(es_direccion3){
		fprintf(fpasm, "\tmov dword edx , [edx]\n");
	}

  fprintf(fpasm, "; cargar el primer operando en eax\n");
  fprintf(fpasm, "\tpop dword eax\n");

  if(es_direccion1){
		fprintf(fpasm, "\tmov dword eax , [eax]\n");
	}
  fprintf(fpasm, "; realizar la suma y dejar el resultado en eax\n");
  fprintf(fpasm, "\tadd eax, edx\n");

  fprintf(fpasm, "; apilar el resultado\n");
  fprintf(fpasm, "\tpush dword eax\n");

}


void restar(FILE* fpasm, int es_direccion3, int es_direccion1){

	fprintf(fpasm, ";restar\n");

  fprintf(fpasm, "; cargar el segundo operando en edx\n");
  fprintf(fpasm, "\tpop dword edx\n");

	if(es_direccion3){
		fprintf(fpasm, "\tmov dword edx , [edx]\n");
	}

  fprintf(fpasm, "; cargar el primer operando en eax\n");
  fprintf(fpasm, "\tpop dword eax\n");

  if(es_direccion1){
		fprintf(fpasm, "\tmov dword eax , [eax]\n");
	}
  fprintf(fpasm, "; realizar la resta y dejar el resultado en eax\n");
  fprintf(fpasm, "\tsub eax, edx\n");

  fprintf(fpasm, "; apilar el resultado\n");
  fprintf(fpasm, "\tpush dword eax\n");

}
void multiplicar(FILE* fpasm, int es_direccion3, int es_direccion1){
  fprintf(fpasm, ";multiplicar\n");

  fprintf(fpasm, "; cargar el segundo operando en ecx\n");
  fprintf(fpasm, "\tpop dword ecx\n");

  if(es_direccion3 == 1){
    fprintf(fpasm, "\tmov dword ecx , [ecx]\n");
  }

  fprintf(fpasm, "; cargar el primer operando en eax\n");
  fprintf(fpasm, "\tpop dword eax\n");

  if(es_direccion1 == 1){
    fprintf(fpasm, "\tmov dword eax , [eax]\n");
  }
  fprintf(fpasm, "\tcdq\n\timul ecx\n");
  fprintf(fpasm, "\tpush dword eax\n");

}
void dividir(FILE* fpasm, int es_direccion3, int es_direccion1){

  fprintf(fpasm, ";dividir\n");

  fprintf(fpasm, "; cargar el segundo operando en ecx\n");
  fprintf(fpasm, "\tpop dword ecx\n");

	if(es_direccion3){
		fprintf(fpasm, "\tmov dword ecx , [ecx]\n");
	}

  fprintf(fpasm, "; cargar el primer operando en eax\n");
  fprintf(fpasm, "\tpop dword eax\n");

  if(es_direccion1){
		fprintf(fpasm, "\tmov dword eax , [eax]\n");
	}

  fprintf(fpasm, "; comparar si divide por 0\n");
  fprintf(fpasm,"\tcmp ecx, 0\n");
	fprintf(fpasm,"\tje DIV_CERO\n");

  fprintf(fpasm, "; realizar la division y el resultado se queda en eax\n");
  fprintf(fpasm, "\tcdq\n\tidiv ecx\n");

  fprintf(fpasm, "; apilar el resultado\n");
  fprintf(fpasm, "\tpush dword eax\n");

}

void o(FILE* fpasm, int es_direccion3, int es_direccion1){

	fprintf(fpasm, ";y\n");

  fprintf(fpasm, "; cargar el segundo operando en edx\n");
  fprintf(fpasm, "\tpop dword edx\n");

	if(es_direccion3 == 1){
		fprintf(fpasm, "\tmov dword edx , [edx]\n");
	}

  fprintf(fpasm, "; cargar el primer operando en eax\n");
  fprintf(fpasm, "\tpop dword eax\n");

	if(es_direccion1 == 1){
		fprintf(fpasm, "\tmov dword eax , [eax]\n");
	}
  fprintf(fpasm, "; realizar la conjunción y dejar el resultado en eax\n");
  fprintf(fpasm, "\tor eax , edx\n");

  fprintf(fpasm, "; apilar el resultado\n");
  fprintf(fpasm, "\tpush dword eax\n");

}

void y(FILE* fpasm, int es_direccion3, int es_direccion1){

	fprintf(fpasm, ";y\n");
	fprintf(fpasm, "; cargar el segundo operando en edx\n");
	fprintf(fpasm, "\tpop dword edx\n");
	if(es_direccion3 == 1){
		fprintf(fpasm, "\tmov dword edx , [edx]\n");
	}
	fprintf(fpasm, "; cargar el primer operando en eax\n");
	fprintf(fpasm, "\tpop dword eax\n");
	if(es_direccion1 == 1){
		fprintf(fpasm, "\tmov dword eax , [eax]\n");
	}
	fprintf(fpasm, "; realizar la conjunción y dejar el resultado en eax\n");
	fprintf(fpasm, "\tand eax , edx\n");

	fprintf(fpasm, "; apilar el resultado\n");
	fprintf(fpasm, "\tpush dword eax\n");
}

void cambiar_signo(FILE* fpasm, int es_direccion){

  fprintf(fpasm, ";cambiar_signo\n");

  fprintf(fpasm, "; cargar el operando en eax\n");
  fprintf(fpasm, "\tpop dword eax\n");

  if(es_direccion){
    fprintf(fpasm, "\tmov dword eax , [eax]\n");
  }

  fprintf(fpasm, "; realizar la negación, multiplicando por -1 y el resultado se queda en eax\n");
  fprintf(fpasm, "\tmov ecx, -1\n");
	fprintf(fpasm, "\timul ecx\n");
  /*Alternativa de las diapositivas:
    fprintf(fpasm, "\tneg eax\n");
  */
  fprintf(fpasm, "; apilar el resultado\n");
  fprintf(fpasm, "\tpush dword eax\n");

}
/*
   Función aritmética de cambio de signo.
   Es análoga a las binarias, excepto que sólo requiere de un acceso a la pila ya que sólo usa un operando.
*/

void no(FILE* fpasm, int es_direccion, int cuantos_no){

	fprintf(fpasm, ";no\n");
  fprintf(fpasm, "; cargar el operando en eax\n");
  fprintf(fpasm, "\tpop dword eax\n");

	if(es_direccion == 1){
		fprintf(fpasm, "\tmov dword eax , [eax]\n");
  }

  fprintf(fpasm, "; ver si eax es 0 y en ese caso saltar a negar_falso\n");
  fprintf(fpasm, "\tor eax , eax\n");
  fprintf(fpasm, "\tjz near negar_falso%d\n", cuantos_no);

  fprintf(fpasm, "; cargar 0 en eax (negación de verdadero) y saltar al final\n");
  fprintf(fpasm, "\tmov dword eax,0\n");
  fprintf(fpasm, "\tjmp near fin_negacion%d\n", cuantos_no);

  fprintf(fpasm, "; cargar 1 en eax (negación de falso)\n");
  fprintf(fpasm, "\tnegar_falso%d: mov dword eax,1\n", cuantos_no);

  fprintf(fpasm, "; apilar eax\n");
  fprintf(fpasm, "\tfin_negacion%d: push dword eax\n", cuantos_no);
}


void igual(FILE * fpasm, int etiqueta, int es_direccion3, int es_direccion1) {


  fprintf(fpasm,"; igual\n");
  fprintf(fpasm,"; cargar la segunda expresión en edx\n");
  fprintf(fpasm,"\tpop dword edx\n");

	if(es_direccion3 == 1){ /*A lo mejor hay que negarlo pero no creo*/
		fprintf(fpasm,"\tmov dword edx , [edx]\n");
	}

  fprintf(fpasm,"; cargar la primera expresión en eax\n");
	fprintf(fpasm,"\tpop dword eax\n");

	if(es_direccion1 == 1){
		fprintf(fpasm,"\tmov dword eax , [eax]\n");
	}

  fprintf(fpasm,"; comparar y apilar el resultado\n");
	fprintf(fpasm,"\tcmp eax, edx\n");
	fprintf(fpasm,"\tje near igual%d\n", etiqueta);
	fprintf(fpasm,"\tpush dword 0\n");
	fprintf(fpasm,"\tjmp near fin_igual%d\n", etiqueta);
	fprintf(fpasm,"\nigual%d:\n\tpush dword 1\n", etiqueta);
	fprintf(fpasm,"\nfin_igual%d:\n", etiqueta);

}


void distinto(FILE * fpasm, int etiqueta, int es_direccion3, int es_direccion1) {


	fprintf(fpasm,"; distinto\n");
	fprintf(fpasm,"; cargar la segunda expresión en edx\n");
	fprintf(fpasm,"\tpop dword edx\n");

	if(es_direccion3){ /*A lo mejor hay que negarlo pero no creo*/
		fprintf(fpasm,"\tmov dword edx , [edx]\n");
	}

	fprintf(fpasm,"; cargar la primera expresión en eax\n");
	fprintf(fpasm,"\tpop dword eax\n");

	if(es_direccion1){
		fprintf(fpasm,"\tmov dword eax , [eax]\n");
	}

	fprintf(fpasm,"; comparar y apilar el resultado\n");
	fprintf(fpasm,"\tcmp eax, edx\n");
	fprintf(fpasm,"\tjne near distinto%d\n", etiqueta);
	fprintf(fpasm,"\tpush dword 0\n");
	fprintf(fpasm,"\tjmp near fin_distinto%d\n", etiqueta);
	fprintf(fpasm,"\ndistinto%d:\n\tpush dword 1\n", etiqueta);
	fprintf(fpasm,"\nfin_distinto%d:\n", etiqueta);

}


void menorigual(FILE * fpasm, int etiqueta, int es_direccion3, int es_direccion1) {
/*CAMBIADO DANI NUEVO*/

	fprintf(fpasm,"; menorigual\n");
	fprintf(fpasm,"; cargar la segunda expresión en edx\n");
	fprintf(fpasm,"\tpop dword edx\n");

	if(es_direccion3){ /*A lo mejor hay que negarlo pero no creo*/
		fprintf(fpasm,"\tmov dword edx , [edx]\n");
	}

	fprintf(fpasm,"; cargar la primera expresión en eax\n");
	fprintf(fpasm,"\tpop dword eax\n");

	if(es_direccion1){
		fprintf(fpasm,"\tmov dword eax , [eax]\n");
	}

	fprintf(fpasm,"; comparar y apilar el resultado\n");
	fprintf(fpasm,"\tcmp eax, edx\n");
	fprintf(fpasm,"\tjle near menorigual%d\n", etiqueta);
	fprintf(fpasm,"\tpush dword 0\n");
	fprintf(fpasm,"\tjmp near fin_menorigual%d\n", etiqueta);
	fprintf(fpasm,"\nmenorigual%d:\n\tpush dword 1\n", etiqueta);
	fprintf(fpasm,"\nfin_menorigual%d:\n", etiqueta);

}


void mayorigual(FILE * fpasm, int etiqueta, int es_direccion3, int es_direccion1) {
/*CAMBIADO DANI NUEVO*/

	fprintf(fpasm,"; mayorigual\n");
	fprintf(fpasm,"; cargar la segunda expresión en edx\n");
	fprintf(fpasm,"\tpop dword edx\n");

	if(es_direccion3){ /*A lo mejor hay que negarlo pero no creo*/
		fprintf(fpasm,"\tmov dword edx , [edx]\n");
	}

	fprintf(fpasm,"; cargar la primera expresión en eax\n");
	fprintf(fpasm,"\tpop dword eax\n");

	if(es_direccion1){
		fprintf(fpasm,"\tmov dword eax , [eax]\n");
	}

	fprintf(fpasm,"; comparar y apilar el resultado\n");
	fprintf(fpasm,"\tcmp eax, edx\n");
	fprintf(fpasm,"\tjge near mayorigual%d\n", etiqueta);
	fprintf(fpasm,"\tpush dword 0\n");
	fprintf(fpasm,"\tjmp near fin_mayorigual%d\n", etiqueta);
	fprintf(fpasm,"\nmayorigual%d:\n\tpush dword 1\n", etiqueta);
	fprintf(fpasm,"\nfin_mayorigual%d:\n", etiqueta);

}


void menor(FILE * fpasm, int etiqueta, int es_direccion3, int es_direccion1) {
/*CAMBIADO DANI NUEVO*/

	fprintf(fpasm,"; menor\n");
	fprintf(fpasm,"; cargar la segunda expresión en edx\n");
	fprintf(fpasm,"\tpop dword edx\n");

	if(es_direccion3){ /*A lo mejor hay que negarlo pero no creo*/
		fprintf(fpasm,"\tmov dword edx , [edx]\n");
	}

	fprintf(fpasm,"; cargar la primera expresión en eax\n");
	fprintf(fpasm,"\tpop dword eax\n");

	if(es_direccion1){
		fprintf(fpasm,"\tmov dword eax , [eax]\n");
	}

	fprintf(fpasm,"; comparar y apilar el resultado\n");
	fprintf(fpasm,"\tcmp eax, edx\n");
	fprintf(fpasm,"\tjl near menor%d\n", etiqueta);
	fprintf(fpasm,"\tpush dword 0\n");
	fprintf(fpasm,"\tjmp near fin_menor%d\n", etiqueta);
	fprintf(fpasm,"\nmenor%d:\n\tpush dword 1\n", etiqueta);
	fprintf(fpasm,"\nfin_menor%d:\n", etiqueta);

}

void mayor(FILE * fpasm, int etiqueta, int es_direccion3, int es_direccion1) {
/*CAMBIADO DANI NUEVO*/

	fprintf(fpasm,"; mayor\n");
	fprintf(fpasm,"; cargar la segunda expresión en edx\n");
	fprintf(fpasm,"\tpop dword edx\n");

	if(es_direccion3){ /*A lo mejor hay que negarlo pero no creo*/
		fprintf(fpasm,"\tmov dword edx , [edx]\n");
	}

	fprintf(fpasm,"; cargar la primera expresión en eax\n");
	fprintf(fpasm,"\tpop dword eax\n");

	if(es_direccion1){
		fprintf(fpasm,"\tmov dword eax , [eax]\n");
	}

	fprintf(fpasm,"; comparar y apilar el resultado\n");
	fprintf(fpasm,"\tcmp eax, edx\n");
	fprintf(fpasm,"\tjg near mayor%d\n", etiqueta);
	fprintf(fpasm,"\tpush dword 0\n");
	fprintf(fpasm,"\tjmp near fin_mayor%d\n", etiqueta);
	fprintf(fpasm,"\nmayor%d:\n\tpush dword 1\n", etiqueta);
	fprintf(fpasm,"\nfin_mayor%d:\n", etiqueta);

}
/*
   Función monádica lógica de negación. No hay un código de operación de la ALU que realice esta operación por lo que se debe codificar un algoritmo que, si encuentra en la cima de la pila un 0 deja en la cima un 1 y al contrario.
   El último argumento es el valor de etiqueta que corresponde (sin lugar a dudas, la implementación del algoritmo requerirá etiquetas). Véase en los ejemplos de programa principal como puede gestionarse el número de etiquetas cuantos_no.
*/

/* FUNCIONES DE ESCRITURA Y LECTURA */
/*
   Se necesita saber el tipo de datos que se va a procesar (ENTERO o BOOLEANO) ya que hay diferentes funciones de librería para la lectura (idem. escritura) de cada tipo.
   Se deben insertar en la pila los argumentos necesarios, realizar la llamada (call) a la función de librería correspondiente y limpiar la pila.
*/
void leer(FILE* fpasm, char* nombre, int tipo){

  fprintf(fpasm, ";leer\n");
	fprintf(fpasm, "\tpush dword _%s\n", nombre);
	/*si es entero*/
	if(tipo == 0){
		fprintf(fpasm, "\tcall scan_int\n");
	}else{ /*si es booleano*/
		fprintf(fpasm, "\tcall scan_boolean\n");
	}
	fprintf(fpasm, "\tadd esp, 4\n");

}
void escribir(FILE* fpasm, int es_direccion, int tipo){
	fprintf(fpasm, "; Acceso al valor de exp si es distinto de constante\n");
	if(es_direccion == 1){
		fprintf(fpasm, "\tpop dword eax\n");
		fprintf(fpasm, "\tmov dword eax , [eax]\n");
    	fprintf(fpasm, "\tpush dword eax\n");
	}
	/*si es entero*/
	if(tipo == ENTERO){
		fprintf(fpasm, "\tcall print_int\n");
	}else if (tipo == BOOLEANO){ /*si es booleano*/
		fprintf(fpasm, "\tcall print_boolean\n");
	}
	fprintf(fpasm, "\tadd esp, 4\n");
	fprintf(fpasm, "\tcall print_endofline\n");
}
/*CONDICIONALES Y BUCLES*/
void abrir_if(FILE *fpasm, int etiqueta, int es_direccion){

  fprintf(fpasm, "\n\tpop dword eax\n");

	if(es_direccion){
		fprintf(fpasm, "\tmov eax, [eax]\n");
	}

	fprintf(fpasm, "\tcmp eax, 0\n");
	fprintf(fpasm, "\tje near fin_si%d\n", etiqueta);

}

void abrir_while(FILE *fpasm, int etiqueta, int es_direccion){

  fprintf(fpasm, "\n\tpop dword eax\n");

	if(es_direccion){
		fprintf(fpasm, "\tmov eax, [eax]\n");
	}

	fprintf(fpasm, "\tcmp eax, 0\n");
	fprintf(fpasm, "\tje near fin_while%d\n", etiqueta);

}

/*PARAMETROS***********************************************/
void asignar_parametro(FILE * fpasm, int num_parametro, int pos, int es_direccion) {
	int valor;
	valor = 4 + 4*(num_parametro - pos);
	fprintf(fpasm, "\n\tpop dword eax\n");
	if(es_direccion == 1){
		fprintf(fpasm, "\tmov dword eax, [eax]\n");
	}
	fprintf(fpasm, "\tmov dword [ebp+%d], eax\n", valor);
}

void leer_parametro(FILE * fpasm, int tipo, int num_parametro, int pos){
	int valor;
	valor = 4 + 4*(num_parametro - pos);
	fprintf(fpasm, ";lectura parametro\n");
	fprintf(fpasm, "\tlea eax, [ebp+%d]\n", valor);
	fprintf(fpasm, "\tpush dword eax\n");
	if (tipo == ENTERO) {
        fprintf(fpasm, "\tcall scan_int\n");
    }
    else if (tipo == BOOLEANO) {
        fprintf(fpasm, "\tcall scan_boolean\n");
    }
	fprintf(fpasm, "\tadd esp, 4\n");
}

void exp_parametro(FILE * fpasm, int num_parametro, int pos) {
	int valor;
	valor = 4 + 4*(num_parametro - pos);
	fprintf(fpasm, "\tlea eax, [ebp+%d]\n", valor);
	fprintf(fpasm, "\tpush dword [eax]\n");
}

/*ASIGNACIONES*/
void asignar_ident(FILE * fpasm, char * id, int es_direccion)
{
    fprintf(fpasm, "\tpop dword eax\n");
    if(es_direccion == 1){
    	fprintf(fpasm, "\tmov dword eax, [eax]\n");
    }
    fprintf(fpasm, "\tmov dword [_%s], eax\n", id);
}
/*FUNCIONES*/
void asignar_local(FILE * fpasm, int pos, int es_direccion) {
	int valor;
	valor = 4 * pos;
	fprintf(fpasm, "\n\tpop dword eax\n");
	if(es_direccion == 1){
		fprintf(fpasm, "\tmov dword eax, [eax]\n");
	}
	fprintf(fpasm, "\tmov dword [ebp-%d], eax\n", valor);
}

void leer_local(FILE * fpasm, int tipo, int pos){
	int valor;
	valor = 4*pos;
  fprintf(fpasm, "; lectura local\n");
	fprintf(fpasm, "\n;lea eax, [ebp-4*%d], eax\n", pos);
	fprintf(fpasm, "\tlea eax, [ebp-%d]\n", valor);
	fprintf(fpasm, "\tpush dword eax\n");
	if (tipo == ENTERO) {
        fprintf(fpasm, "\tcall scan_int\n");
    }else if (tipo == BOOLEANO) {
        fprintf(fpasm, "\tcall scan_boolean\n");
    }
    fprintf(fpasm, "\tadd esp, 4\n");
}

void exp_local(FILE * fpasm, int pos) {
	int valor;

	valor = 4*pos;
	fprintf(fpasm, "\tlea eax, [ebp-%d]\n", valor);
	fprintf(fpasm, "\tpush dword [eax]\n");
}

void retorno_funcion(FILE *fpasm, int es_direccion){
	fprintf(fpasm, "\n\tpop dword eax\n");
	if(es_direccion == 1){
		fprintf(fpasm, "\tmov eax, [eax]\n");
	}
	fprintf(fpasm, "\n\tmov dword esp, ebp\n");
	fprintf(fpasm, "\tpop dword ebp\n");
	fprintf(fpasm, "\tret\n");
}

/*VECTORES*/
void control_errores_vector(FILE * fpasm, char * id, int es_direccion, int tam){/*,int param*/


  fprintf(fpasm, "; Carga del valor del indice en eax\n");
	fprintf(fpasm, "\tpop dword eax\n");
	if(es_direccion == 1){
		fprintf(fpasm, "\tmov dword eax , [eax]\n");
	}

  fprintf(fpasm, "; Si indice < 0 error en tiempo de ejecucion\n");
	fprintf(fpasm, "\tcmp eax,0\n");
	fprintf(fpasm, "\tjl near FUERA_RANGO\n");

  fprintf(fpasm, "; Si indice > 64 error en tiempo de ejecucion\n");
	fprintf(fpasm, "\tcmp eax, %d\n", tam - 1);
	fprintf(fpasm, "\tjg near FUERA_RANGO\n"); /* en las diapos pone jl */



  fprintf(fpasm, "; Cargar en edx la direccion de inicio del vector\n");
	fprintf(fpasm, "\tmov dword edx,  _%s\n", id);

  fprintf(fpasm, "; Cargar en eax la direccion del elemento indexado\n");
	fprintf(fpasm, "\tlea eax, [edx+eax*4]\n");

  fprintf(fpasm, "; Apilar la direccion del elemento indexado\n");
	fprintf(fpasm, "\tpush dword eax\n");
}
