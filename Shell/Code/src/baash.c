#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

#include "tareaA.h"


int pipeline(char* command1,char *command2);

int main(){
	int argc;
	char *argv[1024];

	while(!feof(stdin)){
		char *fichero;
		char *command1;
		char *command2;
		argc = 0;
		int flags[3] = {0,0,0};

		argc = interface(&argv, flags, &fichero, &command1, &command2);

		//comando "exit" 
		if (argc==-1){
			return 0;
		}
		//comando "cd"
		else if ((!strcmp(argv[0],"cd")) && (argc==2)){
			chdir(argv[1]);
		}

		//se ejecuta comando en segundo plano
		else if ((strcmp(argv[argc-1],"&")) == 0){
			int process;
			process =fork();
			if (process<0){
				printf("Error al crear proceso hijo\n");
			}
			else if(process==0){
				//proceso hijo creado
				execv(argv[0],argv);
				return(0);
			}
		}

		else if(flags[0]){
			pipeline(command1,command2);
		}

		else if(flags[1]){
			FILE *f;
			printf("operador %s\n", command1); 
			printf("fichero:%s\n",fichero );
			f=freopen(fichero,"r",stdin);		
            system(command1);
            f=freopen("/dev/tty","r",stdin); 
		}

		else if(flags[2]){
			FILE *foutput;
			FILE *in;
			char buff[512];

			foutput=freopen(fichero,"w",stdout);
			if(!(in = popen(command2, "r"))){break;}
			while(fgets(buff, 512, in)!=NULL){
                printf("%s", buff); 
            }
    	 	freopen("/dev/tty","a",stdout);
            fclose(in);
        } 

        else {
        	int process;
			process =fork();
			if (process<0){
				printf("Error\n");
			}
			else if(process==0){
				//proceso hijo creado
				execv(argv[0],argv);
				perror("fallo en exec");
				exit(EXIT_FAILURE);
				return(0);
			}
        }     	
	}
	return 0;
}


int pipeline(char* command1,char *command2){

 int fd[2],pid=1;
 
 pipe(fd);
 pid=fork();
 switch(pid){
    
    case -1:
            printf("Error");
            break;
         
    case 0:
            close(fd[0]);
            dup2(fd[1],1);  //duplica el filedescriptor
            system(command1);
            close(fd[1]);
            exit(0);
            break;
    default:
            //wait();  
            close(fd[1]); 
            dup2(fd[0],0);
            
            system(command2);
            close(fd[0]);
            break;
 }
 freopen("/dev/tty","a",stdout);
 freopen("/dev/tty","r",stdin);
 
 return -1;
}