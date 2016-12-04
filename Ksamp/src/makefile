DEPEND = Cabecera.h ParteB.h ParteC.h ParteD.h
CFLAGS = -Wall -pedantic 

#Objetivo:
Objeto: ksamp.o
	@gcc -o ksamp ksamp.o

#Compilacion: 
ksamp.o: ksamp.c $(DEPEND)
	@gcc $(CFLAGS) -c ksamp.c

#Funciones:
clean:
	@rm ksamp.o


