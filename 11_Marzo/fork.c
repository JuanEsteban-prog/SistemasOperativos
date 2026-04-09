#include <stdio.h>
#include <unistd.h>

int main(){

	puts("Hola!");
	fork(); //Es una llamada al sistema linux, duplica el proceso desde la cual se lo está llamando. Cuando ocupamos fork() se crea en memoria una copia del programa, a partir de la línea siguiente
	puts("DOS PROCESOS");//Uno es el proceso original, otro es la copia del proceso, esta copia se ejecuta desde la línea después del fork()
	fork();
	fork();
	puts("Adiós!");
	return 0;
}

/*fork infinito:
while(1){
    fork();
}

*/