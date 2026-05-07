#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

// Variable global para contar monedas
static volatile sig_atomic_t monedas = 0;

// Manejador de la señal SIGUSR1
void manejador_moneda(int sig) {

    monedas++;

    if (monedas < 3) {
        write("\n¡Clinc! Moneda recibida. Llevas %d/3 monedas.\n", monedas);
    }
    else {
        write("\n¡Perfecto! Ya tienes 3 monedas.\n");
        write("Sirviendo café...\n");
        write("Gracias por usar la máquina de café.\n");
        exit(0);
    }
}

int main() {

    // Configurar el manejador para SIGUSR1
    if (signal(SIGUSR1, manejador_moneda) == SIG_ERR) {
        perror("Error al configurar signal");
        return 1;
    }

    write("Máquina de café iniciada.\n");
    write("Envía monedas usando señales SIGUSR1.\n\n");

    // Bucle principal
    while (1) {

        write("Máquina encendida. Esperando monedas... (Mi PID es %d)\n", getpid());

        // Mostrar inmediatamente en pantalla
        fflush(stdout);

        // Esperar 3 segundos
        sleep(3);
    }

    return 0;
}
