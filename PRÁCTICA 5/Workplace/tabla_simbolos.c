
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tabla_simbolos.h"


STATUS declarar_variable_local(FILE * fout, TABLA_HASH* tabla_local, char * id, CATEGORIA categoria, TIPO tipo, CLASE clase, int adicional1, int adicional2){

  /* verificamos que la variable a insertar no este en la tabla local */
  if(buscar_simbolo(tabla_local, id)==NULL){
    /* verificamos que la insercion se ha realizado de forma correcta */
    if(insertar_simbolo(tabla_local, id, categoria, tipo, clase, adicional1, adicional2)==ERR){
        return ERR;
    }
    /* al realizarse la insercion de forma correcta imprimimos el id */
    fprintf(fout, "%s\n", id);
    return OK;
  }
  /* al no realizarse de forma correcta, imprimimos -1 seguido del id */
  else{
    fprintf(fout, "-1 %s\n", id);
    return ERR;
  }
}

STATUS declarar_variable_global(FILE * fout, TABLA_HASH* tabla_global, char * id, CATEGORIA categoria, TIPO tipo, CLASE clase, int adicional1, int adicional2){

  /* verificamos que la variable a insertar no este en la tabla global */
  if(buscar_simbolo(tabla_global, id)==NULL) {
    /* verificamos que la insercion se ha realizado de forma correcta */
    if (insertar_simbolo(tabla_global, id, categoria, tipo, clase, adicional1, adicional2)==ERR) {
        return ERR;
    }
    /* al realizarse la insercion de forma correcta imprimimos el id */
    fprintf(fout, "%s\n", id);
    return OK;
  }
  else {
  /* al no realizarse de forma correcta, imprimimos -1 seguido del id */
    fprintf(fout, "-1 %s\n", id);
    return ERR;
  }
}

STATUS declarar_funcion(FILE * fout, TABLA_HASH* tabla_global, TABLA_HASH* tabla_local, char * id, CATEGORIA categoria, TIPO tipo, CLASE clase, int adicional1, int adicional2){

  /* verificamos que la variable a insertar no este en la tabla global */
  if (buscar_simbolo(tabla_global, id)!=NULL) {
    return ERR;
  }
  /* en caso de que no esté, insertamos la variable en la tabla global */
  else{
    if (insertar_simbolo(tabla_global, id, categoria, tipo, clase, adicional1, adicional2)==ERR) {
      /* en caso de error de insercion*/
      fprintf(fout, "-1 %s\n", id);
      return ERR;
    }
    /* abrimos un nuevo ambito */
    /* también insertamos la variable en la tabla local */
    if (insertar_simbolo(tabla_local, id, categoria, tipo, clase, adicional1, adicional2)==ERR) {
      /* en caso de error de insercion*/
      fprintf(fout, "-1 %s\n", id);
      return ERR;
    }

    /* Tras haber pasado todos los controles de errores, podemos declarar esa funcion*/
    fprintf(fout, "%s\n", id);
    return OK;
  }
}

INFO_SIMBOLO* busqueda_global(char * lex, TABLA_HASH *tabla_global){

  INFO_SIMBOLO * valor = NULL;

  /*CdE*/
  if(!tabla_global){
    return NULL;
  }

  /* Buscamos el lexema en la tabla global unicamente */
  valor = buscar_simbolo(tabla_global, lex);

   return valor;
}

INFO_SIMBOLO* busqueda_local(char * lexema, TABLA_HASH *tabla_global, TABLA_HASH *tabla_local){

  INFO_SIMBOLO * valor = NULL;

  /*CdE*/
  if(!tabla_global || !tabla_local){
    return NULL;
  }

  /* Buscamos el lexema en la tabla local */
  valor = buscar_simbolo(tabla_local, lex);

  /* Si no existe lo buscamos en la tabla global*/
  if(!valor){
    valor = buscar_simbolo(tabla_global, lex);
  }

  return valor;
}
