//====================================== PARTE B ==========================================//	

/*
• Tipo y modelo de CPU. 
• Versión de Kernel. 
• Cantidad de tiempo transcurrido desde que se inició el sistema operativo, 
  con el formato ddD hh:mm:ss. 
• Cantidad de sistemas de archivo soportados por el kernel 
*/

//--------------------------- Tipo y Modelo de CPU ---------------------//
// cat /proc/cpuinfo

void cpuinfo(){
	FILE * fcpuinfo;
	char tipo[BUFFSIZE+1], modelo[BUFFSIZE+1];

	fcpuinfo=fopen("/proc/cpuinfo","r");
	for (int i=0;i<4;i++) {
		if (i==1){fgets(tipo,BUFFSIZE+1,fcpuinfo);}
		fgets(modelo,BUFFSIZE+1,fcpuinfo);
	}
	fclose(fcpuinfo);

	sscanf(tipo,"vendor_id :%[^\n]",tipo);
	sscanf(modelo,"model name :%[^\n]",modelo);

	printf("Tipo de CPU: %s\nModelo de CPU: %s\n", tipo,modelo);
}


 //------------------------- Version del Kernel ----------------------//
// cat /proc/version

void kernelinfo(){
	FILE * fversion;
	char cadena1[10], cadena2[10], cadena3[10];

	fversion=fopen("/proc/version","r");
	fscanf(fversion,"%s %s %s",cadena1,cadena2,cadena3);
	fclose(fversion); 

	printf("Version de Kernel: %s\n",cadena3); 
}


//----------------------------- UpTime -----------------------------//
// cat /proc/uptime

void uptime(){
	FILE * fuptime;
	int time,seg,min,hora,dia;

	fuptime=fopen("/proc/uptime","read");
	fscanf(fuptime,"%d",&time);
	fclose(fuptime);

	seg = time%60;
	min = (time/60)%60;
	hora = (time/3600)%24;
	dia = time/86400;

	printf("UpTime: %dD %d%dh:%d%dm:%d%ds\n",dia,hora/10,hora%10,min/10,min%10,seg/10,seg%10);
}


//-------- Cantidad de Sistemas de archivo soportados por el kernel ---------//
// cat /proc/filesystems

void filesystems(){
	FILE * ffilesystems;
	int i=0, c;
	
	ffilesystems = fopen("/proc/filesystems","r");
	while(feof(ffilesystems)== 0){
		c=fgetc(ffilesystems);
		if (c=='\n') {i++;}
	}
	fclose(ffilesystems);

	printf("El kernel soporta %d sistemas de archivos\n", i);
}
