Modulo Encriptar/Desencriptar version 1.0 1/12/2016 
======================================== 
Nombre y Apellido: Esteban Tissot  
E-mail: egtissot@gmail.com  
Matricula: 35276396  

INFORMACION GENERAL  
--------------------

-Los modulos se deberan ser insertados en el kernel de un sistema linux.

-Los modulos se encargan de presentar al kernel un conjunto estandarizado
 de llamadas al sistema y, luego, traducirlas a las operaciones 
 específicas del hardware.

-Los modulos son desarrollados de manera separada del resto del kernel.

-Los modulos son cargados en tiempo de ejecución en el momento en que son 
 necesarios.

-El modulo de Encriptación se encargará de codificar los caracteres que
 reciva. 

-El modulo de Desencriptación se encargará de decodificar los caracteres
 que reciva.

-El codigo de encriptacion se corresponde con desplazar 10 lugares el 
 caracter.

COMPILACION
------------
 
 Los módulos utilizan para comunicarse con el kernel una interfaz 
 previamente definida, esta interfaz esta descripta en los archivos de 
 header del kernel mismo. Para compilar nuestro propio módulo vamos a 
 necesitar entonces los headers del kernel que estamos corriendo.
 
 -El comando uname -r nos muestra el kernel que esta corriendo.
 -El comando aptitude install linux-headers-version_de_kernel instalara 
 las herramientas necesarias para compilar el modulo.
 -El comando make permite compilar el modulo.
 -El comando make clean elimina los archivos generados al compilar.
 -Solo resta cargar los modulos.

CARGA DEL MODULO
-----------------

 El proceso de carga típico de un módulo (simplificado) es el siguiente.
 Cuando el kernel necesita una funcionalidad que no esta presente, el 
 demonio de módulos del kernel kmod ejectua el binario modprobe para 
 cargar el módulo necesario. Claramente kmod “sabe” cual es el módulo 
 que necesita cargar para satisfacer una necesidad particular. 
 El programa modprobe verifica si el módulo en cuestion necesita de la 
 presencia de otros módulos para funcionar correctamente. Una vez que ha
 definido cuales son los módulos que deben ser cargados y donde se 
 encuentran ubicados modprobe utiliza el programa insmod para cargar 
 estos módulos en memoria y ponerlos a disposicion del kernel para ser 
 utilizados. 
 Se puede ver que módulos estan cargados actualmente y cuales son sus 
 dependencias con el comando lsmod.

 En modo root:
 -insmod encripta.ko
 -insmod desencripta.ko

DESCRIPCION  
------------  

-Ambos modulos contienen dos funciones, int init_module(void) y 
 void cleanup_module(void). Estas funciones deben estar definifas 
 obligatoriamente 

-int init_module(void) se ejecuta al cargar el modulo.

-void cleanup_module se ejecuta al descargar el modulo.

-Funciones de los modulos:

	-static int dev_open() -> Abre el dispositivo

	-static ssize_t dev_read() -> Lee el dispositivo
 
	-static ssize_t dev_write() -> Escribe el dispositivo

	-static int dev_rls() -> Cierra el dispositivo

DEPENDENCIAS  
-------------  

-Los modulos no poseen dependencias.






  
