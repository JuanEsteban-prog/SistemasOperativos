//Inicio de explicación llamadas al sistema

#include <stdio.h>
#include <unistd.h>
#include <sys/syscall.h>//Incluye todas las llamadas al sistema de LINUX

int main(){
	
	char mensaje[] = "Hola mundo\n";
	printf("%s", mensaje);
	
	write(1, mensaje, sizeof(mensaje));//Esta linea ya no es compatible con nada que no sea LINUX, lo mismo con lo de adelante
	syscall (SYS_write, 1, mensaje, sizeof(mensaje));
	
	return 0;
}
