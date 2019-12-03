#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tabla_simbolos.h"

#define TAM_MAX_CADENA 200
#define NUM_DATOS 2

int main(int argc, char *argv[]) {

  /* Ambito actual */
  AMBITO ambito;

  /* ficheros de entrada y salida */
  FILE *f_in;
  FILE *f_out;

  /* para guardar los dos datos de cada linea del fichero */
  char cadena[TAM_MAX_CADENA];
  char *datos[NUM_DATOS];
  int valor;

  /* Creamos las dos tablas, local y global */
  TABLA_HASH * tabla_global = NULL;
  TABLA_HASH * tabla_local = NULL;

  /* Control de errores en la entrada de argumentos */
  if (argc != 3) {
    printf("Introduzca el nombre de los 2 ficheros, uno de entrada y otro de salida.\n");
    return 1;
  }

  /* Establecemos los ficheros a partir de los argumentos de entrada */
  f_in = fopen(argv[1], "r");
  f_out = fopen(argv[2], "w");

  /* abrimos ambito global */
  tabla_global = crear_tabla(TAM_MAX_TABLA);
  ambito = GLOBAL;

  /* leemos el fichero hasta que termine (end of file) */
  while (feof(f_in)==0) {

    /* leemos una linea, con control de errores */
    if (fgets(cadena, TAM_MAX_CADENA - 1, f_in) == NULL){
      return -1;
    }

    /* ignoramos saltos de linea */
    if (strcmp(cadena, "\n") == 0) {
        continue;
    }

    /* asignamos cada elemento de la linea a su correspondiente dato en el fichero */
    datos[0] = strtok(cadena, "\t\n ");
    datos[1] = strtok(NULL, "\t\n ");

    /* si no existe un segundo elemento es una busqueda */
    if (datos[1] == NULL) {
        datos[0] = strtok(datos[0], "\n");

        /* imprimimos en el fichero el resultado de la busqueda*/
        exito_busqueda(tabla_global, tabla_local, datos[0], f_out);
    }
    else
    {

      /* convertimos a int el primer dato de la linea*/
      valor = atoi(datos[1]);

      /* insercion de variable en el ambito actual */
      if (valor >= 0)
      {
        /* si el ambito esta en global, quiere decir que unicamente esta abierto el global, no el local */
        if(ambito == GLOBAL)
        {
          declarar_variable_global(f_out, tabla_global, datos[0], VARIABLE, ENTERO, ESCALAR, valor, 0);
        }
        /* si el ambito está en local, quiere decir que los ámbitos abierto son el global y el local */
        else if (ambito == LOCAL) {
          declarar_variable_local(f_out, tabla_local, datos[0], VARIABLE, ENTERO, ESCALAR, valor, 0);
        }
      }
      else if (valor < 0) {
        if (strcmp(datos[0], "cierre") == 0 && valor == -999) {
          /* reabrimos el ambito global (cerrando el local) */
          ambito = GLOBAL;
          fprintf(f_out, "cierre\n");
          liberar_tabla(tabla_local);
          tabla_local = NULL;
        }

        /* insertar funcion */
        else {
          /* volvemos al ambito global (cerrando de nuevo el local)*/
          if (ambito == GLOBAL) {

            /* creamos la tabla del nuevo ambito*/
            tabla_local = crear_tabla(TAM_MAX_TABLA);
            /* volvemos al ambito local*/
            ambito = LOCAL;
          }
          /* declaramos la funcion */
          declarar_funcion(f_out, tabla_global, tabla_local, datos[0], FUNCION, ENTERO, ESCALAR, valor, 0);
        }
      }
    }
  }

  /* cierre de los ficheros de entrada y salida */
  fclose(f_in);
  fclose(f_out);

  /*liberacion de recursos */
  liberar_tabla(tabla_global);

  return 0;
}
