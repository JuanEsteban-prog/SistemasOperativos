#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

// Variable global para contar Ctrl+C
static volatile sig_atomic_t contador_sigint = 0;

// Manejador de SIGINT
void manejador_sigint(int sig) {
    contador_sigint++;

    if (contador_sigint == 1) {
        printf("\nBuen intento... tienes que aplastar 2 veces más Ctrl+C para finalizar el programa.\n");
    }
    else if (contador_sigint == 2) {
        printf("\nYa casi... pulsa Ctrl+C 1 vez más para salir.\n");
    }
    else {
        printf("\nSe ha pulsado Ctrl+C 3 veces. Finalizando programa...\n");
        exit(0);
    }
}

int main() {

    // Registrar el manejador
    if (signal(SIGINT, manejador_sigint) == SIG_ERR) {
        perror("Error al configurar signal");
        return 1;
    }

    printf("Programa iniciado.\n");
    printf("Pulsa Ctrl+C tres veces para salir.\n\n");

    // Bucle infinito
    while (1) {

        // Mostrar PID constantemente
        printf("PID del proceso: %d\n", getpid());

        // Forzar impresión inmediata
        fflush(stdout);

        // Esperar 1 segundo
        sleep(1);
    }

    return 0;
}
