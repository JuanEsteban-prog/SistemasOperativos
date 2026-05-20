#include <studio.h>
#include <unistd.h>
#include <pthread.h>
#include <signal.h>

//Versión de hilos

#define ROWS 4
#define COLS 3

int matrix[ROWS][COLS], ipos, jpos, temp;
pthread_t positivo, negativo, coordinador_thread;

void muestra_tabular();
void postivo_handler(int);
void negativo_handler(int);
void coordinador_handler(int);
void* negativo_f();
void* positivo_f();
void* coordinador_thread_f();

int main(){

}