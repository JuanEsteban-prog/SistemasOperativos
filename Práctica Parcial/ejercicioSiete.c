/*
1.- Crear pipe1 y pipe2
2.- El Abuelo (A) pide una palabra por teclado y se lo envia al Padre(B) a traves del pipe1.
3.- El Padre(B) lee la palabra, la concatena la terminacion UNIX y se la envia al nieto (C) a traves del pipe2.
4.- El nieto (C) lee el pipe2 y lo muestra por pantalla.
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <string.h>

int main()
{

    int pipe1[2];
    int pipe2[2];

    if (pipe(pipe1) == -1 || pipe(pipe2) == -1)
    {
        perror("Error al crear la tuberia");
        exit(EXIT_FAILURE);
    }

    pid_t procesoB = fork();

    if (procesoB < 0)
    {
        perror("Error al crear el Fork!");
        exit(EXIT_FAILURE);
    }
    else if (procesoB == 0)
    { // Proceso Padre (B)
        pid_t procesoC = fork();

        if (procesoC < 0)
        {
            perror("Error al crear el Fork!");
            exit(EXIT_FAILURE);
        }
        else if (procesoC == 0)
        { // Proceso Nieto (C)
            close(pipe1[0]);
            close(pipe1[1]);
            close(pipe2[1]);
            char mensajeRecibidoNieto[100];

            read(pipe2[0], mensajeRecibidoNieto, sizeof(mensajeRecibidoNieto));

            printf("El mensaje recibido por el nieto es: %s\n", mensajeRecibidoNieto);
            exit(0);
        }
        else if (procesoC > 0) // Proceso Padre (B)
        {
            close(pipe1[1]);
            close(pipe2[0]);
            char mensajeRecibidoPadre[100];

            read(pipe1[0], mensajeRecibidoPadre, sizeof(mensajeRecibidoPadre));
            strcat(mensajeRecibidoPadre, "UNIX");

            write(pipe2[1], mensajeRecibidoPadre, strlen(mensajeRecibidoPadre) + 1);
            wait(NULL);
        }
    }
    else if (procesoB > 0)
    { // Proceso Abuelo (A)
        close(pipe1[0]);
        close(pipe2[0]);
        close(pipe2[1]);

        char palabraUsuario[50];

        printf("Escribe una palabra cualquiera: ");
        scanf("%s", palabraUsuario);

        write(pipe1[1], palabraUsuario, strlen(palabraUsuario) + 1);

        wait(NULL);
    }

    return 0;
}