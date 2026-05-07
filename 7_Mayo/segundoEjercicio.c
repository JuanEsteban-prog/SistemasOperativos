#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

static volatile sig_atomic_t monedas = 0;

void manejador_moneda(int sig) {
    monedas++;
}

int main() {

    signal(SIGUSR1, manejador_moneda);

    printf("Máquina de café iniciada.\n");
    printf("Envía monedas usando SIGUSR1.\n\n");

    int monedas_mostradas = 0;

    while (1) {

        printf("Máquina encendida. Esperando monedas... (PID: %d)\n",
               getpid());

        // Detectar nuevas monedas
        if (monedas != monedas_mostradas) {

            monedas_mostradas = monedas;

            if (monedas == 1 || monedas == 2) {

                printf("¡Clinc! Moneda recibida. "
                       "Llevas %d/3 monedas.\n",
                       monedas);
            }
            else if (monedas >= 3) {

                printf("¡Perfecto! Ya tienes 3 monedas.\n");
                printf("Sirviendo café...\n");
                printf("Gracias por usar la máquina de café.\n");

                exit(0);
            }
        }

        sleep(3);
    }

    return 0;
}
