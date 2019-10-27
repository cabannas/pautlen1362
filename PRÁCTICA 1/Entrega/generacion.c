#include <stdio.h>

/* Declaraciones de tipos de datos del compilador */
#define ENTERO 0
#define BOOLEANO 1

/* OBSERVACIÓN GENERAL A TODAS LAS FUNCIONES:
Todas ellas escriben el código NASM a un FILE* proporcionado como primer
argumento.
*/
void escribir_cabecera_bss(FILE* fpasm){

  fprintf(fpasm,";escribir_cabecera_bss\n");

  fprintf(fpasm,"segment .bss\n");
  fprintf(fpasm,"\t__esp resd 1\n");
}
/*
Código para el principio de la sección .bss.
Con seguridad sabes que deberás reservar una variable entera para guardar el
puntero de pila extendido (esp). Se te sugiere el nombre __esp para esta variable.
*/
void escribir_subseccion_data(FILE* fpasm){

  fprintf(fpasm,"\n");
  fprintf(fpasm,";escribir_subseccion_data\n");

  fprintf(fpasm,"segment .data\n");
  fprintf(fpasm,"\tmsj_error_div_0 db \"Division por cero\", 0\n");
  fprintf(fpasm,"\tmsj_error_ind_fuera_rango db \"Indice fuera de rango\", 0\n");
}
/*
Declaración (con directiva db) de las variables que contienen el texto de los
mensajes para la identificación de errores en tiempo de ejecución.
En este punto, al menos, debes ser capaz de detectar la división por 0.
*/

