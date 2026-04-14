/*
Crea una región de memoria compartida para un array de 10 enteros usando mmap().
1.- El Padre debe crear el espacio y luego lanzar a dos hijos simultáneamente.
2.- El Hijo 1 debe llenar las posiciones del 0 al 4 con números pares, luego hace exit(0).
3.- El hijo 2 debe llenar las posiciones del 5 al 9 con números impares, luego hace exit(0).
4.- El padre debe esperar obligatoriamente a que ambos hijos terminen la ejecución.
5.- Finalmente el padre lee el array completo de memoria compartida, imprime todo su contenido y libera la memoria con munmap().
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <unistd.h>

int main()
{

    int *memoria_compartida = mmap(NULL, 10 * sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);

    pid_t hijo1;

    hijo1 = fork();

    if (hijo1 < 0)
    {
        perror("Error en el fork!");
        exit(EXIT_FAILURE);
    }
    else if (hijo1 == 0)
    { // Proceso Hijo
        for (int i = 0; i < 5; i++)
        {
            int numeroPar = (i + 1) * 2;
            memoria_compartida[i] = numeroPar;
        }
        exit(0);
    }
    else if (hijo1 > 0)
    { // Proceso Padre
        pid_t hijo2 = fork();

        if (hijo2 < 0)
        {
            perror("Error en la creacion del fork!");
            exit(EXIT_FAILURE);
        }
        else if (hijo2 == 0)
        { // Proceso hijo
            int numeroImpar = 1;
            for (int i = 5; i < 10; i++)
            {
                memoria_compartida[i] = numeroImpar;
                numeroImpar += 2;
            }
            exit(0);
        }
        else if (hijo2 > 0)
        { // Proceso padre
            wait(NULL);
            wait(NULL);

            for (int i = 0; i < 10; i++)
            {
                printf("%d", memoria_compartida[i]);
                printf("\n");
            }
            munmap(memoria_compartida, 10 * sizeof(int));
        }
    }
    return 0;
}