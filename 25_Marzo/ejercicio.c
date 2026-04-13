#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

int main()
{
    int pipe1[2];
    int pipe2[2];
    pid_t pid;

    srand(time(NULL));

    if (pipe(pipe1) == -1 || pipe(pipe2) == -1)
    {
        perror("Error al crear las tuberías");
        exit(EXIT_FAILURE);
    }

    pid = fork();

    if (pid == -1)
    {
        perror("Error al crear el proceso hijo con fork()");
        exit(EXIT_FAILURE);
    }

    if (pid == 0)
    {

        close(pipe1[1]);
        close(pipe2[0]);

        int numeros_recibidos[10];
        int suma_total = 0;
        int cantidad_de_pares = 0;

        read(pipe1[0], numeros_recibidos, sizeof(numeros_recibidos));
        close(pipe1[0]);

        for (int i = 0; i < 10; i++)
        {
            suma_total += numeros_recibidos[i];
            if (numeros_recibidos[i] % 2 == 0)
            {
                cantidad_de_pares++;
            }
        }

        write(pipe2[1], &suma_total, sizeof(suma_total));
        close(pipe2[1]);

        exit(cantidad_de_pares);
    }
    else
    {

        close(pipe1[0]);
        close(pipe2[1]);

        int array_numeros[10];

        printf("--- El Padre está generando los números ---\n");
        printf("Array generado: [ ");
        for (int i = 0; i < 10; i++)
        {
            array_numeros[i] = (rand() % 100) + 1;
            printf("%d ", array_numeros[i]);
        }
        printf("]\n\n");

        write(pipe1[1], array_numeros, sizeof(array_numeros));
        close(pipe1[1]);

        int suma_del_hijo;
        read(pipe2[0], &suma_del_hijo, sizeof(suma_del_hijo));
        close(pipe2[0]);

        int status;
        wait(&status);

        if (WIFEXITED(status))
        {
            int pares_extraidos = WEXITSTATUS(status);
            printf("--- Resultados obtenidos por el Padre ---\n");
            printf("Suma total calculada por el hijo: %d\n", suma_del_hijo);
            printf("Cantidad de números pares encontrados: %d\n", pares_extraidos);
        }
        else
        {
            printf("El proceso hijo no terminó de forma normal.\n");
        }
    }

    return 0;
}