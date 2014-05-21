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
	
test3: all
	./$(SOURCE) < ejemplos/Ejemplo3	
	
test4: all
	./$(SOURCE) < ejemplos/Ejemplo4	
	
test5: all
	./$(SOURCE) < ejemplos/Ejemplo5

test6: all
	./$(SOURCE) < ejemplos/Ejemplo6
	
test7: all
	./$(SOURCE) < ejemplos/Ejemplo7
	
test8: all
	./$(SOURCE) < ejemplos/Ejemplo8
	

clean:
	rm -f $(SOURCE) lex.yy.c $(SOURCE).tab.c $(SOURCE).tab.h *.*~ *~ *.gch *.o *.dia
