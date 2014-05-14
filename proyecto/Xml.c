#include "Xml.h"

#define TRUE 1
#define FALSE 0

#define TAM_MAX 10//20 es lo suficientemente grande?


//faltan metodos de inicializacion de las estructuras

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
	while((lPar[numMetodo][0]!=NULL) && (numMetodo < TAM_MAX)){
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
		free(aux);
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
	printf("%d-",numFichero);
	aux = fgets(linea,200,par);
	while(aux != NULL){
		fputs(linea,resultado);
		aux = fgets(linea,200,par);
	}
	
	fclose(par);
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
	/*int i=0;
	while(met[i]!=NULL){
		free(met[i]->nombre);
		free(met[i]->tipo);
		free(met[i]);
		i++;
	}
	free(met);*/
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

int main(){
	//system("mkdir tmp");
	int i=0,j=0;	
	atributo** at;
	at = (atributo **) malloc(TAM_MAX*sizeof(atributo*));
	while(i<TAM_MAX){
		at[i] = NULL;
		i++;
	}
	at[0] = crearAtributo("Nombre1","tipo1",PUBLIC);
	at[1] = crearAtributo("Nombre2","tipo2",PRIVATE);
	crearAtributosXML(at);
	
	liberarAtributos(at);
	
	parametro ***par;
	par = (parametro ***) malloc(TAM_MAX*sizeof(parametro**));
	
	//par[0] = (parametro **) malloc(TAM_MAX*sizeof(parametro*));
	//par[1] = (parametro **) malloc(TAM_MAX*sizeof(parametro*));
	i=0,j=0;
	while(i<TAM_MAX){
		par[i] = (parametro **) malloc(TAM_MAX*sizeof(parametro*));
		while(j<TAM_MAX){
			par[i][j] = NULL;
			j++;
		}
		i++;
		j=0;
	}
	
	par[0][0] = crearParametro("Nombre1","tipo1");
	par[0][1] = crearParametro("Nombre2","tipo2");
	par[1][0] = crearParametro("Nombre1","tipo1");
	par[1][1] = crearParametro("Nombre2","tipo3");
	crearParametrosXML(par);
	
	liberarParametros(par);
	
	metodo** met;
	met = (metodo **) malloc(TAM_MAX*sizeof(metodo*));
	while(i<TAM_MAX){
		met[i] = NULL;
		i++;
	}
	
	met[0] = crearMetodo("Nombre1","tipo1",PUBLIC);
	met[1] = crearMetodo("Nombre2","tipo2",PRIVATE);
	//met[1] = NULL;
	crearMetodoXML(met);
	
	liberarMetodos(met);
	
	//if(at[49] == NULL){printf("SIII");}
	//fopen("calabacin.txt","wb"); asi lo creo en caso de que no exista
	//sleep(5);
	printf("--->Done.\n");
	//system("rm -fR tmp");
	return 0;
}
