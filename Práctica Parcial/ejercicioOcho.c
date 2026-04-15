/*
En base al programa minishell.c hecho el 18 de Marzo:
1.- El programa principal pide al usuario que ingrese una opción: 1 para ver archivos, 2 para ver procesos.
2.- Si elige 1, el Padre hace un fork(). El hijo ejecutará execlp("ls", "ls", "-l", NULL);.
3.- Si elige 2, el Padre hace un fork(). El hijo ejecutará execlp("ps", "ps", "-f", NULL);.
4.- Si elige otra cosa, imprime un error.
5.- Sea cual sea el comando,
el Padre siempre debe usar wait(NULL) para esperar a que el comando termine antes de imprimir "Comando finalizado con éxito." y salir.
*/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <string.h>

#define VERSION 0.1

int main()
{

    int opcion;
    char comando[20];
    pid_t pid;

    printf("Introduce 1 para ver archivos o Introduce 2 para ver procesos: ");
    scanf("%d", opcion);

    pid = fork();
    if (pid == 0)
    {
        if (opcion == 1)
        {
            execlp("ls", "ls", "-l", NULL);
        }
        else if (opcion == 2)
        {
            execlp("ps", "ps", "-f", NULL);
        }
        else
        {
            perror("Tecla no reconocida!");
        }
    }
    else if (pid > 0)
    {
        wait(NULL);
        printf("Comando finalizado con exito \n");
    }
}