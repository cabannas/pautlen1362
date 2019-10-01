#include "nasm.h"

/* OBSERVACIÓN GENERAL:
   Todas las funciones escriben el código NASM al FILE* f
*/
FILE *f;

// Abre el fichero f con un nombre
void openFile(char* name){

  f = fopen(name, "w+");
  /*CdE*/
  if(!f){
    return;
  }
}

// Escribir cabecera de datos inicializados
void segmentData(){

  fprintf(f,"segment .data\n");
}

// Definir constante entera
// - No olvide anteponer "_" a name
void constInt(char* name, int value){

  fprintf(f,"\t_%s dd %d\n", name, value);
}

// Definir constante cadena de caracteres
// - No olvide anteponer "_" a name
void constString(char* name, char* value){

  fprintf(f,"\t_%s db \"%s\", 0\n", name, value);
}

// Escribir cabecera de datos no inicializados
// Por defecto se define __esp del apuntador a la pila
void segmentBss(){

  fprintf(f,"\n");
  fprintf(f,"segment .bss\n");
  fprintf(f,"\t__esp resd 1\n");
}

// Declarar variable entera
// - No olvide anteponer "_" a name
void variable(char* name, int size){

  fprintf(f,"\t_%s resd %d\n", name, size);
}

// Declarar segmento de código
// - Incluir  main
// - Incluir funciones de librería alfalib.o
void segmentText(){

  fprintf(f,"\n");
  fprintf(f,"segment .text\n");
  fprintf(f,"\tglobal main\n");
  fprintf(f,"\textern scan_int, print_int, scan_float, print_float, scan_boolean, print_boolean\n");
  fprintf(f,"\textern print_endofline, print_blank, print_string\n");
  fprintf(f,"\textern alfa_malloc, alfa_free, ld_float\n");
  fprintf(f,"\n");
}

// Iniciar programa
// - Guardar el puntero de la pila
void startProgram(){

  fprintf(f,"main:\n");
  fprintf(f,"\tmov dword [__esp], esp\n");
  fprintf(f,"\n");
}

// Escribir una instrucción NASM
void instruction(char* line){

  fprintf(f,"\t%s\n", line);
}

// Escribir n instrucciones NASM
// - n : número de líneas
// - lines: líneas de las instrucciones
// - Manejo de errores: (n fuera de rango)
void instructions(int n, char* lines[]){

  int i = 0;

  /*CdE*/
  if (n<=0){
    return;
  }

  for(i = 0; i < n; i++){
    fprintf(f,"\t%s\n", lines[i]);
  }
}


// Definir subrutina NASM
// - Manejo de errores: (n fuera de rango)
// - name: nombre de la función
// - n : número de líneas
// - lines: líneas de la subrutina
// - go: llama un call para saltar a una etiqueta.
//       Con NULL se ejecuta ret
void subrutine(char* name, int n, char* lines[], char* go){


  /*CdE*/
  if(n<=0){
    return;
  }

  fprintf(f,"%s:\n", name);

  instructions(n, lines);

  if(!go){
    fprintf(f,"\tret\n");
  }else{
    fprintf(f,"\tcall %s\n", go);
  }
  fprintf(f,"\n");
}

// Llamar a la función name
void call(char* name){

  fprintf(f,"\tcall %s\n", name);
}

// Implementación del condicional basado en ladefinición de variables
// - var1: variable 1
// - operation : operación (je, jne, jle, jge, jl, jg)
// - var2: variable 2
// - callThen: (verdadero) salto de subrutina por comparación
// - callElse: (falso) llamar subrutina después de la comparación
// - go: donde continua el programa
void IF(char* var1, char* oper, char* var2, char* callThen, char* callElse, char* go){

  fprintf(f,"\t;IF_STATEMENT\n");
  fprintf(f,"\tpush dword [_%s]\n", var1);
  fprintf(f,"\tpop eax\n");

  fprintf(f,"\tpush dword [_%s]\n", var2);
  fprintf(f,"\tpop ebx\n");

  fprintf(f,"\tcmp eax, ebx\n");
  fprintf(f,"\t%s %s\n", oper, callThen);

  fprintf(f,"\tcall %s\n", callElse);
  fprintf(f,"%s:\n", go);
}

// Capturar de teclado entero y string (type="int" o type="string")
void scan(char* type, char* var){

  fprintf(f,"\t;SCAN_FUNCTION\n");
  fprintf(f,"\tpush dword _%s\n", var);
  if(strcmp(type, "int")==0){
    fprintf(f, "\tcall scan_int\n");
  }
  else if(strcmp(type, "string")==0) {
    fprintf(f, "\tcall scan_string\n");
  }

  fprintf(f,"\tadd esp, 4\n");
  fprintf(f,"\tpush dword [_%s]\n", var);
  fprintf(f,"\n");
}

// Escribir por consola entero y string (type="int" o type="string")
void print(char* t, char* var){

  fprintf(f,"\t;PRINT_FUNCTION\n");
  fprintf(f,"\tpush dword %s\n", var);
  if(strcmp(t, "int")==0){
    fprintf(f, "\tcall print_int\n");
  }
  else if(strcmp(t, "string")==0) {
    fprintf(f, "\tcall print_string\n");
  }

  fprintf(f,"\tadd esp, 4\n");
  fprintf(f,"\tpush dword %s\n", var);
  fprintf(f,"\n");
}

// Terminación de programa NSAM
// Cierra el el fichero FILE* f
void quit(){
  fprintf(f,"quit:\n");
  fprintf(f,"\tmov dword esp, [__esp]\n");
  fprintf(f,"\tret\n");
}
