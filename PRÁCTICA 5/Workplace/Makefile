all: clean alfa

y.tab.c:
	bison -dy alfa.y

lex.yy.c:
	flex alfa.l

alfa: lex.yy.c y.tab.c
	gcc -Wall -o alfa *.c

nasm:
	nasm -g -o generacionNasm.o -f elf32 generacionNasm.asm
	gcc -m32 -o generacionNasm generacionNasm.o alfalib.o

clean:
	rm -f alfa *~ core *.yy.* *.tab.* y.output generacionNasm*.* generacionNasm