void declarar_variable(FILE* fpasm, char * nombre, int tipo, int tamano){

  fprintf(fpasm,";declarar_variable\n");

  fprintf(fpasm,"\t_%s resd %d\n", nombre, tamano);
}
/*
Para ser invocada en la sección .bss cada vez que se quiera declarar una
variable:
- El argumento nombre es el de la variable.
- tipo puede ser ENTERO o BOOLEANO (observa la declaración de las constantes
del principio del fichero).
- Esta misma función se invocará cuando en el compilador se declaren
vectores, por eso se adjunta un argumento final (tamano) que para esta
primera práctica siempre recibirá el valor 1.
*/
void escribir_segmento_codigo(FILE* fpasm){

  fprintf(fpasm,"\n");
  fprintf(fpasm,";escribir_segmento_codigo\n");

  fprintf(fpasm,"segment .text\n");
  fprintf(fpasm,"\tglobal main\n");
  fprintf(fpasm,"\textern scan_int, print_int, scan_float, print_float, scan_boolean, print_boolean\n");
  fprintf(fpasm,"\textern print_endofline, print_blank, print_string\n");
  fprintf(fpasm,"\textern alfa_malloc, alfa_free, ld_float\n");
  fprintf(fpasm,"\n");
}
/*
Para escribir el comienzo del segmento .text, básicamente se indica que se
exporta la etiqueta main y que se usarán las funciones declaradas en la librería
alfalib.o
*/
void escribir_inicio_main(FILE* fpasm){

  fprintf(fpasm,";escribir_inicio_main\n");

  fprintf(fpasm,"main:\n");
  fprintf(fpasm,"\tmov dword [__esp], esp\n");
  fprintf(fpasm,"\n");
}
/*
En este punto se debe escribir, al menos, la etiqueta main y la sentencia que
guarda el puntero de pila en su variable (se recomienda usar __esp).
*/
void escribir_fin(FILE* fpasm){

  fprintf(fpasm,";escribir_fin\n");

  fprintf(fpasm,"quit:\n");
  fprintf(fpasm,"\tmov dword esp, [__esp]\n");
  fprintf(fpasm,"\tret\n");

  fprintf(fpasm,"error_division_por_cero:\n");
  fprintf(fpasm,"\tpush dword msj_error_div_0\n");
  fprintf(fpasm,"\tcall print_string\n");
  fprintf(fpasm,"\tadd esp, 4\n");
  fprintf(fpasm,"\tcall print_endofline\n");
  fprintf(fpasm,"\tjmp near quit\n");

  fprintf(fpasm,"error_indice_fuera_rango:\n");
  fprintf(fpasm,"\tpush dword msj_error_ind_fuera_rango\n");
  fprintf(fpasm,"\tcall print_string\n");
  fprintf(fpasm,"\tadd esp, 4\n");
  fprintf(fpasm,"\tcall print_endofline\n");
  fprintf(fpasm,"\tjmp near quit\n");
}
/*
Al final del programa se escribe:
- El código NASM para salir de manera controlada cuando se detecta un error
en tiempo de ejecución (cada error saltará a una etiqueta situada en esta
zona en la que se imprimirá el correspondiente mensaje y se saltará a la
zona de finalización del programa).
- En el final del programa se debe:
·Restaurar el valor del puntero de pila (a partir de su variable __esp)
·Salir del programa (ret).
*/
void escribir_operando(FILE* fpasm, char* nombre, int es_variable){

  fprintf(fpasm,";escribir_operando\n");

  if(es_variable){
    fprintf(fpasm,"\tpush dword _%s\n", nombre);
  }else{
    fprintf(fpasm,"\tpush dword %s\n", nombre);
  }
}
/*
Función que debe ser invocada cuando se sabe un operando de una operación
aritmético-lógica y se necesita introducirlo en la pila.
- nombre es la cadena de caracteres del operando tal y como debería aparecer
en el fuente NASM
- es_variable indica si este operando es una variable (como por ejemplo b1)
con un 1 u otra cosa (como por ejemplo 34) con un 0. Recuerda que en el
primer caso internamente se representará como _b1 y, sin embargo, en el
segundo se representará tal y como esté en el argumento (34).
*/
void asignar(FILE* fpasm, char* nombre, int es_variable){

  fprintf(fpasm,";asignar\n");

  fprintf(fpasm,"\tpop dword eax\n");
  /* no se puede hacer pop en una variable directamente, tenemos que usar
  los registros*/
  if(es_variable){
    fprintf(fpasm,"\tmov dword eax, [eax]\n");
    /* de este modo, si es una variable lo que está en el registro, sacaremos
    el valor de la variable y reescribiremos el registro*/
  }
  fprintf(fpasm,"\tmov dword [_%s], eax\n", nombre);
  /* asignamos a la nueva variable el valor que se encuentra en el registro*/


}
/*
- Genera el código para asignar valor a la variable de nombre nombre.
- Se toma el valor de la cima de la pila.
- El último argumento es el que indica si lo que hay en la cima de la pila es
una referencia (1) o ya un valor explícito (0).
*/

/* FUNCIONES ARITMÉTICO-LÓGICAS BINARIAS */
/*
En todas ellas se realiza la operación como se ha resumido anteriormente:
- Se extrae de la pila los operandos
- Se realiza la operación
- Se guarda el resultado en la pila
Los dos últimos argumentos indican respectivamente si lo que hay en la pila es
una referencia a un valor o un valor explícito.
explícito.
Deben tenerse en cuenta las peculiaridades de cada operación. En este sentido
sí hay que mencionar explícitamente que, en el caso de la división, se debe
controlar si el divisor es “0” y en ese caso se debe saltar a la rutina de error
controlado (restaurando el puntero de pila en ese caso y comprobando en el retorno
que no se produce “Segmentation Fault”)
*/

void sumar(FILE* fpasm, int es_variable_1, int es_variable_2){

  fprintf(fpasm,";sumar\n");

  fprintf(fpasm,"\tpop dword edx\n");
  if(es_variable_2){
    fprintf(fpasm,"\tmov dword edx, [edx]\n");
  }

  fprintf(fpasm,"\tpop dword eax\n");
  if(es_variable_1){
    fprintf(fpasm,"\tmov dword eax, [eax]\n");
  }

  fprintf(fpasm,"\tadd eax, edx\n");

  fprintf(fpasm,"\tpush dword eax\n");
}

