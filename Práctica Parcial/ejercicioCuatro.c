/*
NO SE PUEDE USAR ARRAYS NI <string.h>

Escribir un programa que contanga la función llamada es_palindromo. Esta función debe recibir una cadena de texto (un puntero a char)
y devolver 1 si es un palindromo(Se lee igual de izquierda a derecha que de derecha a izquierda. Ej- reconocer) y 0 si no lo es.

RESTRICCIONES:
No podemos usar la notación de índices de arrays (cadena[i]). Todo se tiene que hacer moviendo punteros hacia adelante p++ y hacia atrás p--.
*/

#include <stdio.h>

int es_palindromo(char *cadena)
{
    char *fin = cadena;

    // ir al final
    while (*fin != '\0')
    {
        fin++;
    }

    fin--; // último carácter válido

    // comparar extremos
    while (cadena < fin)
    {
        if (*cadena != *fin)
        {
            return 0; // falla
        }

        cadena++;
        fin--;
    }

    return 1; // todo correcto
}

int main()
{
    char texto[] = "reconocer";

    if (es_palindromo(texto))
    {
        printf("1\n");
    }
    else
    {
        printf("0\n");
    }

    return 0;
}