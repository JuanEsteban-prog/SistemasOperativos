#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <signal.h> //-> Libreria donde esta todo el trabajo de las señales

void manejador(int signum);

int main()
{
    signal(SIGINT, manejador); // signal, hace que cuando el sistema operativo reciba la señal sigqquit, nos la pasa a nosotros para que la manejemos, entonces cuando aplastamos control + c para intentar parar el programa, lo que pasará es que la consola nos mostrará el mensaje que te jodan.

    while (true)
    {
        puts("Hola amiguitos, aqui estoy pasando el rato");
        sleep(2);
    }

    return 0;
}

void manejador(int signum)
{
    puts("Que te jodan");
}