void restar(FILE* fpasm, int es_variable_1, int es_variable_2){

  fprintf(fpasm, ";restar\n");

  fprintf(fpasm,"\tpop dword edx\n");
  if(es_variable_2){
    fprintf(fpasm,"\tmov dword edx, [edx]\n");
  }

  fprintf(fpasm,"\tpop dword eax\n");
  if(es_variable_1){
    fprintf(fpasm,"\tmov dword eax, [eax]\n");
  }

  fprintf(fpasm,"\tsub eax, edx\n");

  fprintf(fpasm,"\tpush dword eax\n");
}

void multiplicar(FILE* fpasm, int es_variable_1, int es_variable_2){

  fprintf(fpasm, ";multiplicar\n");

  fprintf(fpasm,"\tpop dword ecx\n");
  if(es_variable_2){
    fprintf(fpasm,"\tmov dword ecx, [ecx]\n");
  }

  fprintf(fpasm,"\tpop dword eax\n");
  if(es_variable_1){
    fprintf(fpasm,"\tmov dword eax, [eax]\n");
  }
  fprintf(fpasm,"\tcdq\n");
  fprintf(fpasm,"\timul ecx\n");

  fprintf(fpasm,"\tpush dword eax\n");

}

void dividir(FILE* fpasm, int es_variable_1, int es_variable_2){

  fprintf(fpasm, ";dividir\n");

  fprintf(fpasm,"\tpop dword ecx\n");
  if(es_variable_2){
    fprintf(fpasm,"\tmov dword ecx, [ecx]\n");
  }

  fprintf(fpasm,"\tpop dword eax\n");
  if(es_variable_1){
    fprintf(fpasm,"\tmov dword eax, [eax]\n");
  }

  fprintf(fpasm, "\tcmp ecx, 0\n");
  fprintf(fpasm, "\tje error_division_por_cero\n");

  fprintf(fpasm,"\tcdq\n");
  fprintf(fpasm,"\tidiv ecx\n");

  fprintf(fpasm,"\tpush dword eax\n");
}

void o(FILE* fpasm, int es_variable_1, int es_variable_2){

  fprintf(fpasm,";o\n");

  fprintf(fpasm,"\tpop dword edx\n");
  if(es_variable_2){
    fprintf(fpasm,"\tmov dword edx, [edx]\n");
  }

  fprintf(fpasm,"\tpop dword eax\n");
  if(es_variable_1){
    fprintf(fpasm,"\tmov dword eax, [eax]\n");
  }

  fprintf(fpasm,"\tor eax, edx\n");

  fprintf(fpasm,"\tpush dword eax\n");

}

void y(FILE* fpasm, int es_variable_1, int es_variable_2){
  fprintf(fpasm,";y\n");

  fprintf(fpasm,"\tpop dword edx\n");
  if(es_variable_2){
    fprintf(fpasm,"\tmov dword edx, [edx]\n");
  }

  fprintf(fpasm,"\tpop dword eax\n");
  if(es_variable_1){
    fprintf(fpasm,"\tmov dword eax, [eax]\n");
  }

  fprintf(fpasm,"\tand eax, edx\n");

  fprintf(fpasm,"\tpush dword eax\n");
}

void cambiar_signo(FILE* fpasm, int es_variable){
  fprintf(fpasm,";Cambiar_signo\n");

  fprintf(fpasm,"\tpop dword eax\n");
  if(es_variable){
    fprintf(fpasm,"\tmov dword eax, [eax]\n");
  }
  fprintf(fpasm,"\tmov dword ecx, -1\n"); //dword incluido 24 oct
  fprintf(fpasm,"\timul ecx\n");

  fprintf(fpasm,"\tpush dword eax\n");
}
/*
Función aritmética de cambio de signo.
Es análoga a las binarias, excepto que sólo requiere de un acceso a la pila ya
que sólo usa un operando.
*/

