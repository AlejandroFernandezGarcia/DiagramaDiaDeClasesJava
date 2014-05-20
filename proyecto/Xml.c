#include "Xml.h"
#include <unistd.h>

#define TRUE 1
#define FALSE 0

#define TAM_MAX 50//20 es lo suficientemente grande?

atributo* crearAtributo(char *nombre, char *tipo,int visibilidad){
	atributo *at;
	at = malloc (sizeof(atributo));
	at->nombre = malloc(sizeof(char)*200);
	at->tipo = malloc(sizeof(char)*200);
	
	strcpy(at->nombre,nombre);
	strcpy(at->tipo,tipo);
	at->visibilidad = visibilidad;
	return at;
}

parametro* crearParametro(char *nombre, char *tipo){
	parametro *par;
	par = malloc (sizeof(parametro));
	par->nombre = malloc(sizeof(char)*200);
	par->tipo = malloc(sizeof(char)*200);
	
	strcpy(par->nombre,nombre);
	strcpy(par->tipo,tipo);
	return par;
}

metodo* crearMetodo(char *nombre,char *tipo, int visibilidad){
	metodo *met;
	met = malloc (sizeof(metodo));
	met->nombre = malloc(sizeof(char)*200);
	met->tipo = malloc(sizeof(char)*200);
	
	strcpy(met->nombre,nombre);
	strcpy(met->tipo,tipo);
	met->visibilidad = visibilidad;
	return met; 
}

clase* crearClase(char *nombre, int interfaz, int abstracta){/*Hace falta puntero¿?¿?*/
	clase *c;
	c = (clase*) malloc(sizeof(clase));
	c->nombre = malloc(sizeof(char)*200);
	
	strcpy(c->nombre,nombre);
	c->interfaz = interfaz;
	c->abstracta = abstracta;
	return c;
}

void copiarFicheroAtributos(FILE *resultado){
	FILE *f;
	char *linea,*aux;
	linea = malloc (200*sizeof(char));
	f = fopen("tmp/atributos.xml","r");
	aux = fgets(linea,200,f);
	while(aux != NULL){
		fputs(linea,resultado);
		aux = fgets(linea,200,f);
	}
	fclose(f);
	free(linea);
}

void copiarFicheroMetodo(FILE *resultado){
	FILE *f;
	char *linea,*aux;
	linea = malloc (200*sizeof(char));
	f = fopen("tmp/metodo.xml","r");
	aux = fgets(linea,200,f);
	while(aux != NULL){
		fputs(linea,resultado);
		aux = fgets(linea,200,f);
	}
	fclose(f);
	free(linea);
}

void copiarFicheroLayer(FILE *resultado){
	FILE *f;
	char *linea,*aux;
	linea = malloc (200*sizeof(char));
	f = fopen("tmp/layer.xml","r");
	aux = fgets(linea,200,f);
	while(aux != NULL){
		fputs(linea,resultado);
		aux = fgets(linea,200,f);
	}
	fclose(f);
	free(linea);
}

void crearFinalXML(char *path, char *nombre){
	FILE *f;
	FILE *resultado;
	char *aux, *linea;
	aux = malloc (sizeof(char)*200);
	linea = malloc (sizeof(char)*200);
	if((path[strlen(path)-1]) == '/'){
		sprintf(aux,"%s%s%s",path,nombre,".dia");
	}else{
		sprintf(aux,"%s/%s%s",path,nombre,".dia");
	}
	resultado = fopen(aux, "w");
	f = fopen("plantillas/estructuraPrincipal.xml","r");
	free(aux);
	if(resultado==NULL){
		free(aux);
		printf("El directorio de salida no existe");
		exit(1);
	}
	aux = fgets(linea,200,f);
	while(aux != NULL){
		if(strstr(linea,"<!--Aqui el layer de clases-->") != NULL){
			copiarFicheroLayer(resultado);
			fputs("\n",resultado);
		}else{
			fputs(linea,resultado);
		}
		aux = fgets(linea,200,f);
	}
	fclose(f);
	fclose(resultado);
	free(linea);
}

