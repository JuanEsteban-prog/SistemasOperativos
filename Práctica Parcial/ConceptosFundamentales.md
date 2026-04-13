### Llamadas al sistema vs Librería Estándar

- La librería estándar `<stdio.h>` nos permite utilizar printf, scanf, etc.
- Llamada al sistema: Para escribir o leer directamente del sistema, usamos write(1, buffer, tamaño) (donde 1 es pantalla/stdout) y read (0, buffer, tamaño)(donde 0 es el teclado/stdin)

### fork()

- La llamada fork() duplica el proceso exactamente en el punto en el que se invoca. Tenemos una copia exacta en memoria pero con una pequeña diferencia.
  - **En el proceso padre:** fork() devuelve el PID(PROCESS IDENTIFIER un número mayor que 0) del hijo que acaba de nacer.
  - **En el proceso hijo:** fork() devuelve 0.
  - **Sincronización:** El padre siempre debe esperar a que sus hijos terminen usando wait(&estado).

### Comunicación IPC mediante tuberías(pipe)

Un padre y un hijo viven en memorias separadas; no pueden compartir variables normales. Para hablar entre ellos se una `pipe()` que transforma un array de dos enteros en una tubería del Sistema Operativo.

- **Regla de oro:** tuberia[1] sirve para escribir, y tubería[0] sirve para leer.
- **Buenas prácticas:** Siempre debemos usar close() en el extremo que no vamos a usar en el proceso (si el hijo lee, cerramos la escritura y viceversa).

### Memoria compartida `mmap`

Cuando las tuberías se quedan cortas, usamos `mmap()` con las banderas MAP_SHARED | MAP_ANONYMOUS y -1 como file descriptor para pedirle al Sistema Operativo un bloque de Memoria RAM que tanto el padre como el hijo pueden leer y editar a la vez. Pero esto tiene un problema:

- **Condiciones de carrera:** También se conocen como Race Conditions, si el padre e hijo intentan modificar la misma variable al mismo tiempo sin sincronizarse, el resultado es impredecible. Al terminar es buena práctica limpiar la tubería con `munmap()`

### Reemplazo de imagen `exec`

Cuando no queremos que el hijo ejecute nuestro código, sino un programa totalmente distinto, invocamos a la familia de funciones exec(). Al hacerlo, el código del hijo se borra por completo y es sustituido por el nuevo programa.