void no(FILE* fpasm, int es_variable, int cuantos_no){ //mov dwords eax 24 oct
  fprintf(fpasm,";no\n");

  fprintf(fpasm,"\tpop dword eax\n");
  if(es_variable){
    fprintf(fpasm,"\tmov dword eax, [eax]\n");
  }

  fprintf(fpasm,"\tcmp eax, 0\n");
  fprintf(fpasm,"\tje _es_cero%d\n", cuantos_no);

  fprintf(fpasm,"\tmov dword eax, 0\n");
  fprintf(fpasm,"\tjmp _no_fin%d\n", cuantos_no);

  fprintf(fpasm, "_es_cero%d:\n", cuantos_no);
  fprintf(fpasm, "\tmov dword eax, 1\n");

  fprintf(fpasm,"_no_fin%d:\n", cuantos_no);
  fprintf(fpasm,"\tpush dword eax\n");
}
/*
Función monádica lógica de negación. No hay un código de operación de la ALU
que realice esta operación por lo que se debe codificar un algoritmo que, si
encuentra en la cima de la pila un 0 deja en la cima un 1 y al contrario.
El último argumento es el valor de etiqueta que corresponde (sin lugar a dudas,
la implementación del algoritmo requerirá etiquetas). Véase en los ejemplos de
programa principal como puede gestionarse el número de etiquetas cuantos_no.
*/
/* FUNCIONES COMPARATIVAS */
/*
Todas estas funciones reciben como argumento si los elementos a comparar son o
no variables. El resultado de las operaciones, que siempre será un booleano (“1”
si se cumple la comparación y “0” si no se cumple), se deja en la pila como en el
resto de operaciones. Se deben usar etiquetas para poder gestionar los saltos
necesarios para implementar las comparaciones.
*/
void igual(FILE* fpasm, int es_variable1, int es_variable2, int etiqueta){
  fprintf(fpasm,";igual\n");

  fprintf(fpasm,"\tpop dword edx\n");
  if(es_variable2){
    fprintf(fpasm,"\tmov dword edx, [edx]\n");
  }

  fprintf(fpasm,"\tpop dword eax\n");
  if(es_variable1){
    fprintf(fpasm,"\tmov dword eax, [eax]\n");
  }

  fprintf(fpasm,"\tcmp eax, edx\n");
  fprintf(fpasm,"\tje _igual%d\n", etiqueta);

  fprintf(fpasm,"\tmov eax, 0\n");
  fprintf(fpasm,"\tjmp _fin_igual%d\n", etiqueta);

  fprintf(fpasm,"_igual%d:\n", etiqueta);
  fprintf(fpasm,"\tmov eax, 1\n");

  fprintf(fpasm,"_fin_igual%d:\n", etiqueta);

  fprintf(fpasm,"\tpush dword eax\n");
}

void distinto(FILE* fpasm, int es_variable1, int es_variable2, int etiqueta){

  fprintf(fpasm,";distinto\n");

  fprintf(fpasm,"\tpop dword edx\n");
  if(es_variable2){
    fprintf(fpasm,"\tmov dword edx, [edx]\n");
  }

  fprintf(fpasm,"\tpop dword eax\n");
  if(es_variable1){
    fprintf(fpasm,"\tmov dword eax, [eax]\n");
  }

  fprintf(fpasm,"\tcmp eax, edx\n");
  fprintf(fpasm,"\tjne _distinto%d\n", etiqueta);

  fprintf(fpasm,"\tmov eax, 0\n");
  fprintf(fpasm,"\tjmp _fin_distinto%d\n", etiqueta);

  fprintf(fpasm,"_distinto%d:\n", etiqueta);
  fprintf(fpasm,"\tmov eax, 1\n");

  fprintf(fpasm,"_fin_distinto%d:\n", etiqueta);

  fprintf(fpasm,"\tpush dword eax\n");

}

