/*Define un array de 10 números enteros y un "número objetivo" a buscar.
El proceso principal (Padre) debe crear dos procesos hijos utilizando la llamada al sistema fork().

El Hijo 1 deberá buscar el número objetivo en la primera mitad del array. 

Si lo encuentra, terminará su ejecución devolviendo un estado de éxito(exit(1)).

Si no lo encuentra, terminará devolviendo un estado de fracaso (exit(0)).

El Hijo 2 deberá de hacer lo mismo, pero buscando en la segunda mitad del array.

El proceso Padre sebe usar la llamada al sistema wait() para esperar obligatoriamente a que ambos hijos terminen.

El Padre debe inspeccionar el estado de salida de cada hijo utilizando las macros adecuadas (WIFEXITED y WEXISTATUS)
*/