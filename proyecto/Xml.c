#include "Xml.h"

#define TRUE 1
#define FALSE 0

#define TAM_MAX 50




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
	if(f==NULL){
		printf("No existen la plantilla\n");
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
	free(aux);
}



int main(){
	//system("mkdir tmp");
	atributo** at;
	at = (atributo **) malloc(TAM_MAX*sizeof(atributo*));//50 es lo suficientemente grande
	at[0] = crearAtributo("Nombre1","tipo1",PUBLIC);
	at[1] = crearAtributo("Nombre2","tipo2",PRIVATE);
	crearAtributosXML(at);
	//if(at[49] == NULL){printf("SIII");}
	//fopen("calabacin.txt","wb"); asi lo creo en caso de que no exista
	//sleep(5);
	printf("%s - %s\n",at[0]->nombre,at[0]->tipo);
	//system("rm -fR tmp");
}
