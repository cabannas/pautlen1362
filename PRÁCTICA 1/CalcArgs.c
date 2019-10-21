#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void imprimirCabeceras(FILE *fp, int operando_1, int operando_2){

  fprintf(fp,"segment .data\n");
  fprintf(fp,"\t_label_menu db \"Menú: [1] Suma. [2] Multilpicación. [3] Parte entera de una división. [4] Salir.\", 0\n");
  fprintf(fp,"\t_label_choice db \"Su opción: \", 0\n");
  fprintf(fp,"\t_process1 db \"Procesando suma ... \", 0\n");
  fprintf(fp,"\t_process2 db \"Procesando multiplicación ...\", 0\n");
  fprintf(fp,"\t_process3 db \"Procesando división ...\", 0\n");
  fprintf(fp,"\t_sumares db \"El resultado de la suma es: \", 0\n");
  fprintf(fp,"\t_multres db \"El resultado de la multiplicación es: \", 0\n");
  fprintf(fp,"\t_divres db \"El resultado entero de la división es: \", 0\n");
  fprintf(fp,"\t_simbsuma db \" + \", 0\n");
  fprintf(fp,"\t_simbmult db \" * \", 0\n");
  fprintf(fp,"\t_simbdiv db \" / \", 0\n");
  fprintf(fp,"\t_simbigual db \" = \", 0\n");
  fprintf(fp,"\n");

  fprintf(fp,"\t_x dd %d\n", operando_1);
  fprintf(fp,"\t_y dd %d\n", operando_2);
  fprintf(fp,"\n");

  fprintf(fp,"segment .bss\n");
  fprintf(fp,"\t__esp    resd 1\n");
  fprintf(fp,"\t_option  resd 1\n");
  fprintf(fp,"\t_z resd 1\n");
  fprintf(fp,"\n");

  fprintf(fp,"segment .text\n");
  fprintf(fp,"\tglobal main\n");
  fprintf(fp,"\textern print_string, print_endofline, scan_int, print_int\n");
  fprintf(fp,"\n");

  fprintf(fp,"main:\n");
  fprintf(fp,"\tmov dword [__esp], esp\n");
  fprintf(fp,"\n");
}

void imprimirMenu(FILE *fp){

  fprintf(fp,"menu:\n");
  fprintf(fp,"\t;Mostrar menú\n");
  fprintf(fp,"\tpush dword _label_menu\n");
  fprintf(fp,"\tcall print_string\n");
  fprintf(fp,"\tadd esp, 4\n");
  fprintf(fp,"\tcall print_endofline\n");
  fprintf(fp,"\n");

  fprintf(fp,"\t;Elegir opción\n");
  fprintf(fp,"\tpush dword _label_choice\n");
  fprintf(fp,"\tcall print_string\n");
  fprintf(fp,"\tadd esp, 4\n");
  fprintf(fp,"\tpush dword _option\n");
  fprintf(fp,"\tcall scan_int\n");
  fprintf(fp,"\tadd esp, 4\n");
  fprintf(fp,"\tpush dword [_option]\n");
  fprintf(fp,"\n");

  fprintf(fp,"\t;Ejecutar opción de menú\n");
  fprintf(fp,"\tpop eax\n");
  fprintf(fp,"\tcmp eax, 1\n");
  fprintf(fp,"\tje suma\n");
  fprintf(fp,"\tcmp eax, 2\n");
  fprintf(fp,"\tje multiplicacion\n");
  fprintf(fp,"\tcmp eax,3\n");
  fprintf(fp,"\tje division\n");
  fprintf(fp,"\tcmp eax, 4\n");
  fprintf(fp,"\tje salir\n");
  fprintf(fp,"\tcall menu\n");
  fprintf(fp,"\n");
}

void imprimeSuma(FILE *fp){

  fprintf(fp,"suma:\n");
  fprintf(fp,"\tmov eax, [_x]\n");
  fprintf(fp,"\tmov edx, [_y]\n");
  fprintf(fp,"\tadd eax, edx\n");
  fprintf(fp,"\tmov [_z], eax\n");
  fprintf(fp,"\n");

  fprintf(fp,"\tpush dword _sumares\n");
  fprintf(fp,"\tcall print_string\n");
  fprintf(fp,"\tadd esp, 4\n");
  fprintf(fp,"\tpush dword [_x]\n");
  fprintf(fp,"\tcall print_int\n");
  fprintf(fp,"\tadd esp, 4\n");
  fprintf(fp,"\tpush dword _simbsuma\n");
  fprintf(fp,"\tcall print_string\n");
  fprintf(fp,"\tadd esp, 4\n");
  fprintf(fp,"\tpush dword [_y]\n");
  fprintf(fp,"\tcall print_int\n");
  fprintf(fp,"\tadd esp, 4\n");
  fprintf(fp,"\tpush dword _simbigual\n");
  fprintf(fp,"\tcall print_string\n");
  fprintf(fp,"\tadd esp, 4\n");
  fprintf(fp,"\tpush dword [_z]\n");
  fprintf(fp,"\tcall print_int\n");
  fprintf(fp,"\tadd esp, 4\n");
  fprintf(fp,"\n");

  fprintf(fp,"\tcall print_endofline\n");
  fprintf(fp,"\tcall menu\n");
  fprintf(fp,"\n");
}

