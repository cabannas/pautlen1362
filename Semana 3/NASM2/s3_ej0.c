#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "nasm.h"

int main(int argc, char **argv) {
	openFile("s3_ej0.asm");

    segmentData();    
	constString("msg","Hello world!!"); 
	segmentBss();    //Es obligatorio
    segmentText(); //Es obligatorio
	startProgram();
	print("string","_msg");
    quit();

	/*Salida de consola:
	Hello world!!
	*/
}
	