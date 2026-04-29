#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void sig_handler_padre(int signum)
{
    printf("Padre: recibe una señal de respuesta del chaval\n");
}

void sig_handler_hijo(int sigum)
{
    printf("Hijo: recibida señal del padre\n");
    sleep(1);
    kill(getppid(), SIGUSR1); // getppid -> saca el id de su padre
}

int main()
{
    pid_t pid;
    pid = fork();

    if (pid == 0)
    {                                      // Proceso hijo(registra la señal SIGUSER1 para si)
        signal(SIGUSR1, sig_handler_hijo); // Solo la ejecuta el proceso hijo, no el proceso padre. EL hijo cuando reciba la señal SIGUSER1, se va a la función sig_handler_hijo.
        printf("Hijo: a la espera de una señal\n");
        pause();
    }
    else
    { // Proceso padre. Ahora registramos la señal SIGUSER1 para el padre
        signal(SIGUSR1, sig_handler_padre);
        sleep(1);
        kill(pid, SIGUSR1);
        printf("Padre: ...me quedo a la espera de una repsuesta del chaval \n");
        pause();
    }

    return 0;
}