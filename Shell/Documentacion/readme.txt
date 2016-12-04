Baash Program version 1.0 22/11/2016 
======================================== 
Nombre y Apellido: Esteban Tissot  
E-mail: egtissot@gmail.com  
Matricula: 35276396  

INFORMACION GENERAL  
--------------------

-Baash es un programa intérprete de línea de comandos (shell).

-Se utilizan mecanismos de concurrencia y comunicación UNIX.

-En la interfaz Baash se mostrara un promp que contiene en nombre del 
 host, el nombre del usuario y el directorio.

-Los comandos a ejecutar se escriben luego del promp y para ejecutarlos 
 se deben presionar enter.

-Los comandos deben contener la sintaxis: comando argumento1 argumento2...

-Se aceptan redirecciones a traves del caracter ">" o "<".

-Se puede ejecutar pipe de la forma comando1 | comando2.

-Se permiten procesos en segundo plano mediante el caracter & al 
 final del comando.

-Admite path relativo y absoluto.

-No soporta busqueda en secuencia PATH.

-Para finalizar el programa se debe escribir el comando "exit" o 
 presionar la combinacion ctrl+D.
   

COMPILACION  
------------  

-Una vez que se descargó y se descomprimió el archivo baash.tar.gz nos 
 posicionamos en la carpeta donde se encuentra el archivo "baash.c" y 
 abrimos una terminal (click derecho -> Abrir en Terminal).  

-En la Terminal escribimos make y presionamos enter, este comando  
 compilara el programa, creara algunos archivos en la carpeta y quedará 
 listo para su ejecucion.

-En esta version al momento de compilar se mostrara en pantalla tres 
 warnings, los mismos no afectaran la ejecución del programa.

-Si se ejecuta el comando make clean se elimina el archivo baash.o  

EJECUCION  
----------  

-En la Terminal escribimos ./baash

MAIN
-----

-En la funcion principal se especifican los algoritmos correspondientes 
 para atender las solicitudes de posisoniamiento (cd), ejecucion en 
 segundo plano, pipe, redireccionamiento y el resto de los comandos. 

DEPENDENCIAS  
-------------  

-ParteA.h 
	Contiene las funciones para presentar adecuadamente el promp y 
	tomar la entrada por teclado. Tambien contiene una funcion 
	para realizar el parseo. 


FUTURAS MEJORAS
----------------

- Mejorar el parseo y aplicarlo en redireccionamientos y en pipeline.

- Dar soporte a busqueda en secuencia PATH.  



