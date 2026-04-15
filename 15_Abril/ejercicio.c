/*
Creamos dos procesos, uno se llama lee y el otro escribe. (3 procesos, el padre y los otros dos mencioandos)
Tenemos una variable compartida que almacena un numero.
Se crea ambos procesos uno atras de otro. Una vez los dos estan creados, un preceso lee un numero por teclado.
Una vez que el proceso a leido el numero por teclado, el proceso escribe, accede a la memoria compartida y muestra el numero por pantalla.
Ese mismo proceso escribe muestra un mensaje que dice: Pulsa una tecla para finalizar(Espera a que pulsemos una tecla para que muera).
*/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <string.h>

int main()
{

    int *variable_compartida = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);

    int pipe1[2];
    if (pipe(pipe1) == -1)
    {
        perror("Error al crear la tuberia");
        exit(EXIT_FAILURE);
    }

    pid_t lee = fork();

    if (lee < 0)
    {
        perror("Error al crear el proceso lee!");
        exit(EXIT_FAILURE);
    }
    else if (lee == 0)
    { // Proceso hijo (lee)
        close(pipe1[0]);
        int variableUsuario;
        printf("Escribe un numero cualquiera en el teclado: \n");
        scanf("%d", &variableUsuario);
        *variable_compartida = variableUsuario;
        write(pipe1[1], 1);
    }
    else if (lee > 0)
    { // Proceso padre
        pid_t escribe = fork();

        if (escribe < 0)
        {
            perror("Error al crear el proceso escribe!");
            exit(EXIT_FAILURE);
        }
        else if (escribe == 0)
        { // Proceso hijo(escribe)
            close(pipe1[1]);
            printf("El numero es: %d", *variable_compartida);
            exit(0);
            // Espera que aplastemos una tecla para finalizar el proceso.
        }
        else if (escribe > 0)
        { // Proceso padre.
            wait(NULL);
            wait(NULL);
        }
    }

    munmap(variable_compartida, sizeof(int));
    return 0;
}