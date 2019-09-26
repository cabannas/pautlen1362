#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int main(int argc, char *argv[]){

  FILE * fp;
  int op1 = 0, op2 = 0;

  fp = fopen(argv[1], "r+");

  op1 = atoi(argv[2]);
  op2 = atoi(argv[3]);

 //fseek(fp, 0, SEEK_END);

  fseek(fp, 545, SEEK_SET);
  fprintf(fp, "\t_x dd %d\n", op1);
  fprintf(fp, "\t_y dd %d\n", op2);
  fprintf(fp, "\n");


//  printf("%ld", ftell(fp));


  fclose(fp);

  return 0;
}
