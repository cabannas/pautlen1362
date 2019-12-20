#ifndef _ALFA_H
#define _ALFA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*#define TOK_ERROR -1
#define ESCALAR 1
#define VECTOR 2
#define INT 1
#define BOOLEAN 2*/

#define MAX_LONG_ID 100
#define MAX_TAMANIO_VECTOR 64

typedef struct {
	char lexema[MAX_LONG_ID+1];
	int tipo;
	int valor_entero;
	int es_direccion;
	int etiqueta;
} tipo_atributos;


#endif
