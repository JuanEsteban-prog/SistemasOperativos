#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

#define LIMITE 10

pthread_barrier_t barrera;
// Array de semáforos para controlar el turno de finalización
sem_t semaforos[LIMITE];
pthread_t array[LIMITE];

void calcula()
{
    long long unsigned t;
    for (t = 0; t < (0xFFFFFFF); t++)
        ;
}

void *creaThread(void *arg)
{
    int numero_hilo = *(int *)arg;
    int indice = numero_hilo - 1; // Índice de 0 a 9
    pthread_t id_hilo = pthread_self();

    // 1. EL NACIMIENTO
    printf("He nacido. Soy el hilo %d con ID %lu\n", numero_hilo, (unsigned long)id_hilo);

    // 2. LA ESPERA (Barrera para que todos nazcan primero)
    pthread_barrier_wait(&barrera);

    // 3. EL TRABAJO
    calcula();

    // 4. CONTROL DE SALIDA EN ORDEN INVERSO (10 -> 1)
    // El hilo 10 no espera a nadie, los demás esperan al anterior (i+1)
    if (numero_hilo < LIMITE)
    {
        sem_wait(&semaforos[indice]);
    }

    printf("El hilo número %d con ID %lu acaba su ejecución.\n", numero_hilo, (unsigned long)id_hilo);

    // Al terminar, el hilo actual le da paso al siguiente en orden descendente
    if (numero_hilo > 1)
    {
        sem_post(&semaforos[indice - 1]);
    }

    free(arg);
    pthread_exit(NULL);
}

int main(void)
{
    pthread_barrier_init(&barrera, NULL, LIMITE);

    // Inicializamos los semáforos en 0 (bloqueados)
    for (int i = 0; i < LIMITE; i++)
    {
        sem_init(&semaforos[i], 0, 0);
    }

    for (int i = 0; i < LIMITE; i++)
    {
        int *arg = malloc(sizeof(int));
        *arg = i + 1;
        pthread_create(&array[i], NULL, creaThread, arg);
        usleep(10000);
    }

    for (int i = LIMITE - 1; i >= 0; i--)
    {
        pthread_join(array[i], NULL);
    }

    // Limpieza
    pthread_barrier_destroy(&barrera);
    for (int i = 0; i < LIMITE; i++)
    {
        sem_destroy(&semaforos[i]);
    }

    printf("EL ÚLTIMO HILO EN NACER FUE EL PRIMERO EN TERMINAR.\n");
    return 0;
}
