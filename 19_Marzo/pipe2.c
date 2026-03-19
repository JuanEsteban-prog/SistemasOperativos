// Un padre crea a un hijo. El padre tiene un buffer de 100 bytes de caracteres(cadena de 100 caracteres) y le pedimos al usuario que introduzca una cadena por teclado, el padre le envía al hijo la cadena, el hijo cuenta el número de vocales que hay en la cadena y le devuelve al padre ese número, el padre saca en número por pantalla y acaba el programa. 

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>
#include <ctype.h>//tolower(char) -> convierte los caracteres en minúscula.
#include <string.h>

#define MAX_BUFFER 100

int contar_vocales(const char *cadena){
    int contador = 0;
    char c;

    for(int i = 0; cadena[i] != '\0'; i++){
        c = tolower(cadena[i]);
        if(c=='a' || c=='e' || c=='i' || c=='o' || c=='u'){
            contador++;
        }
    }
    return contador;
}

int main(){
    int tuberia[2], tuberia1[2];
    pid_t hijo;

    // Crear tuberías
    if(pipe(tuberia) == -1 || pipe(tuberia1) == -1){
        perror("Error creando tuberías");
        exit(EXIT_FAILURE);
    }

    hijo = fork();

    if(hijo < 0){
        perror("Error creando el proceso hijo");
        exit(EXIT_FAILURE);
    }

    if(hijo > 0){ // PADRE
        char mensaje_enviar[MAX_BUFFER];
        int total_vocales;

        close(tuberia[0]);   // cerrar lectura
        close(tuberia1[1]);  // cerrar escritura

        printf("Escribe un mensaje: ");
        fgets(mensaje_enviar, MAX_BUFFER, stdin);

        // Eliminar salto de línea
        mensaje_enviar[strcspn(mensaje_enviar, "\n")] = 0;

        // Enviar al hijo
        write(tuberia[1], mensaje_enviar, strlen(mensaje_enviar) + 1);
        close(tuberia[1]);

        // Recibir resultado
        read(tuberia1[0], &total_vocales, sizeof(total_vocales));
        close(tuberia1[0]);

        printf("Número de vocales: %d\n", total_vocales);

        wait(NULL);

    }else{ // HIJO
        char mensaje_recibido[MAX_BUFFER];
        int num_vocales;

        close(tuberia[1]);   // cerrar escritura
        close(tuberia1[0]);  // cerrar lectura

        // Leer del padre
        read(tuberia[0], mensaje_recibido, MAX_BUFFER);
        close(tuberia[0]);

        num_vocales = contar_vocales(mensaje_recibido);

        // Enviar resultado al padre
        write(tuberia1[1], &num_vocales, sizeof(num_vocales));
        close(tuberia1[1]);

        exit(EXIT_SUCCESS);
    }

    return 0;
}