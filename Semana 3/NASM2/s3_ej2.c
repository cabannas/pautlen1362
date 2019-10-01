#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "nasm.h"

int main(int argc, char **argv) {
	openFile("s3_ej2.asm");

    segmentData();    
	segmentBss(); 
    segmentText();

	// Programa suma
	startProgram();
	char *lines[] = {
	 	"mov eax, 2", 
		"mov ebx, 3",
		"add eax, ebx"
	};
	instructions(3, lines);
	print("int", "eax");
    quit();

	/*Salida de consola:
	5
	*/
}
	