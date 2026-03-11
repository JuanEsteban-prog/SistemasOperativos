#include <stdio.h>
#include <unistd.h>

int main(){

    puts("Esta línea sol la ejecuta el proceso padre");

    //A partir de aquí dos procesos se ejecutan!
    fork();
    puts("Esta línea la ejecuta el proceso padre y el hijo... pero quién es quién?");
    return 0;
}