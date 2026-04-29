#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>

#define LIMITE 10 // Limite de la cantidad de hilos

void calcula()
{
    long long unsigned t;
    for (t = 0; t < (0xFFFFFFF); t++)
        ;
}

pthread_t array[LIMITE];
int n = 1;

// Implementación de la función que ejecuta cada hilo
void *creaThread(void *arg)
{
    // Recuperamos el número del hilo enviado como argumento
    int numero_hilo = *(int *)arg;

    // Obtenemos el ID real del hilo (pthread_t)
    pthread_t id_hilo = pthread_self();

    // Mensaje de inicio (hacemos un cast a unsigned long long para evitar warnings al imprimir el ID)
    printf("He nacido. Soy el hilo %d con ID %llu\n", numero_hilo, (unsigned long long)id_hilo);

    // Llamamos a la función de retardo/trabajo
    calcula();

    // Mensaje de finalización
    printf("El hilo número %d con ID %llu acaba su ejecución.\n", numero_hilo, (unsigned long long)id_hilo);

    // Liberamos la memoria del argumento que reservamos en el main
    free(arg);

    pthread_exit(NULL);
}

int main(void)
{

    // 1. Bucle para crear los hilos
    for (int i = 0; i < LIMITE; i++)
    {
        // Reservamos memoria para pasar el número 'n' de forma segura a cada hilo
        int *arg = malloc(sizeof(int));
        *arg = n;
        n++;

        // Creamos el hilo y le pasamos el puntero con su número correspondiente
        if (pthread_create(&array[i], NULL, creaThread, arg) != 0)
        {
            perror("Error al crear el hilo");
            return 1;
        }
    }

    // 2. Bucle para esperar a que todos los hilos terminen
    // Si no hacemos pthread_join, el main terminará y cerrará los hilos prematuramente
    for (int i = 0; i < LIMITE; i++)
    {
        pthread_join(array[i], NULL);
    }

    return 0;
}