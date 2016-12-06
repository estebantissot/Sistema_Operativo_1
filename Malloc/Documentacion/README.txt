Malloc version 1.0 6/12/2016 
======================================== 
Nombre y Apellido: Esteban Tissot  
E-mail: egtissot@gmail.com  
Matricula: 35276396  

INFORMACION GENERAL  
--------------------

-Se implementa la funcion malloc que permite alojar bloques de memoria
 en un programa en C.

-Se implementa la funcion free que permite liberar bloques de memoria
 reservados por la funcion malloc.

-Se implementa la funcion calloc que llama a la funcion malloc y luego
 rellena ese espacio reservado con 0.

-Se especifican 4 politicas de ajuste, first fit, best fit, next fit y
 worst fit. Para seleccionar una u otra hay que modificar el codigo fuente,
 hay que comentar la política por defecto (first_fit) y descomentar la 
 politica requerida. Esto se hace dentro de la funcion malloc.
 

DESCRIPCION  
------------  

-Algoritmo de la funcion malloc:
 	busca un bloque lo suficientemente grande
	-si base esta inicializado:
		-trata de dividir el bloque
		-marca el fragmento como usado
	-si base no esta inicializado extiende la heap
	si la funcion falla devolvemos NULL

-La funcion free libera memoria. Esto se hace poniendo el break, llamada
 a la funcion brk() en la posicion del fragmento si estamos al final de 
 la heap. 
 Algoritmo:
	-si el puntero es valido:
		-recibimos la direccion del bloque
		-lo marcamos como libre
		-si el anterior existe y esta libre, retrocedemos y 
		fusionamos ambos bloques.
		-si estamos en el ultimo bloque liberamos memoria
		-si no hay mas bloques volvemos al estado original.
	-si el puntero no es valido no hacemos nada.

-Politicas de Ajuste:
	-first_fit Politica del primer ajuste. Se busca y utiliza el 
		primer lugar en memoria libre y con tamaño suficiente.
	
	-best_fit Politica del mejor ajuste. Se busca el segmento de memoria 
		 libre utilizable de tamaño mas parecido o que deje menor 
		 memoria sin utilizar dentro del mismo segmento.

	-next_fit Politica del proximo ajuste. Se busca el espacio de memoria 
		que cumplan con el minimo de tamaño que requerimos pero 
		empezamos a buscar del ultimo segmento de memoria que 
		modificamos.

	-worst_fit Politica del peor ajuste. Se busca cual es el segmento de 
		memoria libre utilizable que deje mayor espacio sin utilizar 
		dentro del mismo segmento. 

DEPENDENCIAS  
-------------  

-no existen dependencias.






  
