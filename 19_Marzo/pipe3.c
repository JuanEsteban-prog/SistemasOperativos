/*Creamos un hijo, papá va a crear 10 números aleatorios y se los envía uno a uno al hijo. 
El Hijo va a averiguar cuáles son los números primos, lo va a mostar por pantalla y devuelve al padre el totoal de primos que ha encontrado.
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>
#include <ctype.h>//tolower(char) -> convierte los caracteres en minúscula.
#include <string.h>

int main(){
    
    int num;
    srand(time(NULL));

    for(int i = 0; i < 10; i++){
        num = rand()%100 + 1; //La función rand genera un número aleatorio dentro de un rago. %100 hace que sepamos que el número va de 0 a 100, y si queremos que comience desde 1 le sumamos 1. 
        printf("%d\n", num);
    }

    return 0;
}