EXE=alfa
DELETE = *~ core *.yy.* *.tab.* y.output generacionNasm*.*
NASM = nasm
EXE_NASM = generacionNasm

all: clean $(EXE)

y.tab.c:
	bison -dy alfa.y

lex.yy.c:		
	flex alfa.l

$(EXE): lex.yy.c y.tab.c 
	gcc -Wall -o alfa *.c

$(NASM):
	$(NASM) -g -o $(EXE_NASM).o -f elf32 $(EXE_NASM).asm
	gcc -m32 -o $(EXE_NASM) $(EXE_NASM).o alfalib.o

clean:
	rm -f $(EXE) $(DELETE) $(EXE_NASM)
