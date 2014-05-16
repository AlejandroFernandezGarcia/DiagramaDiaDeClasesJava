%{
	#include "Ficheros.c"
	#include "Xml.c"
	#include <stdio.h>
	void yyerror (char const *);
	extern FILE *yyin;
	atributo** at;
	parametro ***par;
	metodo** met;
	clase *c;
	int numAtributo=0;
	int numMetodo=0;
	int numParametro=0;
	int numClases=0;

	
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
%type <valInt> m_visibilidad
%start S
%%
S : package imports clase atributos metodos '}' 
	| package imports clase metodos '}'
	| package imports clase atributos '}'{printf("}\n");}
	;

package: PACKAGE STRING ';';

m_visibilidad: PUBLIC {$$=PUBLIC;}
	| PRIVATE {$$=PRIVATE;}
	| PROTECTED {$$=PROTECTED;}
	| /*Default*/ {$$=PACKAGE;}
	;

imports: IMPORT STRING ';'
	| 
	;

clase : m_visibilidad CLASS STRING '{' {c = crearClase($3); numClases++;}
	;
	
atributo: m_visibilidad STRING STRING ';' {at[numAtributo] = crearAtributo($3,$2,$1); numAtributo++;}
	;
	
atributos: atributos atributo
	| atributo
	;

parametro: STRING STRING ',' {par[numMetodo][numParametro] = crearParametro($2,$1);
										numParametro++;}
	| STRING STRING {par[numMetodo][numParametro] = crearParametro($2,$1);
						  numParametro++;}
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

metodos: m_visibilidad STRING STRING '(' parametros ')' '{' relleno_metodo '}' {met[numMetodo] = crearMetodo($3,$2,$1);numMetodo++;}
	| m_visibilidad STRING STRING '(' ')' '{' relleno_metodo '}' {met[numMetodo] = crearMetodo($3,$2,$1); numMetodo++;}
	| m_visibilidad STRING STRING '(' parametros ')' '{' '}' {met[numMetodo] = crearMetodo($3,$2,$1); numMetodo++;}
	| m_visibilidad STRING STRING '(' ')' '{' '}' {met[numMetodo] = crearMetodo($3,$2,$1); numMetodo++;}
	; 

%%
int main(){
	const char extension[6] = ".java";
	char **pathArchivos;
	int i=0;
	char *rutaSalida,*nombreSalida;
	pathArchivos = obtenerPathFicheros(extension);
	rutaSalida = malloc(sizeof(char)*200);
	nombreSalida = malloc(sizeof(char)*200);
	printf("Nombre del fichero de salida\n");
	scanf("%s",nombreSalida);
	printf("Directorio donde quieres guardarlo\n");
	scanf("%s",rutaSalida);
	FILE *f;
	system("mkdir tmp");
	while(pathArchivos[i] != NULL){
		/*Inicializar estructuras antes de cada parseo*/
		numAtributo=0;
		numMetodo=0;
		numParametro=0;
		at = inicializarAtributos();
		par = inicializarParametro();
		met = inicializarMetodo();
		
		/*Abrir fichero .java y asignarselo a la entrada del analizador*/
		f = fopen(pathArchivos[i],"r");
		yyin= f;
		yyparse();
		
		/*Crea los XML intermedios generandolos a partir de las estructuras*/
		crearAtributosXML(at);
		crearParametrosXML(par);
		crearMetodoXML(met);
		crearClaseXML(c,i);
		
		/*Libera todas las estructuras*/
		free(nombreSalida);
		free(c->nombre);
		free(c);
		liberarParametros(par);
		liberarAtributos(at);
		liberarMetodos(met);
		
		i++;
	}
	fclose(f);
	printf("\n");

	printf("Finalizado el parseo de todas las clases.\n");
	pritff("Generando %s.dia",nombreSalida);
	crearLayerXML(numClases);
	crearFinalXML(rutaSalida,nombreSalida);
	
	free(rutaSalida);

	printf("--->Done.\n");
	system("rm -fR tmp");
	return 0;
}

void yyerror (char const *message) { 
	fprintf (stderr,"%s\n", message);
}
//para el modificador default no se pone nada
//es un error poner algo
