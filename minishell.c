#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <wait.h>

#define VERSION 0.1

int main (void){

    char comando [20];
    pid_t hijo;

    printf("Bienvenidos a JL-Shell %0.2f. Introduzca un comando para ejecutar: \n", VERSION);
    scanf("%s", comando);
    while(strcmp(comando, "salir")!=0){
        hijo = fork();
        if (hijo == 0){
            char cadena[50] = "/bin/";
            strcat(cadena, comando);
            puts(cadena);
            execl(cadena, comando, NULL);
            return 0;
        }else if(hijo > 0){
            wait(NULL);
            printf("Introduzca un comando para ejecutar: \n");
            scanf("%s", comando);            
        }
    }
    return 0;
}