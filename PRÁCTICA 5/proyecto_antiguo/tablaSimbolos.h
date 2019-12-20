#ifndef TABLASIMBOLOS_H
#define ABLASIMBOLOS_H
#include "tablaHash.h"

#define TAM_TABLA_MAX 1000

typedef enum {
    GLOBAL = 0,
    LOCAL
} AMBITO;

STATUS DeclararVariableLocal(TABLA_HASH* tablaLocal, char * id, CATEGORIA categoria, TIPO tipo, CLASE clase, int adic1, int adic2);
STATUS DeclararVariableGlobal(TABLA_HASH* tablaGlobal, char * id, CATEGORIA categoria, TIPO tipo, CLASE clase, int adic1, int adic2);
STATUS DeclararFuncion(TABLA_HASH* tablaGlobal, TABLA_HASH* tablaLocal, char * id, CATEGORIA categoria, TIPO tipo, CLASE clase, int adic1, int adic2);

/***** P4 *****/
INFO_SIMBOLO* busquedaGlobal(char * lexema, TABLA_HASH *tablaGlobal);
INFO_SIMBOLO* busquedaLocal(char * lexema, TABLA_HASH *tablaGlobal, TABLA_HASH *tablaLocal);

#endif


