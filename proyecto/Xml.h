#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define PRIVATE 1
#define PUBLIC 0
#define DEFAULT 3
#define PROTECTED 2

#define ASOCIACION 10
#define HERENCIA 11
#define REALIZACION 12

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
	int interfaz;
	int abstracta;
};
typedef struct tclase clase;

struct tRelaciones{
	int tipo;
	int idCabeza;
	int idCola;
};
typedef struct tRelaciones relacion;


/*Inicialización a NULL*/
atributo** inicializarAtributos();
parametro*** inicializarParametro();
metodo** inicializarMetodo();

/*Crear cada estructura*/
atributo* crearAtributo(char *nombre, char *tipo, int visibilidad);
parametro* crearParametro(char *nombre, char *tipo);
metodo* crearMetodo(char *nombre,char *tipo, int visibilidad);
clase* creaClase(char *nombre, int interfaz, int abstracta);

/*Crear XML a partir de las estructuras*/
void crearMetodoXML(metodo **lMet);
void crearParametrosXML(parametro ***lPar);
void crearAtributosXML(atributo **lAt);
void crearClaseXML(clase *clase,int numeroClase,int numTotalClases);
void crearLayerXML(int numeroTotalDeClases,int numRelacion);
void crearFinalXML(char *path, char *nombre);
void crearRelacionesXML(relacion *relaciones, int numeroTotalDeClases, int numeroRelaciones);
