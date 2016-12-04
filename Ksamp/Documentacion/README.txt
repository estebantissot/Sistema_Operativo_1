ksamp Program version 1.0 14/10/2016 
======================================== 
Nombre y Apellido: Esteban Tissot  
E-mail: egtissot@gmail.com  
Matricula: 35276396  

INFORMACION GENERAL  
--------------------

-ksamp es un programa que provee de informacion sobre el sistema, muestra  
 datos sobre el hardware, sistema operativo y algunas estadisticas.  

-ksamp solo puede ejecutarse en sistemas operativos basados en LINUX  
 debido a que hace uso del sistema de archivo /proc.  

-Si no se pone le guion "-" antes de las opciones, el programa no las  
 reconoce.

-La fecha y hora son las correspondientes al meridiano de Greenwich  
 (UTC 00:00). Dependiendo del lugar en el que se este se debe modificar  
 segun <https://es.wikipedia.org/wiki/Huso_horario#UTC.C2.B100:00.2C_Z>  
 EJEMPLO: Argentina se encuentra en la zona horaria -03:00, es decir  
 que ksamp muestra 3 horas mas de las que hay en Argentina.  

COMPILACION  
------------  

-Una vez que se descargo y se descomprimio el archivo ksamp.tar.gz  
 nos posicionamos en la carpeta donde se encuentra el archivo "ksamp.c"  
 y abrimos una terminal (click derecho -> Abrir en Terminal).  

-En la Terminal escribimos make y hacemos enter, este comando compilara  
 el programa, creara algunos archivos en la carpeta y quedara listo para  
 su ejecucion.

-Si se ejecuta el comando make clean se elimina el archivo ksamp.o  

EJECUCION  
----------  

-En la Terminal escribimos ./ksamp [OPCIONES] [ARGUMENTO1] [ARGUMENTO2]  

DESCRIPCION  
------------  

-ksamp  
        Nombre del Equipo, Fecha y Hora, Tipo y Modelo de CPU, Tiempo  
        transcurrido desde que se incio, Cantidad de sistemas de  
        archivo soportados por el kernel.  

-ksamp -s  
        Informacion de "ksamp" mas: Tiempo de CPU, Cantidad de cambio  
        de contexto, Fecha y Hora de inicio de sistema, Cantidad de  
	procesos creados.  

-ksamp -l a b  
        Informacion de "ksamp -s" mas:Peticiones a disco, Memoria total  
	y disponible, promedio de carga de 1 minuto en intervalos de  
	"a" segundos durante "b" segundos.  

-ksamp -l -h a b  
        Informacion de "ksamp -l" La opcion -h devuelve valores de  
	memoria en MB.  

-Si se escribe algun argumento u opcion no valida, se obtendra un  
 mensaje de error y se mostrara la informacion descripta.

DEPENDENCIAS  
-------------  

-Cabecera.h  
	Contiene las funciones para obtener el nombre de equipo, la  
	fecha y la hora. Hace uso de los directorios /proc/hostname  
	y /proc/driver/rtc.  

-ParteB.h  
	Contiene funciones para obtener el tipo y modelo de CPU, version  
	del kernel, cantidad de tiempo transcurrido desde que se inicio  
	el sistema y cantidad de archivos soportados por el kernel.  
	Manipula los directorios: /proc/cpuinfo , /proc/version ,  
	/proc/uptime , /proc/filesystems.  

-ParteC.h  
	Contiene funciones para la opcion "ksamp -s". Hace uso del  
	directorio /proc/stat.  

-ParteD.h  
	Contiene funciones para la opcion "ksamp -l a b". Hace uso de  
	los directorios /proc/diskstats , /proc/meminfo , /proc/loadavg.  

