#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h>
#include "Ficheros.h"

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
	closedir(auxDir);
	return contador;
}

void liberarPathFicheros(char **pathFicheros){
	int i=0;
	while(pathFicheros[i] != NULL){
		free(pathFicheros[i]);
		i++;
	}
	free(pathFicheros);
}

char **obtenerPathFicheros(const char *extension){
	// /home/alejandro/NetBeansProjects/ER-12-04/src/interfazUsuario/escritorio
	char **pathArchivos;
	int numArchivos=0;
	int archivoActual=0;
	DIR *dir;
	struct dirent *ldir;
	char *directorio = malloc(200*sizeof(char));
	system("clear");
	printf("Path absoluto o relativo del codigo en java\n");
	scanf("%s",directorio);
	dir=opendir(directorio);
	if(dir==NULL){
		perror("Error");
		exit(1);
	}else{
		//printf(" no Error\n");
		numArchivos = contarFicheros(directorio,extension);
		pathArchivos = (char**) malloc((1+numArchivos)*sizeof(char*));
		int w;
		for(w=0;w < numArchivos+1; w++){
			pathArchivos[w] = NULL;
		}
		ldir = readdir(dir);
		while(ldir != NULL){
			if(comprobarExtension(ldir->d_name,extension)){
				pathArchivos[archivoActual] = (char*) malloc(200*sizeof(char));
				sprintf(pathArchivos[archivoActual],"%s/%s",directorio,ldir->d_name);
				//strcpy(pathArchivos[archivoActual],ldir->d_name);
				archivoActual++;
			}
			ldir = readdir(dir);
		}
		//pathArchivos[numArchivos+1] = NULL;//?
	}
	if(closedir(dir)==-1){
		printf("Error closedir\n");
	}
	//hacer frees
	free(directorio);
	
	return pathArchivos;
}

/*int main(){
	char **pathArchivos = obtenerPathFicheros(".java");
	liberarPathFicheros(pathArchivos);
	return 1;
}*/
