CC = gcc -ansi -pedantic
CFLAGS = -Wall -g

all: pruebaMorfo.o lex.yy.o
	$(CC) $(CFLAGS) -o pruebaMorfo pruebaMorfo.o lex.yy.o
pruebaMorfo.o: pruebaMorfo.c tokens.h
	$(CC) $(CFLAGS) -c pruebaMorfo.c
lex.yy.o: lex.yy.c tokens.h
	$(CC) $(CFLAGS) -c lex.yy.c
lex.yy.c: alfa.l
	$flex alfa.l
clean:
	rm -rf pruebaMorfo  lex.yy.o pruebaMorfo.o
