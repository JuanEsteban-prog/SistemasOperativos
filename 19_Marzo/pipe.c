// Creamos tubería, proceso hijo, el hijo se queda a la espera mientras que el padre lee dos números, después se lo envía al hijo. Envíamos los números según lo lee. Cuando recibimos todo el hijo hace la suma y muestra el resultado. El hijo muere antes que el hijo
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>

int main(){

    pid_t hijo;
    int tuberia[2];

    int primerNumero, segundoNumero;
    hijo = fork();

    if(hijo == -1){
        perror("Error en el fork!");
        exit(1);
    }else if(hijo == 0){
        close(tuberia[1]); 

        read(tuberia[0], &primerNumero, sizeof(primerNumero));
        read(tuberia[0], &segundoNumero, sizeof(segundoNumero));

        int suma = primerNumero + segundoNumero;

        printf("Hijo: La suma es %d\n", suma);

        close(tuberia[0]); 
        exit(0);
    }else if(hijo > 0){
        close(tuberia[0]); 

        printf("Introduce el primer numero: ");
        scanf("%d", &primerNumero);
        write(tuberia[1], &primerNumero, sizeof(primerNumero)));

        printf("Introduce el segundo numero: ");
        scanf("%d", &segundoNumero);
        write(tuberia[1], &segundoNumero, sizeof(segundoNumero));
        wait(NULL);

        close(tuberia[1]); 

        printf("Padre: El hijo ha terminado\n");
    }

    return 0;
}
