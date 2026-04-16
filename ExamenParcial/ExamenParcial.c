#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/wait.h>

#define NUM_HIJOS 4
#define INCREMENTOS 100000

int main(void)
{

	int *contador = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);

	if (contador == MAP_FAILED)
	{
		perror("mmap");
		exit(EXIT_FAILURE);
	}

	*contador = 0;

	pid_t hijo1 = fork();

	if (hijo1 < 0)
	{
		perror("Error en la creacion del fork");
		exit(EXIT_FAILURE);
	}
	else if (hijo1 == 0)
	{
		// PROCESO HIJO1
		// Ejecutar un bucle de 100.000 iteraciones.
		for (int i = 0; i <= INCREMENTOS; i++)
		{
			*contador = *contador + 1;
		}
		exit(0);
	}
	else if (hijo1 > 0)
	{ // PROCESO PADRE
		pid_t hijo2 = fork();
		pid_t hijo3 = fork();
		pid_t hijo4 = fork();

		if (hijo2 < 0)
		{
			perror("Error en la creacion del fork");
			exit(EXIT_FAILURE);
		}
		else if (hijo2 == 0)
		{
			// PROCESO HIJO2
			for (int i = 0; i <= INCREMENTOS; i++)
			{
				*contador = *contador + 1;
			}
			exit(0);
		}

		if (hijo3 < 0)
		{
			perror("Error en la creacion del fork");
			exit(EXIT_FAILURE);
		}
		else if (hijo3 == 0)
		{
			// PROCESO HIJO3
			for (int i = 0; i <= INCREMENTOS; i++)
			{
				*contador = *contador + 1;
			}
			exit(0);
		}

		if (hijo4 < 0)
		{
			perror("Error en la creacion del fork");
			exit(EXIT_FAILURE);
		}
		else if (hijo4 == 0)
		{
			// PROCESO HIJO4
			for (int i = 0; i <= INCREMENTOS; i++)
			{
				*contador = *contador + 1;
			}
			exit(0);
		}
		printf("=== INICIO ===\n");
		printf("Lanzando 4 hijos, cada uno hará 100000 incrementos\n");

		wait(NULL);
		wait(NULL);
		wait(NULL);
		wait(NULL);

		printf("== Resultado del contador compartido ==\n ");

		int valorEsperado = INCREMENTOS * NUM_HIJOS;

		printf("Valor esperado: %d\n", valorEsperado);
		printf("Valor obtenido: %d\n", *contador);
		int incrementosPerdidos = (INCREMENTOS * NUM_HIJOS) - *contador;
		printf("Incrementos perdidos por la condición de carrera: %d\n", incrementosPerdidos);

		exit(0);
	}

	munmap(contador, sizeof(int)); // Liberar la memoria compartida.
	return 0;
}
