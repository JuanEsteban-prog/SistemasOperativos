/*
Comunicación entre procesos con memora compartida anónima(mmap).
El hijo calcula los 10 primeros números de Fibonacci y los escribe en la memoria compartida. El padre los lee tras esperar al hijo y los saca por pantalla.
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <wait.h>
#include <stdlib.h>
#include <sys/mman.h>

#define N 10; //Cantidad de números de Fibonacci a calcular.
int main(){
    

    
    return 0;
}