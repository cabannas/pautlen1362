#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "nasm.h"

int main(int argc, char **argv) {
	openFile("s3_ej3.asm");

    segmentData();    
	segmentBss(); 
	variable("x", 1);
    variable("y", 1);
	variable("z", 1);

    segmentText();
	// Creación de la función multi
	char *lines[] = {
	 	"mov eax, [_x]", 
		"mov ebx, [_y]",
		"mul ebx"
	};
	subrutine("multi", 3, lines, NULL);
	
	// Programa multiplicación
	startProgram();
	scan("int", "x");
	scan("int", "y");
	call("multi");
	print("int", "eax");
    quit();

	/*Salida de consola:
	4  <- entrada de teclado var x
	7  <- entrada de teclado var y
    28
	*/
}
	