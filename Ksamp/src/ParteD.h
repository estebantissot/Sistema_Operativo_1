//====================================== PARTE D ==========================================//

/*
• Número de peticiones a disco realizadas. 
• Cantidad de memoria configurada en el hardware y cantidad disponible 
• Promedio de carga de 1 minuto. 
*/


//----------------------------- Peticiones a Disco -----------------------------//
//cat /proc/diskstats

void petdisc(){
	char buffer[BUFFSIZE+1];
	char *p=NULL;
	int peticiones;
	FILE *fdiskstats;

	fdiskstats=fopen("/proc/diskstats","r");
		while (!feof(fdiskstats)){
			fgets(buffer,BUFFSIZE+1,fdiskstats);
			p=strstr(buffer,"sda");
			if(p !=NULL){
				strcpy(buffer,p);
				break;
			}
		}
	fclose(fdiskstats); 

	sscanf(buffer, "sda %d",&peticiones);
	printf("Peticiones a Disco: %d\n",peticiones);
}


//-------------------------------- Memoria ----------------------------------//
// cat /proc/meminfo

void inforam(int hflag){
	float memtotal, memfree, memdisp;
	FILE *fmeminfo;

	fmeminfo=fopen("/proc/meminfo","r");
	fscanf(fmeminfo,"MemTotal: %f kB \n",&memtotal);
	fscanf(fmeminfo,"MemFree: %f kB\n",&memfree);
	fscanf(fmeminfo,"MemAvailable: %f kB",&memdisp);
	fclose(fmeminfo);

	if (hflag==1){
		printf("Memoria Total: %.2f MB\n", memtotal/1024);
		//printf("Memoria Free: %.2f kB\n", memfree/1024);
		printf("Memoria Disponible: %.2f MB\n", memdisp/1024);
	}
	else{
		printf("Memoria Total: %f kB\n", memtotal);
		//printf("Memoria Free: %f kB\n", memfree);
		printf("Memoria Disponible: %f kB\n", memdisp);
	}	
}


//--------------------------- Promedio de carga ----------------------------// 
// cat /proc/loadavg

void carga(){
	float carga;
	FILE *floadavg;

	floadavg=fopen("/proc/loadavg","r");
	fscanf(floadavg,"%f",&carga);
	fclose(floadavg);

	printf("Carga: %.2f\n", carga);
}