void imprimeMultiplicacion(FILE *fp){

  fprintf(fp,"multiplicacion:\n");
  fprintf(fp,"\tmov eax, [_x]\n");
  fprintf(fp,"\tmov edx, [_y]\n");
  fprintf(fp,"\timul edx\n");
  fprintf(fp,"\tmov [_z], eax\n");
  fprintf(fp,"\n");

  fprintf(fp,"\tpush dword _multres\n");
  fprintf(fp,"\tcall print_string\n");
  fprintf(fp,"\tadd esp, 4\n");
  fprintf(fp,"\tpush dword [_x]\n");
  fprintf(fp,"\tcall print_int\n");
  fprintf(fp,"\tadd esp, 4\n");
  fprintf(fp,"\tpush dword _simbmult\n");
  fprintf(fp,"\tcall print_string\n");
  fprintf(fp,"\tadd esp, 4\n");
  fprintf(fp,"\tpush dword [_y]\n");
  fprintf(fp,"\tcall print_int\n");
  fprintf(fp,"\tadd esp, 4\n");
  fprintf(fp,"\tpush dword _simbigual\n");
  fprintf(fp,"\tcall print_string\n");
  fprintf(fp,"\tadd esp, 4\n");
  fprintf(fp,"\tpush dword [_z]\n");
  fprintf(fp,"\tcall print_int\n");
  fprintf(fp,"\tadd esp, 4\n");
  fprintf(fp,"\n");

  fprintf(fp,"\tcall print_endofline\n");
  fprintf(fp,"\tcall menu\n");
  fprintf(fp,"\n");
}

void imprimeDivision(FILE *fp){

  fprintf(fp,"division:\n");
  fprintf(fp,"\tmov edx, 0\n");
  fprintf(fp,"\tmov eax, [_x]\n");
  fprintf(fp,"\tmov ecx, [_y]\n");
  fprintf(fp,"\tidiv ecx\n");
  fprintf(fp,"\tmov [_z], eax\n");
  fprintf(fp,"\n");

  fprintf(fp,"\tpush dword _divres\n");
  fprintf(fp,"\tcall print_string\n");
  fprintf(fp,"\tadd esp, 4\n");
  fprintf(fp,"\tpush dword [_x]\n");
  fprintf(fp,"\tcall print_int\n");
  fprintf(fp,"\tadd esp, 4\n");
  fprintf(fp,"\tpush dword _simbdiv\n");
  fprintf(fp,"\tcall print_string\n");
  fprintf(fp,"\tadd esp, 4\n");
  fprintf(fp,"\tpush dword [_y]\n");
  fprintf(fp,"\tcall print_int\n");
  fprintf(fp,"\tadd esp, 4\n");
  fprintf(fp,"\tpush dword _simbigual\n");
  fprintf(fp,"\tcall print_string\n");
  fprintf(fp,"\tadd esp, 4\n");
  fprintf(fp,"\tpush dword [_z]\n");
  fprintf(fp,"\tcall print_int\n");
  fprintf(fp,"\tadd esp, 4\n");
  fprintf(fp,"\n");

  fprintf(fp,"\tcall print_endofline\n");
  fprintf(fp,"\tcall menu\n");
  fprintf(fp,"\n");
}

void imprimeSalir(FILE *fp){

  fprintf(fp,"salir:\n");
  fprintf(fp,"\tmov dword esp, [__esp]\n");
  fprintf(fp,"\tret\n");
  fprintf(fp,"\n");
}

void calculadoraNASM (FILE *fp, int operando_1, int operando_2){

  imprimirCabeceras(fp, operando_1, operando_2);
  imprimirMenu(fp);
  imprimeSuma(fp);
  imprimeMultiplicacion(fp);
  imprimeDivision(fp);
  imprimeSalir(fp);

}

int main(int argc, char *argv[]){

  FILE * fp;
  int op1 = 0, op2 = 0;

  char *name = argv[1];
  char *end = ".asm";
  char fullname[80] = "";

  strcat(fullname, name);
  strcat(fullname, end);

  fp = fopen(fullname, "w+");

  op1 = atoi(argv[2]);
  op2 = atoi(argv[3]);



  calculadoraNASM(fp, op1, op2);

  fclose(fp);

  return 0;
}
