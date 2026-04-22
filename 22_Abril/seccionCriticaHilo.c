/*Tenemos que hacer un programa de secciones críticas sin procesos, tenemos que utilizar hilos en su lugar0*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define LIMITE 1000000
int variable_compartida;
pthread_t suma, resta;

void function_suma(void* arg){
    for(int i = 0; i < LIMITE; i++){
        variable_compartida = variable_compartida + 1;
    }
    return NULL;
}

void function_resta(void* arg){
    for(int i = 0; i < LIMITE; i++){
        variable_compartida = variable_compartida - 1;
    }
    return NULL;
}

int main(void)
{
    variable_compartida = 0;
    pthread_create(&suma, NULL; &funcion_suma, NULL); // Creamos los hilos
    pthread_create(&resta, NULL; &funcion_resta, NULL); // Creamos los hilos
    pthraed_join(resta, NULL);
    pthraed_join(suma, NULL);

    printf("El valor de la variable es %d\n", variable_compartida);
}
