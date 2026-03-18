#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(){
	
	pid_t hijo = fork();
	if (hijo > 0){ //Proceso padre
		wait(NULL);
		puts("El proceso suicida hijo ha acabado de ejecutar el esclavo, me largo");
	}else if(hijo == 0){
		execlp("./esclavo", "esclavo", NULL);
		puts("Esto en teoría no sale ya por pantalla");
	}
	
	
	return 0;
}