void menor_igual(FILE* fpasm, int es_variable1, int es_variable2, int etiqueta){
  fprintf(fpasm,";menor_igual\n");

  fprintf(fpasm,"\tpop dword edx\n");
  if(es_variable2){
    fprintf(fpasm,"\tmov dword edx, [edx]\n");
  }

  fprintf(fpasm,"\tpop dword eax\n");
  if(es_variable1){
    fprintf(fpasm,"\tmov dword eax, [eax]\n");
  }

  fprintf(fpasm,"\tcmp eax, edx\n");
  fprintf(fpasm,"\tjle _menor_igual%d\n", etiqueta);

  fprintf(fpasm,"\tmov eax, 0\n");
  fprintf(fpasm,"\tjmp _fin_menor_igual%d\n", etiqueta);

  fprintf(fpasm,"_menor_igual%d:\n", etiqueta);
  fprintf(fpasm,"\tmov eax, 1\n");

  fprintf(fpasm,"_fin_menor_igual%d:\n", etiqueta);

  fprintf(fpasm,"\tpush dword eax\n");
}

void mayor_igual(FILE* fpasm, int es_variable1, int es_variable2, int etiqueta){

  fprintf(fpasm,";mayor_igual\n");

  fprintf(fpasm,"\tpop dword edx\n");
  if(es_variable2){
    fprintf(fpasm,"\tmov dword edx, [edx]\n");
  }

  fprintf(fpasm,"\tpop dword eax\n");
  if(es_variable1){
    fprintf(fpasm,"\tmov dword eax, [eax]\n");
  }

  fprintf(fpasm,"\tcmp eax, edx\n");
  fprintf(fpasm,"\tjge _mayor_igual%d\n", etiqueta);

  fprintf(fpasm,"\tmov eax, 0\n");
  fprintf(fpasm,"\tjmp _fin_mayor_igual%d\n", etiqueta);

  fprintf(fpasm,"_mayor_igual%d:\n", etiqueta);
  fprintf(fpasm,"\tmov eax, 1\n");

  fprintf(fpasm,"_fin_mayor_igual%d:\n", etiqueta);

  fprintf(fpasm,"\tpush dword eax\n");
}


void menor(FILE* fpasm, int es_variable1, int es_variable2, int etiqueta){

  fprintf(fpasm,";menor\n");

  fprintf(fpasm,"\tpop dword edx\n");
  if(es_variable2){
    fprintf(fpasm,"\tmov dword edx, [edx]\n");
  }

  fprintf(fpasm,"\tpop dword eax\n");
  if(es_variable1){
    fprintf(fpasm,"\tmov dword eax, [eax]\n");
  }

  fprintf(fpasm,"\tcmp eax, edx\n");
  fprintf(fpasm,"\tjl _menor%d\n", etiqueta);

  fprintf(fpasm,"\tmov eax, 0\n");
  fprintf(fpasm,"\tjmp _fin_menor%d\n", etiqueta);

  fprintf(fpasm,"_menor%d:\n", etiqueta);
  fprintf(fpasm,"\tmov eax, 1\n");

  fprintf(fpasm,"_fin_menor%d:\n", etiqueta);

  fprintf(fpasm,"\tpush dword eax\n");
}


void mayor(FILE* fpasm, int es_variable1, int es_variable2, int etiqueta){

  fprintf(fpasm,";mayor\n");

  fprintf(fpasm,"\tpop dword edx\n");
  if(es_variable2){
    fprintf(fpasm,"\tmov dword edx, [edx]\n");
  }

  fprintf(fpasm,"\tpop dword eax\n");
  if(es_variable1){
    fprintf(fpasm,"\tmov dword eax, [eax]\n");
  }

  fprintf(fpasm,"\tcmp eax, edx\n");
  fprintf(fpasm,"\tjg _mayor%d\n", etiqueta);

  fprintf(fpasm,"\tmov eax, 0\n");
  fprintf(fpasm,"\tjmp _fin_mayor%d\n", etiqueta);

  fprintf(fpasm,"_mayor%d:\n", etiqueta);
  fprintf(fpasm,"\tmov eax, 1\n");

  fprintf(fpasm,"_fin_mayor%d:\n", etiqueta);

  fprintf(fpasm,"\tpush dword eax\n");
}

