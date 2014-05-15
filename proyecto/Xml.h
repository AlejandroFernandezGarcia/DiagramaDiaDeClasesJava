#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define PRIVATE 1
#define PUBLIC 0
#define PACKAGE 3
#define PROTECTED 2

struct tatributo {
	char *nombre;
	char *tipo;
	int visibilidad;
};

typedef struct tatributo atributo;

struct tparametro {
	char *nombre;
	char *tipo;
};
typedef struct tparametro parametro;

struct tmetodo {
	char *nombre;
	char *tipo;
	int visibilidad;
};
typedef struct tmetodo metodo;

struct tclase {
	char *nombre;
};
typedef struct tclase clase;


atributo* crearAtributo(char *nombre, char *tipo, int visibilidad);
parametro* crearParametro(char *nombre, char *tipo);
metodo* crearMetodo(char *nombre,char *tipo, int visibilidad);
clase* creaClase(char *nombre);


void crearMetodoXML(metodo **lMet);
void crearParametrosXML(parametro ***lPar);
void crearAtributosXML(atributo **lAt);
void crearClaseXML(clase *clase,int numeroClase);
void crearLayerXML(int numeroTotalDeClases);
void crearFinalXML(char *path, char *nombre);
