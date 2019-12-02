#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tabla_hash.h"


INFO_SIMBOLO *crear_info_simbolo(const char *lexema, CATEGORIA categ, TIPO tipo, CLASE clase, int adic1, int adic2){

  INFO_SIMBOLO * info_sim;

  /* Reservamos memoria para info_sim */
  info_sim = (INFO_SIMBOLO *) malloc(sizeof(INFO_SIMBOLO));

  /* Control de errores de reserva de memoria de info_sim */
  if(!info_sim){
    printf("Error en la reserva de memoria de info_sim\n");
    return NULL;
  }

  /* Accedemos al lexema y lo duplicamos */
  info_sim->lexema = malloc (strlen(lexema)+1);

  /* Control de errores de reserva de memoria del lexema */
  if(!(info_sim->lexema)){
    printf("Error en la reserva de memoria del lexema de info_sim\n");
    return NULL;
  }

  /* Sobreescribimos el lexema */
  strcpy(info_sim->lexema, lexema);

  /* Control de errores de sobreescritura de memoria del lexema */
  if(!(info_sim->lexema)){
    printf("Error al sobreescribir el lexema de info_sim\n");
    return NULL;
  }

  /* Asignamos cada atributo con su campo correspondiente */
  info_sim->categoria = categ;
  info_sim->tipo = tipo;
  info_sim->clase = clase;
  info_sim->adicional1 = adic1;
  info_sim->adicional2 = adic2;

  return info_sim;
}

void liberar_info_simbolo(INFO_SIMBOLO *is){

  /* Si info_sim existe */
  if(is){
    /* Si el lexema existe, lo liberamos */
    if(is->lexema){
      /* Liberamos el lexema */
      free(is->lexema)
    }
    /* Liberamos info_sim */
    free(is);
  }

  return;
}

NODO_HASH *crear_nodo(INFO_SIMBOLO *is){

  /* Definimos un nodo nuevo */
  NODO_HASH nodo_hash;

  /* Reservamos memoria para el nodo hash */
  nodo_hash = (NODO_HASH *) malloc(sizeof(NODO_HASH));

  /* Control de errores de reserva de memoria de nodo_hash */
  if(!nodo_hash){
    printf("Error en la reserva de memoria de nodo_hash\n");
    return NULL;
  }

  /* Asignamos info_sim al nodo hash, y */
  nodo_hash->info = is;
  /* No existe un siguiente  */
  nodo_hash->siguiente = NULL;

  return nodo_hash;
}

void liberar_nodo(NODO_HASH *nh){

  /* Si nodo_hash existe */
  if(nh){
    /* liberamos llamando a la funcion de liberar_info_simbolo definida anteriormente */
    liberar_info_simbolo(nh->info);
    /* liberamos  nodo_hash*/
    free(nh);
  }

  return;

}

TABLA_HASH *crear_tabla(int tam){

  /* Creamos una tabla hash */
  TABLA_HASH *tabla_hash;

  /* Reservamos memoria para tabla_hash */
  tabla_hash = (TABLA_HASH *) malloc(sizeof(TABLA_HASH));

  /* Control de errores para la reserva de memoria de tabla_hash*/
  if(!tabla_hash){
    printf("Error al reservar memoria para la tabla hash\n");
    return NULL;
  }

  /* Reservamos memoria para la tabla con el tamano indicado */
  tabla_hash->tabla = (NODO_HASH**) malloc (tam*sizeof(NODO_HASH*))

  /* Control de errores en la reserva de memoria para la tabla*/
  if (!tabla_hash->tabla){
    printf("Error al reservar memoria para la tabla de la tabla hash\n");
    /*  Liberamos tabla_hash*/
    free(tabla_hash);
    return NULL;
  }

  /* Asignamos el tamaño a su campo correspondiente*/
  tabla_hash->tam = tam;

  return tabla_hash;
}