/* FUNCIONES DE ESCRITURA Y LECTURA */
/*
Se necesita saber el tipo de datos que se va a procesar (ENTERO o BOOLEANO) ya
que hay diferentes funciones de librería para la lectura (idem. escritura) de cada
tipo.
Se deben insertar en la pila los argumentos necesarios, realizar la llamada
(call) a la función de librería correspondiente y limpiar la pila.
*/
void leer(FILE* fpasm, char* nombre, int tipo){

  fprintf(fpasm,";leer\n");

  fprintf(fpasm,"\tpush dword _%s\n", nombre);

  if(tipo == ENTERO){
    fprintf(fpasm,"\tcall scan_int\n");
  }else{
    fprintf(fpasm,"\tcall scan_boolean\n");
  }
  fprintf(fpasm,"\tadd esp, 4\n");

}

void escribir(FILE* fpasm, int es_variable, int tipo){

  fprintf(fpasm,";escribir\n");

  fprintf(fpasm,"\tpop dword eax\n");
  if(es_variable){
    fprintf(fpasm,"\tmov dword eax, [eax]\n");
  }
  fprintf(fpasm,"\tpush dword eax\n");

  if(tipo == ENTERO){
    fprintf(fpasm,"\tcall print_int\n");
  }else{
    fprintf(fpasm,"\tcall print_boolean\n");
  }
  fprintf(fpasm,"\tadd esp, 4\n");
  fprintf(fpasm,"\tcall print_endofline\n");
}

void ifthenelse_inicio(FILE * fpasm, int exp_es_variable, int etiqueta){

  fprintf(fpasm,";ifthenelse_inicio\n");

  fprintf(fpasm,"\tpop dword eax\n");
  if(exp_es_variable){
    fprintf(fpasm,"\tmov dword eax, [eax]\n");
  }
  fprintf(fpasm,"\tcmp eax, 0\n");
  fprintf(fpasm,"\tje near _before_else%d\n", etiqueta); //if no se cumple

}

void ifthen_inicio(FILE * fpasm, int exp_es_variable, int etiqueta){

  fprintf(fpasm,";ifthen_inicio\n");

  fprintf(fpasm,"\tpop dword eax\n");
  if(exp_es_variable){
    fprintf(fpasm,"\tmov dword eax, [eax]\n");
  }
  fprintf(fpasm,"\tcmp eax, 0\n");
  fprintf(fpasm,"\tje near _if_not%d\n", etiqueta); //if no se cumple
}

