#define BUFFSIZE 256

//====================================== CABECERA ==========================================//

/* 
	• Nombre del equipo
	• Fecha
	• Hora
*/

//----------------------------- Hostname -------------------------//
// cat /proc/hostname

void hostname(){
	FILE *fhostname; 
	char buffer[BUFFSIZE+1]; 

	fhostname = fopen("/proc/sys/kernel/hostname","r"); 
	fgets(buffer, BUFFSIZE+1, fhostname); 
	fclose(fhostname);
	printf("Hostname: %s",buffer); 
}


//----------------------------- Fecha y Hora -------------------------//
// cat /proc/driver/rtc

void fecha(){
	FILE *frtc;
	char time[BUFFSIZE+1];
	char date[BUFFSIZE+1];

	frtc=fopen("/proc/driver/rtc","r");
	fgets(time, BUFFSIZE+1,frtc);
	fgets(date, BUFFSIZE+1,frtc);
	fclose(frtc);

	sscanf (date, "rtc_date : %s", date);
	sscanf (time, "rtc_time : %s", time);

	printf("Fecha: %s\nHora: %s\n",date, time);
}	