%{
  #include <stdio.h>

%}
%option noyywrap
%%
INICIO { printf("-> INICIO\n"); }
FIN { printf("-> FIN\n"); }
VECTOR { printf("-> VECTOR\n"); }
ENTERO { printf("-> ENTERO\n"); }
LOGICO { printf("-> LOGICO\n"); }
"+" {printf("-> SUMA\n");}
DANI { printf("-> EL MAS GUAY\n"); }
ALEX { printf("-> EL PUTO KA A ESE PUNTO O\n"); }
%%
int main() {
return yylex();
}
