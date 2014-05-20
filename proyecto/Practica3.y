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
	char **nombresClases;
	int numAtributo=0;
	int numMetodo=0;
	int numParametro=0;
	int numClases=0;
	relacion *relaciones;
	int numRelacion=0;
	int numTotalClases=0;
	int z;
	int control=FALSE;
	
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
%token <valChar> EXTENDS
%token <valChar> IMPLEMENTS
%token <valChar> INTERFACE
%token <valChar> ABSTRACT
%token <valChar> CLASS
%token <valChar> LLAVE_A
%token <valChar> PACKAGE
%token <valChar> IMPORT
%type <valInt> m_visibilidad
%start S
%%
S : package imports tipo_fichero ext_imp '{' atributos metodos '}' 
	| package imports tipo_fichero ext_imp '{' metodos '}'
	| package imports tipo_fichero ext_imp '{' atributos '}'
	;

ext_imp: EXTENDS STRING {for(z=0;z<numTotalClases;z++){
									if(strstr($2,nombresClases[z])!=NULL){
										relacion rel;
										rel.tipo=HERENCIA;
										rel.idCabeza=z;
										rel.idCola=numClases-1;
										//printf("--%d\n",numClases);
										relaciones[numRelacion]=rel;
										numRelacion++;
									}
								} free($2);}
	| IMPLEMENTS STRING  {for(z=0;z<numTotalClases;z++){
									if(strstr($2,nombresClases[z])!=NULL){
										relacion rel;
										rel.tipo=REALIZACION;
										rel.idCabeza=z;
										rel.idCola=numClases-1;
										//printf("--%d\n",numClases);
										relaciones[numRelacion]=rel;
										numRelacion++;
									}
								} free($2);}
	| /*Vacio*/
	;

package: PACKAGE STRING ';' {free($2);};

m_visibilidad: T_PUBLIC {$$=PUBLIC;}
	| T_PRIVATE {$$=PRIVATE;}
	| T_PROTECTED {$$=PROTECTED;}
	| /*Default*/ {$$=DEFAULT;}
	;

imports: imports IMPORT STRING ';' {free($3);}
	| 
	;

tipo_fichero : m_visibilidad CLASS STRING  {c = crearClase($3,FALSE,FALSE);
														  numClases++;free($3);}
	| m_visibilidad INTERFACE STRING 		 {c = crearClase($3,TRUE,FALSE);
															numClases++;free($3);}
	| m_visibilidad ABSTRACT CLASS STRING	 {c = crearClase($4,FALSE,TRUE);
														  numClases++;free($4);}
	;
	
atributo: m_visibilidad STRING STRING ';'	{for(z=0;z<numTotalClases;z++){
															if(strstr($2,nombresClases[z])!=NULL){
																relacion rel;
																rel.tipo=ASOCIACION;
																rel.idCabeza=z;
																rel.idCola=numClases-1;
																//printf("--%d\n",numClases);
																relaciones[numRelacion]=rel;
																numRelacion++;
																control=TRUE;
															}
														}
														if(!control){
															at[numAtributo] = crearAtributo($3,$2,$1);
															numAtributo++;
														}
														control=FALSE;
														free($2);free($3);}
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

metodo: m_visibilidad STRING STRING '(' parametros ')' '{' relleno_metodo '}' {met[numMetodo] = crearMetodo($3,$2,$1);
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

metodos: metodos metodo
	| metodo
	;

%%
int main(){
	const char extension[6] = ".java";
	char **pathArchivos;
	int i=0;
	char *rutaSalida,*nombreSalida;
	nombresClases = (char**) malloc(TAM_MAX*sizeof(char*));
	pathArchivos = obtenerPathFicheros(extension,&numTotalClases,nombresClases);
	relaciones = malloc(numTotalClases*(numTotalClases-1)*sizeof(relacion));//??????
	rutaSalida = malloc(sizeof(char)*200);
	nombreSalida = malloc(sizeof(char)*200);
	printf("Nombre del fichero de salida\n");
	scanf("%s",nombreSalida);
	printf("Directorio donde quieres guardarlo\n");
	scanf("%s",rutaSalida);
	FILE *f;
	system("mkdir tmp");
	printf("\nAnalizando %d ficheros JAVA\n",numTotalClases);
	while(pathArchivos[i] != NULL){
		/*Inicializar estructuras antes de cada parseo*/
		numAtributo=0;
		numMetodo=0;
		numParametro=0;
		at = inicializarAtributos();
		par = inicializarParametro();
		met = inicializarMetodo();
		
		/*Abrir fichero .java y asignarselo a la entrada del analizador*/
		printf(".");
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
		fclose(f);
	}
	printf("\n");

	printf("\nFinalizado el parseo de todas las clases.\n");
	printf("Generando %s.dia\n",nombreSalida);
	crearRelacionesXML(relaciones, numTotalClases,numRelacion);
	crearLayerXML(numClases,numRelacion);
	crearFinalXML(rutaSalida,nombreSalida);
	
	free(relaciones);
	free(rutaSalida);
	free(nombreSalida);
	liberarPathFicheros(pathArchivos);
	liberarPathFicheros(nombresClases);
	
	printf("--->Done.\n");
	system("rm -fR tmp");
	
	return 0;
}

void yyerror (char const *message) { 
	fprintf (stderr,"%s\n", message);
}
//para el modificador default no se pone nada
//es un error poner algo
