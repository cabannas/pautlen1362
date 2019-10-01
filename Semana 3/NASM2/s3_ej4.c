#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "nasm.h"

int main(int argc, char **argv) {
	openFile("s3_ej4.asm");

  segmentData();
	segmentBss();
	variable("x", 1);
  variable("y", 1);
	variable("z", 1);

  segmentText();
	// Creación de la subrutina then
	char *linesThen[] = {
	 	"mov dword [_z], 1"
	};
	subrutine("then", 1, linesThen, "continue");

	// Creación de la subrutina else
	char *linesElse[] = {
	 	"mov dword [_z], 2"
	};
	subrutine("else", 1, linesElse, "continue");

	// Programa uso de condicional
	// if (x>=y) z = 1;
	// else z=2;
	startProgram();
	scan("int", "x");
	scan("int", "y");
	IF("x", "jge", "y", "then", "else", "continue");
	print("int", "[_z]");
    quit();

	/*Salida de consola:
	3  <- entrada de teclado var x
	4  <- entrada de teclado var y
    2
	*/
}
