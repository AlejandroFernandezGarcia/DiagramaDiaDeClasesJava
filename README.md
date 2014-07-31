##################################################################
Analizador de clases JAVA que genera un diagrama de clases en Dia.
##################################################################

-----------------
Precondiciones: -
-----------------
 - Las clases deben ser compilables.
 - No pueden < y >, por lo tanto no se podrían usar los generics de java.
 - Tampoco anotaciones con @
 - Cada clase debe ir en un fichero.
 - Los métodos pueden llevar cosas dentro, siempre y cuando no sean llaves.


---------
Reconoce-
---------

Reconoce lo especificado en la propuesta.
 - [public | private | protected | default] [abstract] [interface | class] XXX [implements | extends] YYY
 - [public | private | protected | default] [Integer | String | ...] atributo1
 - [public | private | protected | default] [Integer | String | Void | ...] metodo1 (param1, param2)

Reconoce alguna cosa a mayores para gestion de errores como por ejemplo los constructores.

--------------------
Gestión de errores -
--------------------

Como ya se comentó en la propuesta y en el seguimiento, resulta dificil 
pensar que "errores" gestionar debido a que se supone que el código de 
las clases debería estar correctamente  ya que es compilable. Por lo 
tanto, los errores que gestiono serían acotaciones o restricciones que 
le he impuesto al lenguaje, son todas a nivel sintáctico y serían los 
siguientes:

 - El orden del contenido de una clase debe ser: primero atributos y luego métodos.
 - No se admiten constructores.
 - Implements o extends no pueden aparecer los dos a la vez.
 - Implements solo puede llevar como parametro 1 clase.
 - Extends solo puede llevar como parametro 1 clase.

No se si faltaría alguno pero esos son los errores básicos que getiono 
en la gramática.

Para lo errores se mostrará:
 - La clase en la que se ha dado el error.
 - La descripción del error.


----------------
Funcionamiento -
----------------

Para que sea fácil y rapido de ejecutar he puesto un Makefile con las siguientes ordenes:
 - make -> compila
 - make run -> compila y ejecuta
 - make testN -> compila y ejecuta el test N
 - make clean -> limpia el directorio base
	
En total he puesto 8 ejemplos:
 - Del 1 al 3, 8: Ejemplos de un correcto funcionamiento.
 - Del 4 al 7: Ejemplos de tratamiento de errores.


Si se realiza una ejecución normal el programa pedirá:
 - El directorio donde buscar las clases JAVA.
 - El nombre del fichero DIA que será el resultado de la ejecución.
 - El directorio donde se va a guardar el resultado.
	


NOTA: Se utiliza la función system que permite ejecutar comandos del sistema operativo, en este 
		caso la use para crear y borrar la carpeta temporal donde iran los XML temporales. 
		No creo que de algún problema con algun tipo de linux.
NOTA2: Al abrir el XML con el DIA lo más probable es que las flechas no acaben donde deberían acabar y se 
		 solapen con las clases pero las flechas relacionan las clases correctamente, es decir, no queda 
		 "bonito".


