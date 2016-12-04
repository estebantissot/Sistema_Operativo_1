//====================================== PARTE C ==========================================//

/*
•Cantidad de tiempo de CPU utilizado para usuarios, sistema y proceso idle.
• Cantidad de cambios de contexto. 
• Fecha y hora cuando el sistema fue iniciado. 
• Número de procesos creados desde el inicio del sistema. 
*/


//--------------------------- Tiempo de CPU  -------------------------//
// cat /proc/stat

void tcpu(){
	FILE * fstat;
	int user, nice, system, idle;
	
	fstat=fopen("/proc/stat","r");
	fscanf(fstat,"cpu %d %d %d %d",&user, &nice, &system, &idle);
	fclose(fstat);

	printf("Tiempo de CPU utilizado por:\nusuarios: %d\nsistema: %d\nprocesos idle: %d\n", user, system, idle);
}


//--------------------------- Cambio de Contexto ---------------------//
// cat /proc/stat

void ctxt(){
	FILE * fstat;
	char ccontexto[60], buffer[BUFFSIZE+1];
	char *p=NULL;

	fstat=fopen("/proc/stat","r");
	while (!feof(fstat)){
		fgets(buffer,BUFFSIZE+1,fstat);
		p=strstr(buffer,"ctxt");
		if(p !=NULL){
			strcpy(buffer,p);
			break;
		}
	}
	fclose(fstat);

	sscanf(buffer,"ctxt %s",ccontexto);

	printf("Cambios de Contexto: %s\n", ccontexto);
}


//--------------------------- Inicio de Sistema ---------------------//
// cat /proc/stat

void inisist(){
	FILE * fstat;
	char *p;
	char buffer[BUFFSIZE+1];
	unsigned int btime;
	time_t aux;
	char time[30];

	fstat=fopen("/proc/stat", "r");
	while (!feof(fstat)){
		fgets(buffer,BUFFSIZE+1,fstat);
		p=strstr(buffer,"btime");
		if(p !=NULL){
			strcpy(buffer,p);
			break;
		}
	}
	fclose(fstat);

	sscanf(buffer,"btime %u", &btime);
	aux=(time_t)btime;
	strftime(time,30, "%c", localtime(&aux));

	printf("Fecha de Inicio del Sistema: %s\n", time);
}


//--------------------------- Procesos Creados ---------------------//
// cat /proc/stat

void proc_creados(){
	FILE * fstat;
	char *p;
	char buffer[BUFFSIZE+1];
	int cant=0;

	fstat=fopen("/proc/stat", "r");
	while (!feof(fstat)){
		fgets(buffer,BUFFSIZE+1,fstat);
		p=strstr(buffer,"processes");
		if(p !=NULL){
			strcpy(buffer,p);
			break;
		}
	}
	fclose(fstat);

	sscanf(buffer,"processes %d", &cant);
	printf("Total de procesos creados: %d\n", cant);
}