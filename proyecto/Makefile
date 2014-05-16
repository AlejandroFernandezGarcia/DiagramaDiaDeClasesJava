CC=gcc
SOURCE=Practica3

all:
	flex $(SOURCE).l 
	bison -o $(SOURCE).tab.c $(SOURCE).y -yd 
	$(CC) -c Ficheros.c Ficheros.h
	$(CC) -c Xml.c Xml.h
	$(CC) -o $(SOURCE) lex.yy.c $(SOURCE).tab.c -ly -lfl
run: all
	./$(SOURCE)
clean:
	rm -f $(SOURCE) lex.yy.c $(SOURCE).tab.c $(SOURCE).tab.h *.*~ *~ *.gch *.o
