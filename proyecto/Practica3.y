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
%token <valChar> T_PUBLIC
%token <valChar> T_PRIVATE
%token <valChar> T_PROTECTED
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

package: PACKAGE STRING ';' {free($2);};

m_visibilidad: T_PUBLIC {$$=PUBLIC;}
	| T_PRIVATE {$$=PRIVATE;}
	| T_PROTECTED {$$=PROTECTED;}
	| /*Default*/ {$$=DEFAULT;}
	;

imports: IMPORT STRING ';' {free($2);}
	| 
	;

clase : m_visibilidad CLASS STRING '{' {c = crearClase($3); numClases++;free($3);}
	;
	
atributo: m_visibilidad STRING STRING ';' {at[numAtributo] = crearAtributo($3,$2,$1);
														 numAtributo++;free($2);free($3);}
	;
	
atributos: atributos atributo
	| atributo
	;

parametro: STRING STRING ',' {par[numMetodo][numParametro] = crearParametro($2,$1);
										numParametro++;free($1);free($2);}
	| STRING STRING {par[numMetodo][numParametro] = crearParametro($2,$1);
						  numParametro++;free($1);free($2);}
	;

parametros: parametros parametro
	| parametro
	;
	
relleno_metodo: relleno_metodo STRING {free($2);}
	| relleno_metodo STRING ';' {free($2);}
	| STRING {free($1);}
	| STRING ';' {free($1);}
	//| /*Metodo vacio*/
	;

metodos: m_visibilidad STRING STRING '(' parametros ')' '{' relleno_metodo '}' {met[numMetodo] = crearMetodo($3,$2,$1);
																										  numMetodo++;
																										  numParametro=0;
																										  free($2);free($3);}
	| m_visibilidad STRING STRING '(' ')' '{' relleno_metodo '}' {met[numMetodo] = crearMetodo($3,$2,$1);
																					  numMetodo++;
																					  numParametro=0;
																					  free($2);free($3);}
	| m_visibilidad STRING STRING '(' parametros ')' '{' '}' {met[numMetodo] = crearMetodo($3,$2,$1);
																		  		 numMetodo++;
																				 numParametro=0;
																				 free($2);free($3);}
	| m_visibilidad STRING STRING '(' ')' '{' '}' {met[numMetodo] = crearMetodo($3,$2,$1);
																  numMetodo++;
																  numParametro=0;
																  free($2);free($3);}
	; 

%%
int main(){
	const char extension[6] = ".java";
	char **pathArchivos;
	int i=0;
	int numTotalClases=0;
	char *rutaSalida,*nombreSalida;
	pathArchivos = obtenerPathFicheros(extension,&numTotalClases);
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
		liberarAtributos(at);
		
		crearParametrosXML(par);
		liberarParametros(par);
				
		crearMetodoXML(met);
		liberarMetodos(met);

		crearClaseXML(c,i,numTotalClases);
		
		free(c->nombre);
		free(c);
		
		system("rm -f tmp/parametros*.xml");
		
		i++;
		//break;
		fclose(f);
	}
	printf("\n");

	printf("Finalizado el parseo de todas las clases.\n");
	printf("Generando %s.dia\n",nombreSalida);
	crearLayerXML(numClases);
	crearFinalXML(rutaSalida,nombreSalida);
	
	free(rutaSalida);
	free(nombreSalida);
	liberarPathFicheros(pathArchivos);
	
	printf("--->Done.\n");
	system("rm -fR tmp");
	return 0;
}

void yyerror (char const *message) { 
	fprintf (stderr,"%s\n", message);
}
//para el modificador default no se pone nada
//es un error poner algo