void crearRelacionesXML(relacion *relaciones, int numeroTotalDeClases, int numeroRelaciones){
	FILE *f;
	FILE *resultado;
	int relacionActual=0;
	char *aux, *linea;
	int posX,posY;
	linea = malloc (sizeof(char)*200);
	while(relacionActual < numeroRelaciones){
		aux = malloc (sizeof(char)*200);
		f = fopen("plantillas/lineaBasica.xml","r");
		sprintf(aux,"%s%d%s","tmp/linea",relacionActual,".xml");
		resultado = fopen(aux,"w");
		free(aux);
		aux = fgets(linea,200,f);
		while(aux != NULL){
			aux = malloc (sizeof(char)*200);
			if(strstr(linea,"<!--IdFlecha-->") != NULL){
				sprintf(aux,"%s%c%s%c%s%c%d%c%s%c%c%d%c%s\n","    <dia:object type=",'"',"Standard - Line",'"'
															," version=",'"',0,'"'," id=",'"','O',relacionActual+numeroTotalDeClases,'"',">");
				fputs(aux,resultado);
			}else if(strstr(linea,"<!--ConexionCola-->") != NULL){
				if(((float)numeroTotalDeClases/2)>relaciones[relacionActual].idCola){
					posX= 20*(relaciones[relacionActual].idCola)+4;
					posY=	3;
				}else{
					posX= 20*((relaciones[relacionActual].idCola)%(numeroTotalDeClases/2))+4;
					posY= 15;
				}
				sprintf(aux,"%s%c%d,%d%c%s\n","<dia:point val=",'"',posX,posY,'"',"/>");
				fputs(aux,resultado);
			}else if(strstr(linea,"<!--ConexionCabeza-->") != NULL){
				if(((float)numeroTotalDeClases/2)>relaciones[relacionActual].idCabeza){
					posX= 20*(relaciones[relacionActual].idCabeza)+4;
					posY=	3;
				}else{
					posX= 20*((relaciones[relacionActual].idCabeza)%(numeroTotalDeClases/2))+4;
					posY= 15;
				}
				sprintf(aux,"%s%c%d,%d%c%s\n","<dia:point val=",'"',posX,posY,'"',"/>");
				fputs(aux,resultado);
			}else if(strstr(linea,"<!--Estilo de linea-->") != NULL){
				switch(relaciones[relacionActual].tipo){
					case ASOCIACION:
						sprintf(aux,"%s%c%d%c%s\n","        <dia:enum val=",'"',0,'"',"/>");
					break;
					case HERENCIA:
						sprintf(aux,"%s%c%d%c%s\n","        <dia:enum val=",'"',0,'"',"/>");
					break;
					case REALIZACION:
						sprintf(aux,"%s%c%d%c%s\n","        <dia:enum val=",'"',1,'"',"/>");
					break;
				}
				fputs(aux,resultado);
			}else if(strstr(linea,"<!--Cabeza de la linea-->") != NULL){
				switch(relaciones[relacionActual].tipo){
					case ASOCIACION:
						sprintf(aux,"%s%c%d%c%s\n","        <dia:enum val=",'"',1,'"',"/>");
					break;
					case HERENCIA:
						sprintf(aux,"%s%c%d%c%s\n","        <dia:enum val=",'"',12,'"',"/>");
					break;
					case REALIZACION:
						sprintf(aux,"%s%c%d%c%s\n","        <dia:enum val=",'"',12,'"',"/>");
					break;
				}
				fputs(aux,resultado);
			}else{
				fputs(linea,resultado);
			}
			free(aux);
			aux = fgets(linea,200,f);
		}
		relacionActual++;
		fclose(f);
		fclose(resultado);
	}
	
	free(linea);
}

void crearLayerXML(int numeroTotalDeClases,int numRelacion){
	FILE *f;
	FILE *resultado;
	int ficheroActual=0;
	int relacionActual=0;
	char *aux,*linea;
	linea = malloc (sizeof(char)*200);
	aux = malloc (sizeof(char)*200);
	resultado=fopen("tmp/layer.xml","w");
	sprintf(aux,"%s%c%s%c%s%c%s%c%s%c%s%c%s\n","  <dia:layer name=",'"',"Fondo",'"',
	" visible=",'"',"true",'"'," active=",'"',"true",'"',">");
	fputs(aux,resultado);
	free(aux);
	//añadir las relaciones tambien
	while(ficheroActual < numeroTotalDeClases){
		aux = malloc (sizeof(char)*200);
		sprintf(aux,"%s%d%s","tmp/clase",ficheroActual,".xml");
		f=fopen(aux,"r");
		free(aux);
		aux = fgets(linea,200,f);
		while(aux != NULL){
			fputs(linea,resultado);
			aux = fgets(linea,200,f);
		}
		ficheroActual++;
		fclose(f);
	}
	while(relacionActual < numRelacion){
		aux = malloc (sizeof(char)*200);
		sprintf(aux,"%s%d%s","tmp/linea",relacionActual,".xml");
		f=fopen(aux,"r");
		free(aux);
		aux = fgets(linea,200,f);
		while(aux != NULL){
			fputs(linea,resultado);
			aux = fgets(linea,200,f);
		}
		relacionActual++;
		fclose(f);
	}
	fputs("  </dia:layer>\n",resultado);
	fclose(resultado);
	free(linea);
}

