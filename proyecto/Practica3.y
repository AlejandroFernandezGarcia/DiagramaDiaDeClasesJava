%{
	#include "Ficheros.c"
	#include "Xml.c"
	#include <stdio.h>
	void yyerror (char const *);
	void sumarError();
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
	int errorParseando=1;
	
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
	| package imports tipo_fichero ext_imp '{' firmas_metodos '}'
	| package imports tipo_fichero ext_imp '{' metodos atributos '}' {yyerror("los atributos tienen que ir antes que los métodos.");sumarError();}
	;

string_com: string_com ',' STRING {yyerror("no puede haber varios clases separadas por comas en el implements/extends.");sumarError();} 
	| /*Vacio: Esta bien el extends/implements */
	;
ext_imp: EXTENDS STRING string_com {for(z=0;z<numTotalClases;z++){
												if(strcmp($2,nombresClases[z])==0){
													relacion rel;
													rel.tipo=HERENCIA;
													rel.idCabeza=z;
													rel.idCola=numClases-1;
													//printf("--%d\n",numClases);
													relaciones[numRelacion]=rel;
													numRelacion++;
												}
											} free($2);}
	| IMPLEMENTS STRING  string_com {for(z=0;z<numTotalClases;z++){
												if(strcmp($2,nombresClases[z])==0){
													relacion rel;
													rel.tipo=REALIZACION;
													rel.idCabeza=z;
													rel.idCola=numClases-1;
													//printf("|%s|",$2);
													//printf("--%d\n",numClases);
													relaciones[numRelacion]=rel;
													numRelacion++;
												}
											} free($2);}
	| IMPLEMENTS STRING string_com EXTENDS STRING string_com {yyerror("no puede haber implements y extends al mismo tiempo.");sumarError();} 
	| EXTENDS STRING string_com IMPLEMENTS STRING string_com {yyerror("no puede haber implements y extends al mismo tiempo.");sumarError();} 
	| /*Vacio: No hay ni extends ni implements.*/
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

/*Revisar firmas_metodos*/
firmas_metodos: firmas_metodos m_visibilidad STRING STRING '(' parametros ')' ';' {met[numMetodo] = crearMetodo($4,$3,$2);
																											  numMetodo++;
																											  numParametro=0;
																											  free($3);free($4);}
	| m_visibilidad STRING STRING '(' parametros ')' ';' 	{met[numMetodo] = crearMetodo($3,$2,$1);
																			 numMetodo++;
																			 numParametro=0;
																			 free($2);free($3);}
	| firmas_metodos m_visibilidad STRING STRING '(' ')' ';'  {met[numMetodo] = crearMetodo($4,$3,$2);
																				  numMetodo++;
																				  numParametro=0;
																				  free($3);free($4);}
	| m_visibilidad STRING STRING '(' ')' ';'	  {met[numMetodo] = crearMetodo($3,$2,$1);
																numMetodo++;
																numParametro=0;
																free($2);free($3);}
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
	//printf("\nError------->%d\n",errorParseando);
	if(errorParseando==1){
		printf("%d de %d ficheros analizados\n",numClases,numTotalClases);
	
		printf("\nFinalizado el parseo de todas las clases.\n");
		printf("Generado %s.dia\n",nombreSalida);
	
		crearRelacionesXML(relaciones, numTotalClases,numRelacion);	
		crearLayerXML(numClases,numRelacion);
		crearFinalXML(rutaSalida,nombreSalida);
	}else{
		printf("\nNo se ha podido generar el fichero .dia\n");
	}
	
	free(relaciones);
	free(rutaSalida);
	free(nombreSalida);
	liberarPathFicheros(pathArchivos);
	liberarPathFicheros(nombresClases);
	
	system("rm -fR tmp");
	
	return 0;
}

void yyerror (char const *message) { 
	if(errorParseando>1){
		printf ("-Error en %c%s%c: %s\n",'"',c->nombre,'"',message);
	}else{
		printf ("\n-Error en %c%s%c: %s\n",'"',c->nombre,'"',message);
	}
}
void sumarError(){
	errorParseando++;
}

