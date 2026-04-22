	#include <stdio.h>
	#include <stdlib.h>
	#include <unistd.h>
	#include <sys/mman.h>
	#include <sys/wait.h>
	#include <sys/types.h>

	#define NUM_HIJOS 4
	#define INCREMENTOS 100000

	int main(void) {
		// Paso 1 — Crear memoria compartida
		// Usamos mmap para que el entero sea visible por todos los procesos hijos
		int *contador = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, 
							 MAP_SHARED | MAP_ANONYMOUS, -1, 0);

		if (contador == MAP_FAILED) {
			perror("Error en mmap");
			exit(EXIT_FAILURE);
		}

		*contador = 0; 

		printf("=== INICIO ===\n");
		printf("Lanzando %d hijos, cada uno hará %d incrementos...\n", NUM_HIJOS, INCREMENTOS);

		// Paso 2 — Crear los procesos hijos
		for (int id = 1; id <= NUM_HIJOS; id++) {
			pid_t pid = fork();

			if (pid < 0) {
				perror("Error en fork");
				exit(EXIT_FAILURE);
			} 
			else if (pid == 0) {
				// Lógica del PROCESO HIJO
				for (int i = 0; i < INCREMENTOS; i++) {
					*contador = *contador + 1;
				}
				// Finalizar enviando su ID (1, 2, 3 o 4)
				exit(id);
			}
		}

		// Paso 3 — Recoger a los hijos con wait
		int status;
		pid_t pid_finalizado;
		
		for (int i = 1; i <= NUM_HIJOS; i++) {
			pid_finalizado = wait(&status);

			if (WIFEXITED(status)) {
				int id_hijo = WEXITSTATUS(status);
				printf("Posición de finalización %d: El hijo con ID interno %d (PID %d) ha terminado.\n", 
						i, id_hijo, pid_finalizado);
			}
		}

		// Paso 4 — Mostrar el resultado del contador
		int valorEsperado = INCREMENTOS * NUM_HIJOS;
		int valorObtenido = *contador;
		int perdidos = valorEsperado - valorObtenido;

		printf("\n== Resultado del contador compartido ==\n");
		printf("Valor esperado: %d\n", valorEsperado);
		printf("Valor obtenido: %d\n", valorObtenido);
		printf("Incrementos perdidos: %d\n", perdidos);

		// Paso 5 — Liberar los recursos
		if (munmap(contador, sizeof(int)) == -1) {
			perror("Error en munmap");
		}

		return 0;
	}
