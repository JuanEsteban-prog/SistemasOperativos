# ¿Por qué no debemos usar `printf()` dentro de un manejador de señales?

Cuando trabajamos con señales en C (`SIGINT`, `SIGUSR1`, etc.), el manejador de señales puede interrumpir la ejecución del programa en cualquier momento.  

Por eso, dentro del manejador solo se deben usar funciones seguras para señales (*async-signal-safe*).

`printf()` **NO es segura** dentro de un manejador de señales.

---

# Problema de usar `printf()`

La función `printf()` utiliza internamente:

- buffers de memoria,
- estructuras compartidas,
- bloqueos internos (*locks*),
- funciones de entrada/salida complejas.

Si el programa estaba ejecutando un `printf()` y justo en ese instante llega una señal, el manejador puede intentar ejecutar otro `printf()` antes de que el primero termine.

Esto puede provocar:

- condiciones de carrera,
- corrupción de memoria,
- mensajes mezclados,
- bloqueos del programa,
- comportamiento indefinido.

---

# Ejemplo del problema

Supongamos que el programa principal está haciendo:

```c
printf("Esperando señal...\n");
```

Y justo en medio de esa ejecución llega `SIGINT`.

Entonces el manejador hace:

```c
printf("Ctrl+C detectado\n");
```

Ahora existen **dos `printf()` ejecutándose al mismo tiempo** sobre los mismos recursos internos.

El resultado puede ser:

```text
EsperanCtrl+C detectado
do señal...
```

O incluso que el programa se bloquee.

---

# Solución correcta

Dentro del manejador debemos usar únicamente funciones seguras para señales.

La más común es:

```c
write()
```

`write()` es segura porque:

- escribe directamente al descriptor de archivo,
- no usa buffers complejos,
- no utiliza estructuras internas compartidas,
- es una llamada directa al sistema operativo.

---

# Recomendación habitual

La práctica recomendada es:

1. En el manejador:
   - solo modificar variables globales de tipo `sig_atomic_t`,
   - o usar `write()`.

2. En el programa principal:
   - revisar esas variables,
   - y usar `printf()` normalmente fuera del manejador.

---

# Ejemplo correcto

```c
#include <stdio.h>
#include <signal.h>

static volatile sig_atomic_t senal_recibida = 0;

void manejador(int sig) {
    senal_recibida = 1;
}

int main() {

    while (1) {

        if (senal_recibida) {

            printf("Se recibió una señal\n");

            senal_recibida = 0;
        }
    }

    return 0;
}
```

Aquí el manejador solo cambia una variable segura y el `printf()` se ejecuta fuera del manejador, evitando condiciones de carrera.