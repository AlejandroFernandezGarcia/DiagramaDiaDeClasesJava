CC=gcc
SOURCE=Practica3

all:
	flex $(SOURCE).l 
	bison -o $(SOURCE).tab.c $(SOURCE).y -yd 
	$(CC) -c Ficheros.c Ficheros.h
	$(CC) -c Xml.c Xml.h
	$(CC) -g -o $(SOURCE) lex.yy.c $(SOURCE).tab.c -ly -lfl
run: all
	./$(SOURCE)
test1: all
	./$(SOURCE) < ejemplos/Ejemplo1
test2: all
	./$(SOURCE) < ejemplos/Ejemplo2	
	
clean:
	rm -f $(SOURCE) lex.yy.c $(SOURCE).tab.c $(SOURCE).tab.h *.*~ *~ *.gch *.o *.dia
