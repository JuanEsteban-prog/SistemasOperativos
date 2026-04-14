/*
1.- El proceso A(abuelo) debe hacer un fork() para crear el proceso B(Padre).
2.- El proceso B a su vez, ebe hacer un fork() para crear el proceso C(nieto).
3.- El proceso C debe generar un numero aleatorio entre 1 y 10, imprimirlo("Soy el nieto, y mi número es X").
4.- El proceso B debe usar wait() para recoger el estado de C(usando WEXITSTATUS).
    Luego debe multiplicar ese número por 2, imprimirlo("Soy el padre, mi hijo dió X, lo multiplico y devuelo Y") y devolverlo con exit(Y).
5.- El proceso A debe esperar al proceso B, recoger el estado y mostrar el mensaje final("Soy el abuelo y el valor final de mi linaje es Z")
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

    pid_t pid_B = fork();

    if (pid_B < 0)
    {
        perror("Error en la creción del proceso B!!!!");
        exit(EXIT_FAILURE);
    }
    else if (pid_B == 0)
    { // Proceso B (Padre)
        pid_t pid_C = fork();

        if (pid_C < 0)
        {
            perror("Error en la creación del proceso C!!!!");
            exit(EXIT_FAILURE);
        }
        else if (pid_C == 0)
        { // Proceso C (Nieto)

            int numeroAleatorio = ((rand() % 10) + 1);
            printf("Soy el nieto, y mi número es: %d\n", numeroAleatorio);

            exit(numeroAleatorio);
        }
        else if (pid_C > 0)
        {
            int estado;
            wait(&estado);

            int numeroRecibido = WEXITSTATUS(estado);

            int numeroPadre = numeroRecibido * 2;

            printf("Soy el proceso Padre, mi hijo me dio %d, lo multiplico y devuelvo %d\n", numeroRecibido, numeroPadre);

            exit(numeroPadre);
        }
    }
    else if (pid_B > 0)
    {
        int resultadoRecibido;
        wait(&resultadoRecibido);

        int valorFinal = WEXITSTATUS(resultadoRecibido);

        printf("Soy el abuelo, y el valor final de mi linaje es: %d", valorFinal);
    }

    return 0;
}