#ifndef NASM_H
#define NASM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* OBSERVACIÓN GENERAL:
   Todas las funciones escriben el código NASM al FILE* f
*/
FILE *f;

// Abre el fichero f con un nombre
void openFile(char* name);

// Escribir cabecera de datos inicializados
void segmentData();

// Definir constante entera
// - No olvide anteponer "_" a name
void constInt(char* name, int value);

// Definir constante cadena de caracteres
// - No olvide anteponer "_" a name
void constString(char* name, char* value);

// Escribir cabecera de datos no inicializados
// Por defecto se define __esp del apuntador a la pila
void segmentBss();

// Declarar variable entera
// - No olvide anteponer "_" a name
void variable(char* name, int size);

// Declarar segmento de código
// - Incluir  main
// - Incluir funciones de librería alfalib.o
void segmentText();

// Iniciar programa
// - Guardar el puntero de la pila
void startProgram();

// Escribir una instrucción NASM
void instruction(char* line);

// Escribir n instrucciones NASM
// - n : número de líneas
// - lines: líneas de las instrucciones
// - Manejo de errores: (n fuera de rango)
void instructions(int n, char* lines[]);


// Definir subrutina NASM
// - Manejo de errores: (n fuera de rango)
// - name: nombre de la función
// - n : número de líneas
// - lines: líneas de la subrutina
// - go: llama un call para saltar a una etiqueta.
//       Con NULL se ejecuta ret 
void subrutine(char* name, int n, char* lines[], char* go);

// Llamar a la función name
void call(char* name);

// Implementación del condicional basado en ladefinición de variables 
// - var1: variable 1
// - operation : operación (je, jne, jle, jge, jl, jg)
// - var2: variable 2
// - callThen: (verdadero) salto de subrutina por comparación
// - callElse: (falso) llamar subrutina después de la comparación
// - go: donde continua el programa 
void IF(char* var1, char* oper, char* var2, char* callThen, char* callElse, char* go);

// Capturar de teclado entero y string (type="int" o type="string")
void scan(char* type, char* var);

// Escribir por consola entero y string (type="int" o type="string")
void print(char* t, char* var);

// Terminación de programa NSAM
// Cierra el el fichero FILE* f
void quit();

#endif