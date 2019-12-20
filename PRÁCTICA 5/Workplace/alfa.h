#ifndef _ALFA_H
#define _ALFA_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_TAM_VECTOR 64

#define MAX_LON_ID 100


typedef struct {

	char lexema[MAX_LON_ID+1];

	int tipo;

	int valor_entero;

	int es_direccion;

	int etiqueta;

} tipo_atributos;


#endif
