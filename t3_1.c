#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h> 
#include <time.h>
#include <string.h>
#define READ 0
#define WRITE 1
#define TAMANIO 31


int main (int argc, char * argv[]){	//main que recibe parametros donde argv[1] = numero de hilos a crear
	srand(time(NULL)); 
	int numHilos = atoi(argv[1]);	//guardo el numero de hilos que se creearan en la variable numHilos
	int i;	//variable del ciclo
	int t;	//tiempo del hilo
	pid_t pid;
	
	char tiempo[TAMANIO]="";	//variable que guarda el tiempo que duerme
	
	int p[2],readbytes;	//pipe
	pipe(p);
	
	
	for(i = 0; i<numHilos; i++){	
		pid = fork();
		if(pid<0){
			printf("Error en el fork()");
			exit(-1);
		}
		
		if(pid == 0){	
			t = rand()%5 + 1;
			sprintf(tiempo,"%d",t);
			close(p[READ]);
			write(p[WRITE],tiempo,strlen(tiempo)+1);
			close(p[WRITE]);
			sleep(t);
		}else{
		wait(NULL);
		char mensaje[TAMANIO];
		close(p[WRITE]);
		readbytes = read(p[READ],mensaje,sizeof(mensaje));
		printf("PID: %d, durmio durante:%s segundos\n",getpid(),mensaje);
		close(p[READ]);
		
		}

	}


	
	
}		
