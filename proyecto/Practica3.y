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
%token <valChar> PUBLIC
%token <valChar> PRIVATE
%token <valChar> PROTECTED
%token <valChar> CLASS
%token <valChar> LLAVE_A
%token <valChar> PACKAGE
%token <valChar> IMPORT
%type <valChar> m_visibilidad
%start S
%%
S : package imports clase atributos metodos '}' 
	| package imports clase metodos '}'
	| package imports clase atributos '}'{printf("}\n");}
	;

package: PACKAGE STRING ';';

m_visibilidad: PUBLIC {$$="public";}
	| PRIVATE {$$="private";}
	| PROTECTED {$$="protected";}
	| /*Default*/ {$$="default";}
	;

imports: IMPORT STRING ';'
	| 
	;

clase : m_visibilidad CLASS STRING '{' {printf("%s class %s {\n",$1,$3);}
	;
	
atributo: m_visibilidad STRING STRING ';' {printf("%s %s %s;\n",$1,$2,$3);}
	;
	
atributos: atributos atributo
	| atributo
	;

parametro: STRING STRING ','
	| STRING STRING
	;

parametros: parametros parametro
	| parametro
	;
	
relleno_metodo: relleno_metodo STRING
	| relleno_metodo STRING ';'
	| STRING
	| STRING ';'
	//| /*Metodo vacio*/
	;

metodos: m_visibilidad STRING STRING '(' parametros ')' '{' relleno_metodo '}' {printf("%s %s %s (){",$1,$2,$3);}
	| m_visibilidad STRING STRING '(' ')' '{' relleno_metodo '}' {printf("%s %s %s (){",$1,$2,$3);}
	| m_visibilidad STRING STRING '(' parametros ')' '{' '}' {printf("%s %s %s (){",$1,$2,$3);}
	| m_visibilidad STRING STRING '(' ')' '{' '}' {printf("%s %s %s (){",$1,$2,$3);}
	; 

%%
int main(){
	const char extension[6] = ".java";
	char **pathArchivos;
	int i=0;
	pathArchivos = obtenerPathFicheros(extension);
	FILE *f;
	//hacer while de pathArvhivos
	while(pathArchivos[i] != NULL){
		printf("\n%d-> %s\n",i,pathArchivos[i]);
		f = fopen(pathArchivos[i],"r");
		yyin= f;
		yyparse();
		i++;
	}
	fclose(f);
	printf("\n");
	return 0;
}
void yyerror (char const *message) { 
	fprintf (stderr,"%s\n", message);
}
//para el modificador default no se pone nada
//es un error poner algo
