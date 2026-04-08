#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <wait.h>
#include <stdlib.h>
#include <sys/mman.h>//Memory manager, lo necesitamos para utilizar mmap

int main(){
    pid_t hijo ;
    variable_compartida = mmap(NULL, sizeof(*variable_compartida), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    //NULL -> Queremos que ese espacio de memoria compartido este en una dirección memoria en concreto, siempre sera NULL para que el sistema operativo la ponga donde quiera. 
    // sizeof(*variable_compartida) -> Que tamaño queremos que se reserve de memoria compartida
    // PROTREAD | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS -> Máscara de bits, le damos permiso de escritura y de lectura, máscara de bits características que tiene esa región de memoria, protección de lectura y escritura. MAP_SHARED -> Hace que todo el mundo que tiene acceso a ese espacio de memoria sea capaz de escribir en el. MAP_ANONYMOUS -> Hace que la memoria compartida no dependa de un fichero. 
    //-1 -> Si no fuera un MAP_ANONYMOUS, tendría que ir la dirección del fichero, al usarlo siempre tiene que tener -1, que significa que no hay fichero.
    //0 -> Aplicamos offset(desplazar el fichero), al no tener un fichero no podemos desplazarlo, por lo tanto siempre es 0.
    //Para nosotros siempre va a ser el mismo formato para la variable_compartida!
    // A partir de aquí, todos los procesos que tienen acceso a la variable_compartida, tienen acceso a esa dirección de memoria.
    //Siempre tenemos que llamar al mmap antes que el fork!
    //Memory map asigna una región de memoria compartida
    
    hijo = fork();
    
    if(hijo == 0){//Proceso hijo
        puts("Dame un valor para la variable");
        scanf("%d", &*variable_compartida);        
        munmap(variable_compartida, sizeof(variable_compartida));
        exit(0);
    }else if(hijo > 0){//Proceso padre
        puts("Soy el padre, quedo a la espera de que el hijo haga su trabajo");
        wait(NULL);
        printf("Soy el padre, y el hijo ha cambiado el valor de la variable a %d\n", variable_compartida);
        munmap(variable_compartida, sizeof(variable_compartida));
    }
    
    return 0;
}