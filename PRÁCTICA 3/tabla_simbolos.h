#ifndef TABLA_SIMBOLOS_H
#define TABLA_SIMBOLOS_H

#include "tabla_hash.h"

#define TAM_TABLA_MAX 1000

typedef enum {
    GLOBAL = 0,
    LOCAL
}AMBITO;

/* Declara una variable en el ambito local*/
STATUS declarar_variable_local(FILE * fout, TABLA_HASH* tabla_local, char * id, CATEGORIA categoria, TIPO tipo, CLASE clase, int adicional1, int adicional2);

/* Declara una variable en el ambito global*/
STATUS declarar_variable_global(FILE * fout, TABLA_HASH* tabla_global, char * id, CATEGORIA categoria, TIPO tipo, CLASE clase, int adicional1, int adicional2);

/* Declara una funcion en el ambito global*/
STATUS declarar_funcion(FILE * fout, TABLA_HASH* tabla_global, TABLA_HASH* tabla_local, char * id, CATEGORIA categoria, TIPO tipo, CLASE clase, int adicional1, int adicional2);

/* Informa sobre el estado de la busqueda de una función*/
STATUS exito_busqueda(TABLA_HASH *tabla_global, TABLA_HASH *tabla_local, char* id, FILE * fout);

#endif
