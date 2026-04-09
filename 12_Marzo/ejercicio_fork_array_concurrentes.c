/*Define un array de 10 números enteros y un "número objetivo" a buscar.
El proceso principal (Padre) debe crear dos procesos hijos utilizando la llamada al sistema fork().

El Hijo 1 deberá buscar el número objetivo en la primera mitad del array. 

Si lo encuentra, terminará su ejecución devolviendo un estado de éxito(exit(1)).

Si no lo encuentra, terminará devolviendo un estado de fracaso (exit(0)).

El Hijo 2 deberá de hacer lo mismo, pero buscando en la segunda mitad del array.

El proceso Padre sebe usar la llamada al sistema wait() para esperar obligatoriamente a que ambos hijos terminen.

El Padre debe inspeccionar el estado de salida de cada hijo utilizando las macros adecuadas (WIFEXITED y WEXISTATUS)
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    int numeros[10] = {15, 42, 7, 89, 23, 10, 55, 99, 4, 31};
    int objetivo = 55; 

    pid_t pid1, pid2;

    printf("Iniciando búsqueda del número %d...\n", objetivo);

    pid1 = fork();

    if (pid1 < 0) {
        perror("Error al crear el Hijo 1");
        exit(1);
    } 
    else if (pid1 == 0) {
        // --- CÓDIGO DEL HIJO 1 ---
        for (int i = 0; i < 5; i++) {
            if (numeros[i] == objetivo) {
                exit(1); 
            }
        }
        exit(0); 
    }

    pid2 = fork();

    if (pid2 < 0) {
        perror("Error al crear el Hijo 2");
        exit(1);
    } 
    else if (pid2 == 0) {
       
        for (int i = 5; i < 10; i++) {
            if (numeros[i] == objetivo) {
                exit(1); 
            }
        }
        exit(0); 
    }

    // --- CÓDIGO DEL PADRE ---
    
    
    int estado;
    pid_t pid_terminado;
    int encontrado_hijo1 = 0;
    int encontrado_hijo2 = 0;


    for (int i = 0; i < 2; i++) {
        pid_terminado = wait(&estado); 

        if (WIFEXITED(estado)) {
            int codigo_salida = WEXITSTATUS(estado);

            if (pid_terminado == pid1) {
                if (codigo_salida == 1) {
                    encontrado_hijo1 = 1;
                }
            } else if (pid_terminado == pid2) {
                if (codigo_salida == 1) {
                    encontrado_hijo2 = 1;
                }
            }
        }
    }

    printf("--- RESULTADOS ---\n");
    if (encontrado_hijo1) {
        printf("El número %d fue ENCONTRADO por el Hijo 1 (primera mitad del array).\n", objetivo);
    } else if (encontrado_hijo2) {
        printf("El número %d fue ENCONTRADO por el Hijo 2 (segunda mitad del array).\n", objetivo);
    } else {
        printf("El número %d NO fue encontrado en el array.\n", objetivo);
    }

    return 0;
}