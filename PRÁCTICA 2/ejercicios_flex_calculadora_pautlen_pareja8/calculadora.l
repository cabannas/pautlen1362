
%{
#include <math.h>

int a[50], res;
int operando;
int num_elem;


%}

%option noyywrap

/* Rules Section */
DIGIT [0-9]

%%
{DIGIT}{DIGIT}* { a[num_elem] = atoi(yytext); num_elem++;}
"+" { operando = 0;}
"-" { operando = 1;}
"*" { operando = 2;}
"/" { operando = 3;}
"^" { operando = 4;}


"\n"  {
switch(operando){
case(0):
  res = a[0]+a[1];
  break;
case(1):
  res = a[0]-a[1];
  break;
case(2):
  res = a[0]*a[1];
  break;
case(3):
  res = a[0]/a[1];
  break;
case(4):
  res = 1;
  for (int i=0;i<a[1];i++){
  res = res * a[0];
  }
  break;
}

printf("Result ==> %d\n", res);
num_elem = 0;
}

%%

int main()
{
  yylex();
  return 0;
}
