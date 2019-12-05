all: pruebaSintactico
pruebaSintactico: pruebaSintactico.o lex.yy.o y.tab.o
	gcc -o pruebaSintactico pruebaSintactico.o lex.yy.o y.tab.o
lex.yy.o: lex.yy.c
	gcc -c lex.yy.c
lex.yy.c: alfa.l
	$flex alfa.l
y.tab.o: y.tab.c
	gcc -c y.tab.c
y.tab.h: alfa.y
	$ bison -d -y -v alfa.y
pruebaSintactico.o: pruebaSintactico.c y.tab.h
	gcc -c pruebaSintactico.c

clean:
	rm pruebaSintactico  lex.yy.o pruebaSintactico.o y.tab.o y.tab.c y.output y.tab.h lex.yy.c
