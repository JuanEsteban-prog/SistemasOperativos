#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <sys/types.h>

#define NUM_HIJOS 4
#define INCREMENTOS 100000

int main(void) {
    // Paso 1 — Crear una memoria compartida
    int *contador = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, 
                         MAP_SHARED | MAP_ANONYMOUS, -1, 0);

    if (contador == MAP_FAILED) {
        perror("mmap");
        exit(EXIT_FAILURE);
    }

    *contador = 0; // Inicializado a 0

    // Salida inicial según formato solicitado
    printf("=== INICIO ===\n");
    printf("valor inicial del contador : %d\n", *contador);
    printf("Lanzando %d hijos, cada uno hará %d incrementos.....\n\n", NUM_HIJOS, INCREMENTOS);

    // Paso 2 — Crear los procesos hijos
    for (int i = 1; i <= NUM_HIJOS; i++) {
        pid_t pid = fork();

        if (pid < 0) {
            perror("Error en el fork");
            exit(EXIT_FAILURE);
        } 
        else if (pid == 0) {
            // PROCESO HIJO
            for (int j = 0; j < INCREMENTOS; j++) {
                *contador = *contador + 1;
            }
            // Enviamos su número de identificación (1, 2, 3 o 4)
            exit(i);
        }
    }

    // Paso 3 — Recoger a los hijos con wait
    printf("=== Orden de finalización de los hijos ===\n");
    
    int status;
    pid_t pid_hijo;
    for (int i = 1; i <= NUM_HIJOS; i++) {
        pid_hijo = wait(&status); // El padre espera a cualquier hijo

        if (WIFEXITED(status)) {
            int id_interno = WEXITSTATUS(status);
            printf("Posicion %d: termino el Hijo %d (PID %d)\n", i, id_interno, pid_hijo);
        }
    }

    // Paso 4 — Mostrar el resultado del contador
    int valorEsperado = NUM_HIJOS * INCREMENTOS;
    int valorObtenido = *contador;
    int perdidos = valorEsperado - valorObtenido;

    printf("\n== Resultado del contenedor compartido ==\n");
    printf("Valor esperado: %d\n", valorEsperado);
    printf("Valor obtenido: %d\n", valorObtenido);
    printf("incrementos perdidos por la condición de carrera: %d\n", perdidos);

    // Paso 5 — Liberar los recursos
    munmap(contador, sizeof(int));

    return 0;
}