void ifthen_fin(FILE * fpasm, int etiqueta){

  fprintf(fpasm,";ifthen_fin\n");

  fprintf(fpasm,"_if_not%d:\n", etiqueta);
}
void ifthenelse_fin_then( FILE * fpasm, int etiqueta){

  fprintf(fpasm,";ifthenelse_fin_then\n");

  fprintf(fpasm,"\tjmp near _after_else%d\n", etiqueta);
  fprintf(fpasm,"_before_else%d:\n", etiqueta);
  //se ha cumplido el if, y se ejecuta then pero no else
}
void ifthenelse_fin( FILE * fpasm, int etiqueta){

  fprintf(fpasm,";ifthenelse_fin\n");

  fprintf(fpasm,"_after_else%d:\n", etiqueta);
}
void while_inicio(FILE * fpasm, int etiqueta){

  fprintf(fpasm,";while_inicio\n");

  fprintf(fpasm,"_while_inicio%d:\n", etiqueta);

}
void while_exp_pila (FILE * fpasm, int exp_es_variable, int etiqueta){

  fprintf(fpasm,";while_exp_pila\n");

  fprintf(fpasm,"\tpop dword eax\n");
  if(exp_es_variable){
    fprintf(fpasm,"\tmov dword eax, [eax]\n");
  }
  fprintf(fpasm,"\tcmp eax, 0\n");
  fprintf(fpasm,"\tje near _while_fin%d\n", etiqueta);
}
void while_fin( FILE * fpasm, int etiqueta){

  fprintf(fpasm,";while_fin\n");

  fprintf(fpasm,"\tjmp near _while_inicio%d\n", etiqueta);
  fprintf(fpasm,"_while_fin%d:\n", etiqueta);
}
void escribir_elemento_vector(FILE * fpasm,char * nombre_vector, int tam_max, int exp_es_direccion){

  fprintf(fpasm,";escribir_elemento_vector\n");

  fprintf(fpasm,"\tpop dword eax\n");
  if(exp_es_direccion){
    fprintf(fpasm,"\tmov dword eax, [eax]\n");
  }
  fprintf(fpasm,"\tcmp eax, 0\n");
  fprintf(fpasm,"\tjl near error_indice_fuera_rango\n");
  fprintf(fpasm,"\tcmp eax, %d\n", tam_max);
  fprintf(fpasm,"\tjge near error_indice_fuera_rango\n");


}
void declararFuncion(FILE * fd_asm, char * nombre_funcion, int num_var_loc){

  fprintf(fd_asm,";declararFuncion\n");

  fprintf(fd_asm,"_%s:\n", nombre_funcion);
  fprintf(fd_asm,"\tpush ebp\n");
  fprintf(fd_asm,"\tmov ebp, esp\n");
  fprintf(fd_asm,"\tsub esp, 4*%d\n", num_var_loc);

}
void retornarFuncion(FILE * fd_asm, int es_variable){

  fprintf(fd_asm,";retornarFuncion\n");

  fprintf(fd_asm,"\tpop dword eax\n");
  if(es_variable){
    fprintf(fd_asm,"\tmov dword eax, [eax]\n");
  }
  fprintf(fd_asm,"\tmov esp, ebp\n");
  fprintf(fd_asm,"\tpop ebp\n");
  fprintf(fd_asm,"\tret\n");
}
void escribirParametro(FILE* fpasm, int pos_parametro, int num_total_parametros){

  int valor_a_sum;

  valor_a_sum = 4 * (1 + num_total_parametros - pos_parametro);

  fprintf(fpasm,";escribirParametro\n");

  fprintf(fpasm,"\tlea eax, [ebp + %d]\n", valor_a_sum);
  fprintf(fpasm,"\tpush dword eax\n");
}
void escribirVariableLocal(FILE* fpasm, int posicion_variable_local){

  int valor_a_res;

  valor_a_res = 4 * posicion_variable_local;

  fprintf(fpasm,";escribirVariableLocal\n");

  fprintf(fpasm,"\tlea eax, [ebp - %d]\n", valor_a_res);
  fprintf(fpasm,"\tpush dword eax\n");
}
void asignarDestinoEnPila(FILE* fpasm, int es_variable){

  fprintf(fpasm,";asignarDestinoEnPila\n");

  fprintf(fpasm,"\tpop dword ebx\n");
  fprintf(fpasm,"\tpop dword eax\n");
  if(es_variable){
    fprintf(fpasm,"\tmov dword eax, [eax]\n");
  }
  fprintf(fpasm,"\tmov dword [ebx], eax\n");


}
void operandoEnPilaAArgumento(FILE * fd_asm, int es_variable){

  fprintf(fd_asm,";operandoEnPilaAArgumento\n");

  if(es_variable){
    fprintf(fd_asm,"\tpop dword eax\n");
    fprintf(fd_asm,"\tmov dword eax, [eax]\n");
    fprintf(fd_asm,"\tpush dword eax\n");
  }
}
void limpiarPila(FILE * fd_asm, int num_argumentos){

  fprintf(fd_asm,";limpiarPila\n");

  fprintf(fd_asm,"\tadd esp, 4*%d\n", num_argumentos);
}
void llamarFuncion(FILE * fd_asm, char * nombre_funcion, int num_argumentos){

  fprintf(fd_asm,";llamarFuncion\n");

  fprintf(fd_asm,"\tcall %s\n", nombre_funcion);
  limpiarPila(fd_asm, num_argumentos);
  fprintf(fd_asm,"\tpush dword eax\n");
}
