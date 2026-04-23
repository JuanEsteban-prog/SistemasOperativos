## Procesos
- Todos los procesos tienen al menos un hilo.
- Un proceso es una instancia independiente de un programa en ejecución. Cada proceso tiene su propio espacio de memoria.

Para crear un proceso hay que hacer lo siguiente:
```c
#include <stdio.h>
#include <unistd.h>

int main() {
    pid_t pid = fork();

    if (pid == 0) {
        // Código del proceso hijo
        printf("Soy el proceso hijo\n");
    } else if (pid > 0) {
        // Código del proceso padre
        printf("Soy el proceso padre\n");
    } else {
        // Error
        printf("Error al crear el proceso\n");
    }

    return 0;
}
```
### Explicación
- fork() crea una copia del proceso actual.

    - Devuelve:
        - 0 → en el hijo
        - PID del hijo → en el padre
        - -1 → error

## Hilo
Un hilo es una unidad de ejecución dentro de un proceso. A diferencia de los procesos:
- Comparten memoria global
- Comparten variables
- Comparten archivos abiertos

Hay que usar la siguiente librería:
``` c
#include <pthread.h>
```
Su estructura básica es:
```c
pthread_create(&hilo, NULL, funcion, argumento);
```

Ejemplo
```c
#include <stdio.h>
#include <pthread.h>

void* imprimir(void* arg) {
    int num = *(int*)arg;
    printf("Hilo número: %d\n", num);
    return NULL;
}

int main() {
    pthread_t hilos[3];
    int args[3] = {1, 2, 3};

    for (int i = 0; i < 3; i++) {
        pthread_create(&hilos[i], NULL, imprimir, &args[i]);
    }

    for (int i = 0; i < 3; i++) {
        pthread_join(hilos[i], NULL);
    }

    return 0;
}
```