void crearClaseXML(clase *clase,int numeroClase, int numTotalClases){
	FILE *f;
	FILE *resultado;
	f=fopen("plantillas/clase.xml","r");
	char *linea,*aux;
	int posX=0;
	int posY=0;
	linea = malloc (200*sizeof(char));
	aux = malloc(200*sizeof(char));
	sprintf(aux,"%s%d%s","tmp/clase",numeroClase,".xml");
	resultado=fopen(aux,"w");
	free(aux);
	if((f==NULL)||(resultado==NULL)){
		printf("No existen la plantilla/No se ha podido crear el resultado\n");
		free(aux);
		free(linea);
		exit(1);
	}
	aux = fgets(linea,200,f);
	while(aux != NULL){
		if(strstr(linea,"<!--IdClase-->")!=NULL){//idClase
			sprintf(linea,"%s%c%s%c%s%c%d%c%s%c%c%d%c%s\n","    <dia:object type=",'"',"UML - Class",'"'," version=",'"',0,'"'," id=",'"','O',numeroClase,'"',">");
			fputs(linea,resultado);
		}else	if(strstr(linea,"<!--<dia:string>#NombreClase#</dia:string>-->")!=NULL){//nombre
			sprintf(linea,"%s%s%s\n","        <dia:string>#",clase->nombre,"#</dia:string>");
			fputs(linea,resultado);
		}else if(strstr(linea,"Posicion-->")!=NULL){//posicion
			if(numeroClase==0){
				posX=0;
				posY=0;
			}else{
				if(((float)numTotalClases/2)>numeroClase){
					posX= 20*numeroClase;
					posY=	0;
				}else{
					posX= 20*((numeroClase)%(numTotalClases/2));
					posY= 15;
				}
				/*if((numTotalClases/2)>numeroClase){
					posX= 15*numeroClase;
					posY=	0;
				}else{
					posX= 15*((numeroClase)%(numTotalClases/2));
					posY= 10;
				}*/
			}
			sprintf(linea,"%s%c%d%c%d%c%s\n","        <dia:point val=",'"',posX,',',posY,'"',"/>");
			fputs(linea,resultado);
		}else if(strstr(linea,"Combinado de atributos")!=NULL){//copiar fichero atributos
			copiarFicheroAtributos(resultado);
			fputs("\n",resultado);
		}else if(strstr(linea,"Combinado de metodos")!=NULL){//copiar fichero metodos ¿petara por los espacios?
			copiarFicheroMetodo(resultado);
			fputs("\n",resultado);
		}else if(strstr(linea,"<!--Abstracta?-->")!=NULL){//abstracta
			if(clase->abstracta){
				sprintf(linea,"%s%c%s%c%s\n","        <dia:boolean val=",'"',"true",'"',"/>");
			}else{
				sprintf(linea,"%s%c%s%c%s\n","        <dia:boolean val=",'"',"false",'"',"/>");
			}
			fputs(linea,resultado);
		}else if(strstr(linea,"<!--Estereotipo-->")!=NULL){//interfaz
			if(clase->interfaz){
				fputs("        <dia:string>#interface#</dia:string>\n",resultado);
			}else{
				fputs("        <dia:string>##</dia:string>\n",resultado);
			}
			
		}else{
			fputs(linea,resultado);
		}
		aux = fgets(linea,200,f);
	}
	free(linea);
	fclose(f);
	fclose(resultado);
}

