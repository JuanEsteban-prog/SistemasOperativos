#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <pthread.h>

// Variables globales
int n;
long unsigned int t1 = 0, t2 = 1, siguiente, calcula_primo;
pthread_t hilo_fibonacci, hilo_primo;

// Función para calcular la serie de Fibonacci
void* fibonacci(void* arg) {
    printf("--- Hilo Fibonacci iniciado ---\n");
    printf("Serie: ");
    
    for (int i = 1; i <= n; ++i) {
        printf("%lu ", t1);
        calcula_primo = t1; // Guardamos el valor actual para que el otro hilo lo use si se desea
        siguiente = t1 + t2;
        t1 = t2;
        t2 = siguiente;
    }
    printf("\n--- Hilo Fibonacci terminado ---\n\n");
    pthread_exit(NULL);
}

// Función para verificar si el último número calculado es primo
void* es_primo(void* arg) {
    printf("--- Hilo Primo iniciado ---\n");
    int i, flag = 0;
    
    // Usamos el valor de 'calcula_primo' (el último de la serie)
    unsigned long num = calcula_primo;

    if (num <= 1) {
        flag = 1; 
    } else {
        for (i = 2; i <= num / 2; ++i) {
            if (num % i == 0) {
                flag = 1;
                break;
            }
        }
    }

    if (flag == 0)
        printf("El número %lu es PRIMO.\n", num);
    else
        printf("El número %lu NO es primo.\n", num);

    printf("--- Hilo Primo terminado ---\n");
    pthread_exit(NULL);
}

int main() {
    printf("¿Cuántos términos de la serie Fibonacci deseas calcular? ");
    if (scanf("%d", &n) <= 0) return 1;

    // 1. Creamos el hilo de Fibonacci
    if (pthread_create(&hilo_fibonacci, NULL, fibonacci, NULL)) {
        fprintf(stderr, "Error creando el hilo de Fibonacci\n");
        return 1;
    }

    // Esperamos a que termine el hilo de Fibonacci para tener el número final
    pthread_join(hilo_fibonacci, NULL);

    // 2. Creamos el hilo para verificar si el último número es primo
    if (pthread_create(&hilo_primo, NULL, es_primo, NULL)) {
        fprintf(stderr, "Error creando el hilo de Primo\n");
        return 1;
    }

    // Esperamos a que termine el hilo de verificación de primos
    pthread_join(hilo_primo, NULL);

    printf("\nPrograma finalizado con éxito.\n");
    return 0;
}