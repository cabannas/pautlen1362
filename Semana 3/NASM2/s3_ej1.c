#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "nasm.h"

int main(int argc, char **argv) {
	openFile("s3_ej1.asm");

    segmentData();    
	constInt("x", 5);
	
	segmentBss(); 
	variable("y", 1);

    segmentText();

	//Programa resta
	startProgram();
	scan("int", "y");
	instruction("mov eax, [_x]");
	instruction("mov edx, [_y]");
	instruction("sub eax, edx");
	print("int", "eax");
    quit();

	/*Salida de consola:
	3  <- entrada de teclado
    2
	*/
}
	