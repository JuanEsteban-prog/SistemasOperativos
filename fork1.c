#include <stdio.h>
#include <unistd.h>

int main(){

    puts("Esta línea solo la ejecuta el proceso padre");

    //A partir de aquí dos procesos se ejecutan!
    fork();
    puts("Esta línea la ejecuta el proceso padre y el hijo... pero quién es quién?");
    return 0;

    /*Para saber que proceso hace que:
    
    printf("Esta línea la ejecuta el proceso padre, con PID: %d\n", getpid());

    //A partir de aquí dos procesos se ejecutan!
    fork();
    puts("Esta línea la ejecuta el proceso hijo %d\n", getpid());
    return 0;
    */
}