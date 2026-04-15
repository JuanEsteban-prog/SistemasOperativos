// Suma paralela de un array usando la memoria compartida (mmap + fork)
// Implementa un programa en C que calcule, de forma colaborativa entre un proceso padre y un proceso hijo, la suma de todos los elementos de un array de enteros.
// El array tendrá N elementos(con N par). Cada proceso calculará la suma de su mitad del array y escribirá el resultado en una zona de memoria compartida.
// Al final, el proceso padre leerá ambos resultados y mostrará la suma total.

/*
1.- Reservar la zona de memoria compartida anes de llamar al fork.
2.- La zoma compartida debe contener un array de dos enteros: sumas[0] para el padre y sumas[1] para el hijo.
3.- El proceso hijo calculará la suma de la mitad superior del array y guardará en sumas[1].

Después terminará con exit(0)

4.- El proceso padre calculará la suma de la mitad inferior, la guardaraá en sumas[0] y esperará al hijo con wait() antes de leer sumas[1].
5.- Liberar la memoria con munmap() al terminar.
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h> //mmap, munmap
#include <sys/wait.h> // wait
#include <unistd.h>   // fork, getpid

#define N 10 /*Número de elementos (debe ser par)*/

int main()
{
    // Array de datos a sumar
    int datos[N] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int *sumas = mmap(NULL, 2 * sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    int suma_padre;

    pid_t pid = fork();

    if (pid < 0)
    {
        perror("Error al crear el fork!");
        exit(EXIT_FAILURE);
        munmap(sumas, 2 * sizeof(int));
    }
    else if (pid == 0)
    { // Proceso hijo
        int suma_hijo = 0;

        for (int i = N / 2; i < N; i++)
        {
            suma_hijo += datos[i];
        }

        sumas[1] = suma_hijo;
        exit(0);
    }
    else if (pid > 0)
    { // Proceso padre
        for (int i = 0; i < N / 2; i++)
        {
            suma_padre += datos[i];
        }

        sumas[0] = suma_padre;

        // Esperar al hijo
        wait(NULL);

        int total = sumas[0] + sumas[1];

        printf("Padre (PID %d) suma: %d\n", getpid(), suma_padre);
        printf("Suma total: %d\n", total);

        // Liberar memoria
        munmap(sumas, 2 * sizeof(int));
    }
    return 0;
}