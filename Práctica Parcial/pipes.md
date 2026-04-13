## Concepto

Un `pipe` permite la comunicación entre procesos (normalmente padre ↔ hijo).
Cada pipe tiene dos extremos:

- pipe[0] -> Lectura
- pipe[1] -> Escritura

### Para crear el pipe()

```bash
int pipe[2];

if(pipe(pipe) == -1){
    perror("Error al crear el pipe!");
    exit(EXIT_FAILURE);
}
```

### Para crear el proceso hijo y el proceso padre

Ejemplo: enviar un entero int dato = 10;

```bash
pid_t pid = fork();

if(pid < 0){
    perror("Error al crear el fork!");
    exit(EXIT_FAILURE);
}else if(pid == 0){ **PROCESO HIJO**
    close(pipe[1]);
    int recibido;
    read(fd[0], &recibido, sizeof(recibido));
    printf("Dato recibido: %d\n", recibido);
    close(fd[0]); // Cerrar lectura
}else if(pid > 0){ **PROCESO PADRE**
    close(pipe[0]); // NO LEE
    write(pipe[1], &dato, sizeof(dato));
    close(pipe[1]); // cerrar escritura
    wait(NULL); // esperar al hijo
}
```

### RESUMEN GENERAL

#### Para escribir en el pipe

```bash
write (fd[1], datos, tamaño);
```

#### Leer del pipe

```bash
read(fd[0], buffer, tamaño);
```

### Reglas Importantes!

- El pipe es unidireccional.
- Lo que enviamos = Lo que debemos leer(mismo tamaño).
- Cerrar extremos que no se usan(close)
- Crear el pipe() ANTES del fork().
