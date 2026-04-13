/*
NO SE PUEDE UTILIZAR TUBERÍAS

Declarar una región compartida de memoria (mmap) con espacio para un array con 3 enteros.
1.- La posición [0] es para que el Hijo 1 escriba un número (ej. El cuadrado de 5).
2.- La posición [1] es para que el Hijo 2 escriba otro número (ej. el cubo de 5).
3.- La posición [2] será calculada por el Padre sumando [0] y [1].
4.- Sincronizar adecuadamente usando las llamadas a wait() para asegurarnos que el padre no calcule la posición [2] hasta que los hijos hayan terminado de escribir en [0] y [1].
Imprime el resultado.
*/

#include <stdio.h>     //-> Incluye printf() y scanf()
#include <unistd.h>    // -> fork(), pipe(), read(), write(), close().
#include <sys/types.h> //-> pid_t
#include <sys/wait.h>  //-> wait(), waitpid()
#include <stdlib.h>    //-> exit(), rand(), srand()
#include <time.h>      //-> time()
#include <string.h>    //-> strlen(), strcpy(), memcpy().
#include <sys/mman.h>  // -> Memory manager

int main()
{
    int *memoria = mmap(NULL, 3 * sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);

    pid_t hijo1;
    pid_t hijo2;

    // 🔹 PRIMER FORK (HIJO 1)
    hijo1 = fork();

    if (hijo1 < 0)
    {
        perror("Error al crear el fork!");
        exit(EXIT_FAILURE);
    }
    else if (hijo1 == 0)
    { // PROCESO HIJO 1
        memoria[0] = 5 * 5;
        exit(0);
    }

    // SEGUNDO FORK (HIJO 2) SOLO LO EJECUTA EL PADRE
    hijo2 = fork();

    if (hijo2 < 0)
    {
        perror("Error al crear el fork!");
        exit(EXIT_FAILURE);
    }
    else if (hijo2 == 0)
    { // PROCESO HIJO 2
        memoria[1] = 5 * 5 * 5;
        exit(0);
    }

    // SOLO PADRE ORIGINAL LLEGA AQUÍ

    wait(NULL);
    wait(NULL);

    memoria[2] = memoria[0] + memoria[1];

    printf("Resultado: %d + %d = %d\n", memoria[0], memoria[1], memoria[2]);

    return 0;
}