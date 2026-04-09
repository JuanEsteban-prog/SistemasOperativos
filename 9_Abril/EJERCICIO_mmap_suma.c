// Instrucción atómica -> No puede interrumpirse hasta que se ejecute. 
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <unistd.h>

#define LIMITE 1000 

int main(){
    int *variable_compartida = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    *variable_compartida = 0;
    
    int N;  // ← Declarar variable
    pid_t hijo = fork();
    
    if(hijo == 0){
        for(N = 0; N < LIMITE; N++){
            *variable_compartida = *variable_compartida + 1; // Se produce una condición de carrera. Los procesos están entrando y saliendo constantemente de memoria.
        }
        exit(0);
    } else if(hijo > 0){
        for(N = 0; N < LIMITE; N++){
            *variable_compartida = *variable_compartida - 1; // Se produce una condición de carrera.  
        }
        wait(NULL);  
        printf("El resultado de este código es: %d\n", *variable_compartida);  // ← Desreferenciar puntero
    }
    
    munmap(variable_compartida, sizeof(int));
    return 0;
}
