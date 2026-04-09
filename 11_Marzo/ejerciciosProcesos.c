#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

//Vamos a crear dos procesos , pid1 = suma, pid = resta. El padre primero tiene que leer el valor de las variables, una vez leído esto, se tiene que crear el proceso suma y el proceso resta. 


int main(){

	int n1, n2;
	pid_t suma, resta;
	
	puts("Inserta el primer dígito: ");
	scanf("%d", &n1);
	
	puts("Inserta el segundo dígito: ");
	scanf("%d", &n2);
	
	
	suma=fork();

	if(suma>0){//->Esta línea solo la ejecuta el padre, ya que la suma tiene que ser positiva, caso contrario habrían dos restas
		resta=fork();
	}
	if(suma == 0){
		printf("La suma de los dos números es: %d\n", n1+n2);
	}else if(resta == 0){
		printf("La resta de los dos núemros es: %d\n", n1-n2);
	}else if(suma > 0 && resta > 0){
		while(wait(NULL)>0){
			puts("Soy el proceso padre y finalizo mi ejecución!");
		}
	}else{
		perror("Hubo algún error!");
	}
		
    return 0;
}
