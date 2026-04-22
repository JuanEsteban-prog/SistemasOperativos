#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h> // -> Libreria necesaria para trabajar con hilos.

pthread_t ntid;

void printids(const char *s){
    pid_t pid;
    pthread_t tid;
    pid = getpid();
    tid = pthread_self();
    printf("%s pid %u tid %u\n", s, (unsigned int)pid, (unsigned int)tid);
    return; 
}

void* nuevo_hilo (void *arg){
    printids("Nuevo hilo: ");
    return NULL;
}

int main(void){
    pthread_create(&ntid, NULL, &nuevo_hilo, NULL);
    printids("Hilo principal: ");
    usleep(100);
    return 0;
}