void crearAtributosXML(atributo **lAt){
	int i=0;
	char *linea,*aux;
	linea = malloc (200*sizeof(char));
	aux = malloc(200*sizeof(char));
	FILE *resultado;
	FILE *f;
	f = fopen("plantillas/atributo.xml","r");
	resultado = fopen("tmp/atributos.xml","w");
	sprintf(aux,"%s%c%s%c%s\n","      <dia:attribute name=",'"',"attributes",'"',">");
	fputs(aux,resultado);
	free(aux);
	if(f==NULL){
		printf("No existen la plantilla\n");
		free(aux);
		free(linea);
		exit(1);
	}
	while((lAt[i] != NULL) && (i < TAM_MAX)){
		
		//recorrer linea a linea
		aux = fgets(linea,200,f);
		while(aux != NULL){
			if(strstr(linea,"<!--<dia:string>#NombreAtributo#</dia:string>-->")!=NULL){
				sprintf(linea,"%s%s%s\n","            <dia:string>#",lAt[i]->nombre,"#</dia:string>");
			}else if(strstr(linea,"<!--<dia:string>#TipoSegundoAtributo#</dia:string>-->")!=NULL){
				sprintf(linea,"%s%s%s\n","            <dia:string>#",lAt[i]->tipo,"#</dia:string>");
			}else if(strstr(linea,"/>Privacidad-->")!=NULL){
				sprintf(linea,"%s%c%d%c%s\n","            <dia:enum val=",'"',lAt[i]->visibilidad,'"',"/>");
			}
			
			//printf("%s",linea);
			fputs(linea,resultado);
			aux = fgets(linea,200,f);
		}
		//escribirlo en otro fichero
		//printf("---->%s",linea);
		rewind(f);
		i++;
	}
	fputs("      </dia:attribute>",resultado);
	fclose(f);
	fclose(resultado);
	free(linea);
}

void crearParametrosXML(parametro ***lPar){
	int i,numMetodo=0;
	char *linea,*aux;
	linea = malloc (200*sizeof(char));
	FILE *f;
	FILE *resultado;
	f = fopen("plantillas/parametrosMetodo.xml","r");
	while((lPar[numMetodo]!=NULL) && (numMetodo < TAM_MAX)){
		i=0;
		
		aux = malloc(200*sizeof(char));//¿?¿?¿?¿Le habia puesto 500
		sprintf(aux,"%s%d%s","tmp/parametros",numMetodo,".xml");
		resultado = fopen(aux,"w");
		sprintf(aux,"%s%c%s%c%s\n","          <dia:attribute name=",'"',"parameters",'"',">");
		fputs(aux,resultado);
		free(aux);
		if(f==NULL){
			printf("No existen la plantilla\n");
			exit(1);
		}
		while((lPar[numMetodo][i] != NULL) && (i < TAM_MAX)){
		
			//recorrer linea a linea
			aux = fgets(linea,200,f);
			while(aux != NULL){
				if(strstr(linea,"<!--<dia:string>#NombreParametro#</dia:string>-->")!=NULL){
					sprintf(linea,"%s%s%s\n","                <dia:string>#",lPar[numMetodo][i]->nombre,"#</dia:string>");
				}else if(strstr(linea,"<!--<dia:string>#TipoParametro#</dia:string>-->")!=NULL){
					sprintf(linea,"%s%s%s\n","                <dia:string>#",lPar[numMetodo][i]->tipo,"#</dia:string>");
				}
			
				//printf("%s",linea);
				fputs(linea,resultado);
				aux = fgets(linea,200,f);
			}
			//escribirlo en otro fichero
			//printf("---->%s",linea);
			rewind(f);
			i++;
		}
		fputs("          </dia:attribute>",resultado);
		numMetodo++;
		fclose(resultado);
	}
	fclose(f);
	free(linea);
}

void copiarFicherosParametros(FILE *resultado, int numFichero){
	FILE *par;
	char *aux, *linea;
	aux = malloc (200*sizeof(char));
	linea = malloc (200*sizeof(char));
	sprintf(aux,"%s%d%s","tmp/parametros",numFichero,".xml");
	par = fopen(aux,"r");
	free(aux);
	if(par!=NULL){
		aux = fgets(linea,200,par);
		while(aux != NULL){
			fputs(linea,resultado);
			aux = fgets(linea,200,par);
		}
		fputs("\n",resultado);
		fclose(par);
	}
	free(linea);
}

