#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

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

    /*
    int main(){
    
        //Con la línea 3 y 4
        int n;
        pid_t pid1; -> A partir de aquí hay dos procesos ejecutándose. Estos se diferencian en el valor de la variable pid1. pid1==0 solo la cumple el hijo, esto ocurre siempre. El pid del padre siempre es mayor que 0, es por esto que definimos el if de la siguiente forma.
        pid1=fork();
        
        if(pid1==0){->dos procesos leen está linea, el padre no la ejecuta, pero el hijo si. 
            printf("Hola, soy el proceso hijo y tengo PID %d. El PID de mi padres es %d\n", getpid(), getppid());->petppid(get parent process identifier) 
            scanf("%d", &n);
            printf("Genial, has introducido el número %d\n", n);
        }else if(pid1 > 0){-> mientras que el padre ejecuta esta línea. 
            printf("Hola, soy el proceso padre con PID %d. Mi hijo tiene PID %d\n", getpid(), (int)pid1);
        }else{
            perror("ha ocurrido un error al crear el proceso");
        }

        return 0;
    }
    */

    /*Para hacer que el padre espere:
    int main(){
    
        //Con la línea 3 y 4
        int n;
        pid_t pid1; 
        pid1=fork();
        
        if(pid1==0){
            printf("Hola, soy el proceso hijo y tengo PID %d. El PID de mi padres es %d\n", getpid(), getppid());
            scanf("%d", &n);
            printf("Genial, has introducido el número %d\n", n);
        }else if(pid1 > 0){
            printf("Hola, soy el proceso padre con PID %d. Mi hijo tiene PID %d\n", getpid(), (int)pid1);
            wait(NULL);->Hace que el padre espere al hijo.
            //Cuando hay más de un proceso se tiene que hacer lo siguiente: while(wate(NULL)>0);
            puts("Ahora sí, el hijo ha acabadoy ya puedo morir en paz");
        }else{
            perror("ha ocurrido un error al crear el proceso");
        }

        return 0;
    }
    */
}