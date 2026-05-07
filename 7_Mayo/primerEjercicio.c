#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>

// Variable global para contar Ctrl+C
static volatile sig_atomic_t contador = 0;

// Manejador de SIGINT
void manejador_sigint(int sig) {
    contador++;
}

int main() {

    // Registrar manejador
    if (signal(SIGINT, manejador_sigint) == SIG_ERR) {
        perror("Error al configurar signal");
        return 1;
    }

    printf("Programa iniciado.\n");
    printf("Pulsa Ctrl+C tres veces para salir.\n\n");

    // Para evitar repetir mensajes
    int ultimo_mensaje = 0;

    while (1) {

        printf("PID del proceso: %d\n", getpid());

        // Detectar cambio en contador
        if (contador != ultimo_mensaje) {

            ultimo_mensaje = contador;

            if (contador == 1) {

                char mensaje[] =
                    "\nBuen intento... tienes que aplastar 2 veces más Ctrl+C.\n";

                write(STDOUT_FILENO, mensaje, strlen(mensaje));
            }
            else if (contador == 2) {

                char mensaje[] =
                    "\nYa casi... pulsa Ctrl+C 1 vez más.\n";

                write(STDOUT_FILENO, mensaje, strlen(mensaje));
            }
            else if (contador >= 3) {

                char mensaje[] =
                    "\nSe ha pulsado Ctrl+C 3 veces. Finalizando...\n";

                write(STDOUT_FILENO, mensaje, strlen(mensaje));

                exit(0);
            }
        }

        sleep(1);
    }

    return 0;
}
