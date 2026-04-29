### Funciones que vamos a usar con señales:

#### Raise

- raise(): Lanza una señal a nosotros mismos.
- La función kill() lanza una señal a otro proceso.

```c
kill(pid, SIGUSR1);
```

- La función pthread_kill() lanza una señal a otro hilo dentro del mismo proceso.

```c
pthread_hill(tid, SOGUSR1);
```

- La señal pause() hace que el proceso que se lanza se quede dormido hasta que llegue una señal.
