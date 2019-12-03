
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

STATUS exito_busqueda(TABLA_HASH *tabla_global, TABLA_HASH *tabla_local, char* id, FILE * fout){

  INFO_SIMBOLO* info_sim=NULL;
  int control=1;
  int categ=0;

  /* buscamos el simbolo y guardamos el simbolo en una variable*/
  info_sim = buscar_simbolo(tabla_global, id);

  /* Si el simbolo no esta en la tabla global */
  if (info_sim==NULL) {
    control=0;
    /*si existe tabla local*/
    if (tabla_local != NULL) {
      /* buscamos en la tabla local */
      info_sim = buscar_simbolo(tabla_local, id);
      if (info_sim != NULL) {
        /* si esta en la variable*/
        control = 1;
      }
    }
  }

  /* Si no existe la variable en ningun ambito */
  if (control==0) {
    fprintf(fout, "%s -1\n", id);
    return OK;
  }

  /* Si existe la variable en algun ambito*/
  categ = info_sim->categoria;
  /* si la variable es una variable */
  if (categ==VARIABLE) {
    fprintf(fout, "%s %d\n", id, info_sim->adicional1);
    return OK;
  }

  /* si la variable es una funcion */
  else if (categ==FUNCION) {
    fprintf(fout, "%s -10\n", id);
    return OK;
  }

  return ERR;


}
