// Instrucción atómica -> No puede interrumpirse hasta que se ejecute.
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <unistd.h>
#include <semaphore.h>
#include <fcntl.h>

#define LIMITE 10000

int main()
{
    pid_t hijo;
    sem_t *semaforo;
    semaforo = sem_open("/mi_semaforo", O_CREAT, S_IRUSR | S_IWUSR, 1); // Creamos el semaforo, estos se crean a nivel de sistema oepertaivo. EL principal parametro es el 1, un semaforo es un objeto del sistema que tiene una especie de cuenta atras(del ultimo parametro que le pasemos nosotros.). Se usa en servidores y bases de datos en la vida real, ya que se usan como estructura del sistema operativo para controlar la cantidad de personas que se conectan al servidor o a la base de datos. En el momento que el semaforo llegue a 0 no deja pasar a nadie mas, se bloquea hasta que alguien se vaya y luego le deja pasar.
    int *variable_compartida = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    *variable_compartida = 0;

    int N; // ← Declarar variable
    hijo = fork();

    if (hijo == 0)
    {
        for (N = 0; N < LIMITE; N++)
        {
            sem_wait(semaforo);                              //-> Llamamos al semaforo
            *variable_compartida = *variable_compartida + 1; // Se produce una condición de carrera. Los procesos están entrando y saliendo constantemente de memoria.
            sem_post(semaforo);                              //-> Liberamos el semaforo(ya acabamos la seccion critica, por lo tanto liberamos el semaforo).
        }
        exit(0);
    }
    else if (hijo > 0)
    {
        for (N = 0; N < LIMITE; N++)
        {
            sem_wait(semaforo);
            *variable_compartida = *variable_compartida - 1; // Se produce una condición de carrera.
            sem_post(semaforo);                              //-> Liberamos el semaforo(ya acabamos la seccion critica, por lo tanto liberamos el semaforo).
        }
        wait(NULL);
        printf("El resultado de este código es: %d\n", *variable_compartida); // ← Desreferenciar puntero
    }

    munmap(variable_compartida, sizeof(int));
    sem_close(semaforo);        //-> Cerramos el semaforo a nivel local, de programa.
    sem_unlink("/mi_semaforo"); //-> Lo cerramos a nivel de sistema operativo.
    return 0;
}
