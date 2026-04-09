// EJERCICIO DE TIPO EXAMEN

/*
Comunicación entre procesos con memora compartida anónima(mmap).
El pid calcula los 10 primeros números de Fibonacci y los escribe en la memoria compartida. El padre los lee tras esperar al pid y los saca por pantalla.
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <wait.h>
#include <stdlib.h>
#include <sys/mman.h>

#define N 10; //Cantidad de números de Fibonacci a calcular.
int main(){
    // 1.- Crear la región de memoria compartida ANTES del fork
    pid_t pid;
    int *compartido = mmap(NULL, N * sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0); //Así se reserva memoria para un ARRAY! -> En realidad estamos creando el array

    if(compartido == MAP_FAILED){
        perror("mmap");
        exit(EXIT_FAILURE);
    }
    
    // 2.- Crear el proceso pid con un fork

    pid = fork();

    if(pid < 0){
        perror("Error al crear el fork");
        munmap(compartido, N * sizeof(int));
        exit(EXIT_FAILURE);
    }else if(pid == 0){//Proceso hijo
        printf("[HIJO  -  PID %d] Escribiendo Fibinacci en memoria compartida...\n", getpid()); //getpid() nos devuelve nuestro propio número del proceso
        //Calcula y escribe los N primeros números de Fibonacci
        compartido[0] = 0;
        compartido[1] = 1;

        for(int i = 2; i < N; i++){
            compartido[i] 
        }
    }else if(pid > 0){//Proceso padre

        wait(NULL);
        //Lee e imprime los valroes escritos por el hijo
        printf("[Padre - PID %d]Hijo terminado, Leyendo la memoria compartida...", getpid());
        for(int i = 0; i < N; i++){
            printf("%d", compartido[i]);
        }
        printf("\n");

        //Liberar la memoria compartida
        munmap(compartido, N * sizeof(int));
    }

    
    return EXIT_SUCCESS;
}