void crearMetodoXML(metodo **lMet){
	int i=0;
	char *linea,*aux;
	aux = malloc(200*sizeof(char));
	FILE *resultado;
	FILE *f;
	f = fopen("plantillas/metodo.xml","r");
	resultado = fopen("tmp/metodo.xml","w");
	sprintf(aux,"%s%c%s%c%s\n","      <dia:attribute name=",'"',"operations",'"',">");
	fputs(aux,resultado);
	free(aux);
	if(f==NULL){
		printf("No existen la plantilla\n");
		exit(1);
	}
	linea = malloc (200*sizeof(char));
	while((lMet[i] != NULL) && (i < 2)){
		//recorrer linea a linea
		aux = fgets(linea,200,f);
		while(aux != NULL){
			if(strstr(linea,"<!--<dia:string>#NombreMetodo#</dia:string>-->")!=NULL){
				sprintf(linea,"%s%s%s\n","            <dia:string>#",lMet[i]->nombre,"#</dia:string>");
				fputs(linea,resultado);
			}else if(strstr(linea,"<!--<dia:string>#TipoMetodo#</dia:string>-->")!=NULL){
				sprintf(linea,"%s%s%s\n","            <dia:string>#",lMet[i]->tipo,"#</dia:string>");
				fputs(linea,resultado);
			}else if(strstr(linea,">Visibilidad-->")!=NULL){
				sprintf(linea,"%s%c%d%c%s\n","            <dia:enum val=",'"',lMet[i]->visibilidad,'"',"/>");
				fputs(linea,resultado);
			}else if(strstr(linea,"<!--Aqui va combinar parametros-->")!=NULL){
				copiarFicherosParametros(resultado,i);
				//fputs("\n",resultado);
			}else{
				fputs(linea,resultado);
			}
			//printf("%s",linea);
			
			aux = fgets(linea,200,f);
		}
		//escribirlo en otro fichero
		//printf("---->%s",linea);
		rewind(f);
		i++;
	}
	fputs("      </dia:attribute>",resultado);
	fclose(f);
	fclose(resultado);
	free(linea);
	//system("rm tmp/parametros*.xml");
}



void liberarMetodos(metodo **met){
	int i=0;
	while(met[i]!=NULL){
		free(met[i]->nombre);
		free(met[i]->tipo);
		free(met[i]);
		i++;
	}
	free(met);
}


void liberarParametros(parametro ***par){
	int i=0,j=0;
	while(par[i]!=NULL){
		while(par[i][j]!=NULL){
			free(par[i][j]->tipo);
			free(par[i][j]->nombre);
			free(par[i][j]);
			j++;
		}
		free(par[i]);
		i++;
		j=0;
	}
	free(par);
}

void liberarAtributos(atributo **at){
	int i=0;
	while(at[i]!=NULL){
		free(at[i]->nombre);
		free(at[i]->tipo);
		free(at[i]);
		i++;
	}
	free(at);
}

atributo** inicializarAtributos(){
	int i=0;
	atributo** at;
	at = (atributo **) malloc(TAM_MAX*sizeof(atributo*));
	while(i<TAM_MAX){
		at[i] = NULL;
		i++;
	}
	return at;
}

parametro*** inicializarParametro(){
	int i=0,j=0;
	parametro ***par;
	par = (parametro ***) malloc((1+TAM_MAX)*sizeof(parametro**));
	while(i<TAM_MAX){
		par[i] = (parametro **) malloc(TAM_MAX*sizeof(parametro*));
		while(j<TAM_MAX){
			par[i][j] = NULL;
			j++;
		}
		i++;
		j=0;
	}
	par[i] = NULL;
	return par;
}


metodo** inicializarMetodo(){
	int i=0;	
	metodo** met;
	met = (metodo **) malloc(TAM_MAX*sizeof(metodo*));
	while(i<TAM_MAX){
		met[i] = NULL;
		i++;
	}
	return met;
}

/*int main(){
	system("mkdir tmp");
	
	atributo** at = inicializarAtributos();
	parametro ***par = inicializarParametro();
	metodo** met = inicializarMetodo();
	
	at[0] = crearAtributo("Nombre1","tipo1",PUBLIC);
	at[1] = crearAtributo("Nombre2","tipo2",PRIVATE);
	par[0][0] = crearParametro("Nombre1","tipo1");
	par[0][1] = crearParametro("Nombre2","tipo2");
	par[1][0] = crearParametro("Nombre1","tipo1");
	par[1][1] = crearParametro("Nombre2","tipo3");
	met[0] = crearMetodo("Nombre1","tipo1",PUBLIC);
	met[1] = crearMetodo("Nombre2","tipo2",PRIVATE);
	
	clase *c;
	c = crearClase("PrimeraClase");
	
	crearAtributosXML(at);
	crearParametrosXML(par);
	crearMetodoXML(met);
	crearClaseXML(c,0);
	
	
	free(c->nombre);
	free(c);
	liberarParametros(par);
	liberarAtributos(at);
	liberarMetodos(met);
	
	crearLayerXML(1);
	crearFinalXML(".", "Diagrama");
	
	printf("--->Done.\n");
	system("rm -fR tmp");
	return 0;
}*/
