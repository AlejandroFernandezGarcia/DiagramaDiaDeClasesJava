#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

int comprobarExtension(char *nombre, char const *extension){
	if(strstr(nombre,extension)!=NULL){
		return TRUE;
	}else{
		return FALSE;
	}
}

int contarFicheros(char const *directorio,char const *extension){
	DIR *auxDir;
	struct dirent *auxLdir;
	int contador=0;
	auxDir=opendir(directorio);
	auxLdir = readdir(auxDir);
	while(auxLdir != NULL){
		if(comprobarExtension(auxLdir->d_name,extension)==TRUE){
			contador++;
		}
		auxLdir = readdir(auxDir);
	}
	return contador;
}

char **obtenerPathFicheros(){
	// /home/alejandro/NetBeansProjects/ER-12-04/src/interfazUsuario/escritorio
	const char extension[6] = ".java";
	char **pathArchivos;
	int numArchivos=0;
	int archivoActual=0;
	DIR *dir;
	struct dirent *ldir;
	char *directorio = malloc(200*sizeof(char));
	system("clear");
	printf("Path absoluto o relativo del codigo en java\n");
	scanf("%s",directorio);
	if(directorio[0]=='/'){
		dir=opendir(directorio);
	}else{
		char *aux;
		aux = malloc(200*sizeof(char));
		strcpy(aux,getcwd(aux,200*sizeof(char)));
		//strcat(aux,directorio);
		sprintf(aux,"%s/%s",aux,directorio);
		strcpy(directorio,aux);
		printf("%s\n",directorio);
		free(aux);
		dir=opendir(directorio);
	}
	if(dir==NULL){
		perror("Error");
		exit(1);
	}else{
		//printf(" no Error\n");
		numArchivos = contarFicheros(directorio,extension);
		pathArchivos = malloc(numArchivos*sizeof(char*));
		ldir = readdir(dir);
		while(ldir != NULL){
			comprobarExtension(ldir->d_name,extension);
			pathArchivos[archivoActual] = malloc(strlen(ldir->d_name)*sizeof(char));
			strcpy(pathArchivos[archivoActual],ldir->d_name);
			archivoActual++;
			ldir = readdir(dir);
		}
	}
	if(closedir(dir)==-1){
		printf("Error closedir\n");
	}
	//hacer frees
	free(directorio);
}
