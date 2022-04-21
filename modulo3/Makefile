CC = gcc
CFLAGS=  -Wall
all: clean cola.o operaciones.o interprete.o interfaz.o  kernel.o modulo2.o
	
modulo2.o:
	$(CC) $(CFLAGS) -o modulo2.o default.o  modulo2.c interfaz.o interprete.o operaciones.o cola.o  kernel.o -lncurses
interfaz.o: interfaz.h interfaz.o
	$(CC) $(CFLAGS) -c interfaz.c  -lncurses
interprete.o: operaciones.o interprete.h interprete.c
	$(CC) $(CFLAGS) -c interprete.c
operaciones.o: operaciones.h operaciones.c
	$(CC) $(CFLAGS) -c operaciones.c
cola.o: cola.h cola.c
	$(CC) $(CFLAGS) -c cola.c  
kernel.o: kernel.h kernel.c default.c default.h
	$(CC) $(CFLAGS) -c kernel.c default.c
clean:
	rm -f *.o