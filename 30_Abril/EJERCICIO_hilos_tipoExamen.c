/*
Implementar en C (Linux, pthreads) un programa con dos hilos que cooperan mediante señales y un mutex.
Hilo Productor (productor):

Genera N números enteros aleatorios (entre 1 y 100), uno por iteración.
Antes de escribir cada número, adquiere el mutex para escribir en la variable compartida dato.
Una vez escrito el dato y liberado el mutex, notifica al consumidor enviándole SIGUSR1 con pthread_kill.
Tras enviar todos los datos, envía SIGUSR2 al consumidor para indicarle que ha terminado.

Hilo Consumidor (consumidor):

regisrtar manejadores para SIGUSR1 y SIGUSR2.
En cada iteración llama a pause() para quedarse bloqueado hasta recibir una señal.
Al recibir SIGUSR1, adquiere el mutex, lee dato, lo acumula en una suma y lo imprime.
Al recibir SIGUSR2, imprime la suma total y termina.

Requisitos concretos:

Usar pthread_mutex_lock / pthread_mutex_unlock para proteger dato.
Usar pause() en el consumidor como mecanismo de espera.
El número de iteraciones configurable mediante #define.
*/