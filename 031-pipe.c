#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <wait.h>
#include <stdlib.h>

//Una tubería para linux es un array de enteros de dos elementos
//Pipe transforma el array en una potente herramienta para el sistema operativo, que es una tubería.
//Si queremos mandar algo por la tubería tenemos que utilizar el elemento 1.
//Si queremos escuchar algo por la tubería tenemos que utilizar el elemento 0.
//Siempre tenemos que cerrar el lado que no vamos a utilizar. Es decir, si vamis a escribir(1), tenemos que cerrar el lado del que escucha(0).
int main(){

    int tuberia[2];
    pid_t hijo;
    char mensaje[] = "Hola proceso hijo! Misión cumplida!";
    char buffer[100];

    pipe(tuberia);

    hijo = fork();
    if(hijo > 0){//Padre
        close(tuberia[0]);
        printf("[PADRE] escribiendo en el pipe....");
        write(tuberia[1], mensaje, sizeof(mensaje));//De esta forma escribimos en el sistema write(donde voy a escribir, que voy a escribir, el tamaño de donde voy a escribir)
        close(tuberia[1]);
        wait(NULL);
        puts("El hijo ha finalizado, termino mi ejecución \n");
    }else if (hijo == 0){//Proceso hijo(Lee la tubería, lado 0)
        close(tuberia[1]);
        read(tuberia[0], buffer, sizeof(buffer));
        printf("[HIJO] he recibido este mensaje de papá: %s\n", buffer);
        close(tuberia[0]);
        exit(1);
    }
    return 0;
}