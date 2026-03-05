// PROHIBIDO USAR stdio.h
// El programa tiene que mostrar un mensaje que nos diga introduce tu nombre. El tope es 50 caracteres para el buffer de memoria.
// Después va a mostrar otro mensaje, introduce tu edad.
// Leemos la edad del usuario, máximo 3 caracteres. 
// Cuando tengamos almacenado esto, sacamos un mensaje que diga Hola + nombreUsuario + tienes + edad.


// Librería que contiene read() y write()
#include <unistd.h>

int main() {

    // Buffer para almacenar el nombre (máximo 50 caracteres)
    char nombre[50];

    // Buffer para almacenar la edad (máximo 3 caracteres)
    char edad[3];

    // Mensaje para pedir el nombre
    char msgNombre[] = "Introduce tu nombre:\n";

    // Mensaje para pedir la edad
    char msgEdad[] = "Introduce tu edad:\n";

    // Mensaje inicial del saludo
    char msgHola[] = "Hola ";

    // Mensaje intermedio
    char msgTienes[] = " tienes ";

    // Salto de línea final
    char saltoLinea[] = "\n";

    // -----------------------------
    // Mostramos el mensaje para pedir el nombre
    // sizeof(msgNombre) cuenta todos los bytes del array
    // -1 elimina el carácter nulo '\0'
    // -----------------------------
    write(1, msgNombre, sizeof(msgNombre) - 1);

    // -----------------------------
    // Leemos el nombre desde el teclado
    // 0 = entrada estándar
    // nombre = buffer donde guardamos lo leído
    // 50 = máximo de caracteres
    // -----------------------------
    read(0, nombre, 50);

    // -----------------------------
    // Mostramos el mensaje para pedir la edad
    // -----------------------------
    write(1, msgEdad, sizeof(msgEdad) - 1);

    // -----------------------------
    // Leemos la edad (máximo 3 caracteres)
    // -----------------------------
    read(0, edad, 3);

    // -----------------------------
    // Mostramos "Hola "
    // -----------------------------
    write(1, msgHola, sizeof(msgHola) - 1);

    // -----------------------------
    // Mostramos el nombre del usuario
    // Aquí indicamos 50 porque es el tamaño máximo del buffer
    // -----------------------------
    write(1, nombre, 50);

    // -----------------------------
    // Mostramos " tienes "
    // -----------------------------
    write(1, msgTienes, sizeof(msgTienes) - 1);

    // -----------------------------
    // Mostramos la edad
    // -----------------------------
    write(1, edad, 3);

    // -----------------------------
    // Mostramos salto de línea final
    // -----------------------------
    write(1, saltoLinea, sizeof(saltoLinea) - 1);

    return 0;
}

