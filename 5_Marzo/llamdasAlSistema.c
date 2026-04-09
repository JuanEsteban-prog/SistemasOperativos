#include <stdio.h>
#include <unistd.h>
#include <sys/syscall.h>

int main(){

    pid_t pid; // pid_t es del sistema operativo, es un process identifier(identicador de procesos). Recoge el ID de un proceso que se está ejecutando.
    pid = syscall (SYS_getpid);//syscall -> Le pasamos el nombre de la llamada al systema (SYS_getpid)
    printf("El ID mediante llamada al sistema es: %d\n", pid);
    printf("El ID mediante wrapper o función de C es: %d\n", gepid());
    printf("El ID mediante llamada o directísima es: %d\n", (int) syscall(39));//La línea 8 y 11 es lo mismo, la diferencia es que en uno utilizamos el nombre de la llamada y en el otro el número

    return 0;
}