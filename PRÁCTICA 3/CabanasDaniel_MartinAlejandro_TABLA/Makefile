all: prueba_tabla

prueba_tabla: prueba_tabla.o tabla_hash.o tabla_simbolos.o
	gcc -o prueba_tabla  prueba_tabla.o tabla_hash.o tabla_simbolos.o

prueba_tabla.o: prueba_tabla.c tabla_hash.h tabla_simbolos.h
	gcc -c prueba_tabla.c

tabla_hash.o: tabla_hash.c tabla_hash.h
	gcc -c tabla_hash.c

tabla_simbolos.o: tabla_simbolos.c tabla_simbolos.h tabla_hash.h
	gcc -c tabla_simbolos.c

run: prueba_tabla
	./prueba_tabla

clean:
	rm *.o prueba_tabla
