#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(){

	pid_t hijo = fork();
	
	if(hijo > 0){
		wait(NULL); //Proceso padre
	}else if(hijo == 0){
		execlp("/bin/ps", "ps", NULL);
		printf("Toda la clase aprueba con un 10 Sistemas Operativos");
	}
	
	puts("El hijo ha muerto, larga vida al hijo");
	return 0;
}
