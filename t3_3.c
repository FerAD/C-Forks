#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h> 
#include <string.h>
#define READ 0
#define WRITE 1
#define TAMANIO 100




int main (){
	
	int bandera = 0;	//bandera para finalizar el programa	

	int p[2];	//pipe
	pipe(p);

	pid_t pid;	//creo el proceso
	pid = fork();	

	while (bandera == 0){	//mientras la bandera sea 0
		char mensaje[TAMANIO];	//leeo el mensaje
		scanf("%s",&mensaje);	
		
		if(pid < 0){	//mensaje de error si hay problemas con la creacion del proceso
			printf("error\n");
			return -1;
		}
		
		if(pid == 0){	//hijo
				
			close(p[WRITE]); //obtengo el mensaje mediante el pipe
			read(p[READ],mensaje, strlen(mensaje)+1);
			if(mensaje == "termina"){	//si el mensaje es termina imprime id del proceso hijo y cambia el valor de bandera
				printf("Proceso %d terminado\n",getpid());
				bandera = 1;
			}else {	// sino es termina el mensaje imprime el mensaje 
				printf("MENSAJE: %s\n",mensaje);	
			}
			close(p[READ]);
			
		}else {	//padre
			close(p[READ]);	//manda el mensaje por pipe
			write(p[WRITE],mensaje,strlen(mensaje) + 1);
			close(p[WRITE]);
		}
	}

	printf("Proceso %d terminado",getpid());	//cuando bandera == 1 imprime el id del proceso padre
	
	return 1;
	
}	
