CC = gcc
CFLAGS=  -g -Wall
all: clean operaciones.o interprete.o interfaz.o modulo1.o
	
modulo1.o:
	$(CC) $(CFLAGS) -o modulo1.o modulo1.c interfaz.o interprete.o operaciones.o -lncurses
interfaz.o: interfaz.h interfaz.o
	$(CC) $(CFLAGS) -c interfaz.c -lncurses
interprete.o: operaciones.o interprete.h interprete.c
	$(CC) $(CFLAGS) -c interprete.c
operaciones.o: operaciones.h operaciones.c
	$(CC) $(CFLAGS) -c operaciones.c
clean:
	rm -f *.o