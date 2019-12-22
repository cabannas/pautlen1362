#include <stdlib.h>
#include <string.h>
#include "tablaSimbolos.h"


/*-------------- DECLARAR VARIABLE LOCAL ---------------*/

/*
PARAMETROS
id = nombre de la variable
adic2 no se utiliza en esta practica, pero lo dejamos preparado para las siguientes

Hemos supuesto que una variable local puede llamarse igual que una variable global ya que son pertenecientes a distintos ambitos

 */
STATUS DeclararVariableLocal(TABLA_HASH* tablaLocal, char * id, CATEGORIA categoria, TIPO tipo, CLASE clase, int adic1, int adic2) {
    if (buscar_simbolo(tablaLocal, id) == NULL) {
        if (insertar_simbolo(tablaLocal, id, categoria, tipo, clase, adic1, adic2) == ERR) {
            return ERR;
        }

        return OK;
    } else {
        return ERR;
    }
}


/*-------------- DECLARAR VARIABLE GLOBAL --------------*/

/*
PARAMETROS
id = nombre de la variable
adic2 no se utiliza en esta practica, pero lo dejamos preparado para las siguientes
 */
STATUS DeclararVariableGlobal(TABLA_HASH* tablaGlobal, char * id, CATEGORIA categoria, TIPO tipo, CLASE clase, int adic1, int adic2) {
    printf("%s\n", id);
    if (buscar_simbolo(tablaGlobal, id) == NULL) { 
        if (insertar_simbolo(tablaGlobal, id, categoria, tipo, clase, adic1, adic2) == ERR) {
            return ERR;
        }
        return OK;
    } else {
        return ERR;
    }
}

/*-------------- DECLARAR FUNCION --------------*/

/*
PARAMETROS
id = nombre de la variable
adic2 no se utiliza en esta practica, pero lo dejamos preparado para las siguientes
 */

STATUS DeclararFuncion(TABLA_HASH* tablaGlobal, TABLA_HASH* tablaLocal, char * id, CATEGORIA categoria, TIPO tipo, CLASE clase, int adic1, int adic2) {
    if (buscar_simbolo(tablaGlobal, id) != NULL) { /*Buscamos que la funcion no este declarada en la tabla global*/
        return ERR;
    } else { 
        if (insertar_simbolo(tablaGlobal, id, categoria, tipo, clase, adic1, adic2) == ERR) {
            return ERR;
        }
        liberar_tabla(tablaLocal);
        tablaLocal = crear_tabla(TAM_TABLA_MAX);
        if (insertar_simbolo(tablaLocal, id, categoria, tipo, clase, adic1, adic2) == ERR) {
            return ERR;
        }
        return OK;
    }
}

/************BUSQUEDA GLOBAL Y LOCAL***********/
INFO_SIMBOLO* busquedaGlobal(char * lexema, TABLA_HASH *tablaGlobal) {
    INFO_SIMBOLO* dato = NULL;
    dato = buscar_simbolo(tablaGlobal, lexema);
    return dato;
}
INFO_SIMBOLO* busquedaLocal(char * lexema, TABLA_HASH *tablaGlobal, TABLA_HASH *tablaLocal) {
    INFO_SIMBOLO* dato = NULL;
    dato = buscar_simbolo(tablaLocal, lexema);
    if (dato == NULL) {
        dato = buscar_simbolo(tablaGlobal, lexema);
	}
    return dato;
}







