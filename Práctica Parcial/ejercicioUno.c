/*
Crea un programa en C donde el proceso Padre genere un array con 5 números aleatorios entre 1 y 100.
1.- El padre debe enviar este array al proceso Hijo mediante un pipe().
2.- El proceso Hijo debe leer el array y filtrar los números(quedándose solo con los pares).
3.- El hijo devolverá la suma de esos números pares al padre usando el pipe.
4.- El padre imprime el resultado devuelo y espera a que el hijo termine.
*/

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    srand(time(NULL));

    int pipe1[2]; // Padre → Hijo
    int pipe2[2]; // Hijo → Padre
    int numeros[5];
    pid_t hijo;

    // Crear pipes
    if (pipe(pipe1) == -1 || pipe(pipe2) == -1)
    {
        perror("Error al crear pipes");
        exit(EXIT_FAILURE);
    }

    hijo = fork();

    if (hijo < 0)
    {
        perror("ERROR EN LA CREACIÓN DEL HIJO");
        exit(EXIT_FAILURE);
    }

    else if (hijo > 0)
    { // PROCESO PADRE

        // Cerrar extremos que no usa
        close(pipe1[0]); // no lee de pipe1
        close(pipe2[1]); // no escribe en pipe2

        // Generar números aleatorios
        printf("Padre genera: ");
        for (int i = 0; i < 5; i++)
        {
            numeros[i] = (rand() % 100) + 1;
            printf("%d ", numeros[i]);
        }
        printf("\n");

        // Enviar array al hijo
        write(pipe1[1], numeros, sizeof(numeros));
        close(pipe1[1]); // cerrar escritura

        // Recibir suma del hijo
        int suma = 0;
        read(pipe2[0], &suma, sizeof(suma));
        close(pipe2[0]);

        printf("Suma de pares recibida del hijo: %d\n", suma);

        // Esperar al hijo
        wait(NULL);
    }

    else
    { // PROCESO HIJO

        // Cerrar extremos que no usa
        close(pipe1[1]); // no escribe en pipe1
        close(pipe2[0]); // no lee de pipe2

        int buffer[5];

        // Leer array del padre
        read(pipe1[0], buffer, sizeof(buffer));
        close(pipe1[0]);

        // Filtrar pares y sumar
        int suma = 0;
        for (int i = 0; i < 5; i++)
        {
            if (buffer[i] % 2 == 0)
            {
                suma += buffer[i];
            }
        }

        // Enviar suma al padre
        write(pipe2[1], &suma, sizeof(suma));
        close(pipe2[1]);

        exit(0);
    }

    return 0;
}