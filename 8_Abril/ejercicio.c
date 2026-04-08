//Tenemos dos procesos y al menos una variable compartida. El padre una vez que ya ha creado al hijo, el padre lee un número entero. Cuando el padre lee el número, el hijo va a calcular su factorial, y el padre una vez que el hijo haya terminado de calcular el factorial, saca el valor del factorial por pantalla.

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h> 
#include <stdlib.h>
#include <sys/mman.h>

static long unsigned int *variable_compartida;//Usamos unsigned long long para evitar que el factorial se desborde rápido.

int main() {

    pid_t hijo;

    variable_compartida = mmap(NULL, sizeof(*variable_compartida), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    *variable_compartida = 0;

    hijo = fork();

    if(hijo < 0){
        perror("ERROR AL CREAR EL HIJO!");
        exit(EXIT_FAILURE);
    }else if(hijo == 0){//Proceso hijo
        long unsigned int factorial = 1, i:
        while(*variable_compartida == 0){//Hace esperar al proceso padre, funciona hasta que el padre lee una variable y cambia el valor de variable_compartida
            usleep(2);
        }
        
        for(i = 1; i <= *variable_compartida; i++){
            factorial = factorial * i; 
        }
        *variable_compartida = factorial; 
        exit(0); 

    }else if(hijo > 0){//Proceso padre
        puts("Introduce un número para calcular su factorial: ");
        scanf("%lu", &*variable_compartida);
        wait(NULL);
        printf("El valor del factorial es: %lu\n", *variable_compartida);
    }
    
    return 0;
}