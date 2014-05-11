%{
	#include "Ficheros.c"
	#include <stdio.h>
	void yyerror (char const *);
	extern FILE *yyin;

	
%}
%union{
	int valInt;
	char *valChar;
}
%error-verbose
%token <valChar> STRING
%start S
%%
S : empleados
	;

empleados : STRING
	;
	
%%
int main(){
	yyparse();
	return 0;
}
void yyerror (char const *message) { 
	fprintf (stderr,"%s\n", message);
}
