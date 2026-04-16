/*
: Tienes PROHIBIDO usar printf, scanf o strlen en todo el programa,
excepto en el último paso del Comandante (el Abuelo). Todo lo demás debe hacerse con llamadas al sistema puras (write, read) y punteros.

Se requiere desarrollar una aplicación en C que calcule el factorial de una serie de números.
El objetivo es practicar la creación de procesos, el uso de tuberías (pipes) para la comunicación y la sincronización básica.

1.- Datos iniciales:
    - Define un array de 5 números enteros.
    - El proceso padre debe llenar este array con números aleatorios entre 1 y 10 y mostrarlos por pantalla.
2.- Creación de proceso:
    - El padre debe crear un proceso hijo mediante fork().
    - El padre debe esperar a que el hijo termine antes de mostrar los resultados finales (wait).
3.- Procesamiento en el hijo:
    - El proceso hijo no debe usar hilos. En su lugar, debe recorrer el array de números recibidos por el padre(por herencia de memoria)
    y calcular el factorial de cada uno de ellos.
4.- Comunicación:
    - Crea in pipe antes del fork().
    - El proceso hijo debe enviar el array de resultados al proceso padre a través del pipe.
5.- Salida padre:
    - Una vez que el padre recibe los datos del pipe, debe imprimir: "Resultado recibido: El factorial de [número] es [resultado]".
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <string.h>
#include <time.h>

int main()
{
    srand(time(NULL));

    int pipe1[2];
    int numeros[5];

    for (int i = 0; i < 5; i++)
    {
        numeros[i] = (rand() % 10) + 1;
        printf("%d", numeros[i]);
    }

    pid_t pid;

    if (pipe(pipe1) == -1)
    {
        perror("Error al crear la tuberia!");
        exit(EXIT_FAILURE);
    }

    pid = fork();

    if (pid < 0)
    {
        perror("Error al hacer fork!");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0)
    { // Proceso hijo
        close(pipe1[0]);
        long resultados[5];
        for (int i = 0; i < 5; i++)
        {
            int num_actual = numeros[i];
            long calculo_factorial = 1;
            for (int j = 1; j <= num_actual; j++)
            {
                calculo_factorial = calculo_factorial * j;
            }
            resultados[i] = calculo_factorial;
        }

        write(pipe1[1], resultados, sizeof(long) * 5);

        close(pipe1[1]);
        exit(0);
    }
    else if (pid > 0)
    { // Proceso Padre
        close(pipe1[1]);
        long resultados_recibidos[5];
        read(pipe1[0], resultados_recibidos, sizeof(long) * 5);
        wait(NULL);
        for (int i = 0; i < 5; i++)
        {
            printf("Resultado recibido: El factorial de %d es %ld\n", numeros[i], resultados_recibidos[i]);
        }
    }

    return 0;
}