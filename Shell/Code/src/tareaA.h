#include <stdio.h>
#include <unistd.h>

#define BUFFSIZE 256

void getPrompt();
char* cuserid(char *string);
void comando(char argv0[512], char pathcmd[], char cmd[]);

int interface(char *argv[1024], int flags[], char **fichero, char **command1, char **command2){
	int i =0;
	*command1=(char *)malloc(256);
	*command2=(char *)malloc(256);
	*fichero=(char *)malloc(256);

	char s[2] = " \n";
	char buffer[512];
	strcpy(buffer,"\n");

	while((strcmp(buffer,"\n") == 0)&&(!feof(stdin))){
		getPrompt();
		fgets(buffer,512,stdin);	
	}

	//si el comando el "exit", la funcion termina.
	if ((!strcmp(buffer,"exit\n")) || (feof(stdin))){
		return -1;
	}
	//si se va a usar pipe
	if (strstr(buffer,"|") != NULL){
		flags[0] = 1;
		sscanf(buffer, "%[^\t\n|] | %[^\t\n]",*command1, *command2);

	}
	//si se va a redir
	if (strstr(buffer,"<") != NULL){
		flags[1] = 1;
		printf("buffer:%s\n", buffer );
		sscanf(buffer, "%[^\t\n<] < %[^\t\n]",*command1, *fichero);
	}
	//si se va a usar stdout
	if (strstr(buffer,">") != NULL){
		flags[2] = 1;
		sscanf(buffer, "%[^\t\n>] > %[^\t\n]", *command2, *fichero);
	}

	argv[0] = (char*) calloc(1, sizeof(char));
    argv[0] = strtok(buffer, s);	//get the first argv 
    while(argv[i] != NULL){	//walk through other argv 
    	argv[i+1] = (char*) calloc(1, sizeof(char));
		argv[i+1] = strtok(NULL, s);
		i++;
	}

	return i;
}


void getPrompt(){
	char p[BUFFSIZE+1];
	char hostname[BUFFSIZE+1];
	char path[BUFFSIZE+1];

	//Se obtiene nombre de Usuario
	cuserid(p);
	//Se obtine nombre del Host
	gethostname(hostname, BUFFSIZE+1);
	//Se obtiene working directory
	getcwd(path,BUFFSIZE+1);

	strcat(p,"@");
	strcat(p,hostname);
	strcat(p,":");
	strcat(p,path);
	strcat(p,"$");

	printf("%s ",p);
}


void comando(char argv0[512], char pathcmd[], char cmd[]){
	
	char *token[BUFFSIZE+1];
	int i=0;

    token[0] = strtok(argv0, "/");	//get the first argv 
 
    while( token[i] != NULL ){	//walk through other argv 
 		if(i>=1){
 			strcat(pathcmd,token[i-1]);
			strcat(pathcmd,"/");
 		}

		token[i+1] = strtok(NULL, "/");
		strcpy(cmd,token[i]);
			i++;
	}

}
