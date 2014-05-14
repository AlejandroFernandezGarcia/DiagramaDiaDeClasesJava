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

atributo* crearAtributo(char *nombre, char *tipo, int visibilidad);