void liberar_tabla(TABLA_HASH *th){

  int contador = 0;
  int limite;
  NODO_HASH * nodo_aux;

  /* Comprobamos que la tabla exista */
  if(!th){
    printf("La tabla ya estaba liberada\n");
  }

  limite = th->tam;

  /* Para cada tabla*/
  if(th->tabla){
    while(contador < limite){

      /* Liberamos cada nodo de la tabla utilizando un nodo auxiliar*/
      while(th->tabla[contador]){

        nodo_aux = th->tabla[contador]->siguiente;
        liberar_nodo(th->tabla[contador]);
        th->tabla[contador] = nodo_aux;
      }

      contador++;
    }

    /* Liberamos el atributo de la tabla */
    free(th->tabla);
  }

  /* Liberamos tabla_hash*/
  free(th);

  return;
}


unsigned long hash(const char *str){

  /* Definimos el valor para aplicar el hash con la macro HASH_INI */
  unsigned long hash_ini = HASH_INI;

  unsigned char *aux;

  aux = (unsigned char *) str;

  /* Aplicamos la funcion hash basica */
  while(*aux){
    hash_ini = hash_ini*HASH_FACTOR + *aux;
    aux++;
  }

  return hash_ini;
}


INFO_SIMBOLO *buscar_simbolo(const TABLA_HASH *th, const char *lexema){

  NODO_HASH * nodo_aux;
  int indice;

  /* para calcular la posicion */
  indice = hash(lexema) % th->tam;

  for (nodo_aux = th->tabla[indice], nodo_aux && (!nodo_aux->info || strcmp(nodo_aux->info->lexema, lexema)), nodo_aux = nodo_aux->siguiente);

  /*Control de errores de el nodo auxiliar*/
  if(nodo_aux != NULL){
    return nodo_aux->info;
  }
  else {
    return NULL;
  }
}

STATUS insertar_simbolo(TABLA_HASH *th, const char *lexema, CATEGORIA categ, TIPO tipo, CLASE clase, int adic1, int adic2){

  int indice;
  INFO_SIMBOLO * info_sim;
  NODO_HASH * nodo_aux = NULL;




  /* Primero buscamos el simbolo */
  if(buscar_simbolo(th, lexema))
  {
      return ERR;
  }

  /* para calcular la posicion */
  indice = hash(lexema) % th->tam;

  /*Reservamos memoria para el nodo info_sim*/
  info_sim = crear_info_simbolo(lexema, categ, tipo, clase, adic1, adic2);

  /*Control de errores para info_sim*/
  if(info_sim == NULL){
      return ERR;
  }

  nodo_aux = crear_nodo(info_sim);

  /*Control de errores para el nodo_aux*/
  if (nodo_aux == NULL) {
      liberar_info_simbolo(info_sim);
      return ERR;
  }

  /*Insertamos el simbolo*/
  nodo_aux->siguiente = th->tabla[indice];
  th->tabla[indice] = nodo_aux;
  return OK;

}

void borrar_simbolo(TABLA_HASH *th, const char *lexema){

  NODO_HASH * nodo_aux;
  NODO_HASH * nodo_anterior = NULL;
  int indice;


  /* calculamos la posicion hash */
  indice = hash(lexema) % th->tam;

  /* Buscamos el nodo con esa posicion*/
  for(nodo_aux = th->tabla[indice], nodo_aux && (!nodo_aux->info || strcmp(nodo_aux->info->lexema, lexema)), nodo_aux = nodo_aux->siguiente){
    nodo_anterior = nodo_aux;
  }

  /* Control de errores, existencia del nodo */
  if(nodo_aux == NULL){
    return;
  }
  /* Control de errores, existencia del nodo anterior */
  if(nodo_anterior ==  NULL){
      /* borramos el primer nodo */
      th->tabla[indice] = nodo_aux->siguiente;
  }else{
      /* borramos cualquiero otro nodo */
      nodo_anterior->siguiente = nodo_aux->siguiente;
  }
  /*Liberamos finalmente el nodo*/
  liberar_nodo(nodo_aux);
  return;
}
