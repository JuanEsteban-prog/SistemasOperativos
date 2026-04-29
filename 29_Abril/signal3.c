#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void manejador(int signum)
{
    puts("Dentro del manejador de señales");
}

int main()
{

    signal(SIGUSR1, manejador);
    puts("Dentro del main");
    raise(SIGUSR1); // hace que nos lanzemos la señal a nosotros mismos.
    puts("De nuevo dentro de la main");

    return 0;
}