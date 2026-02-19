#include <stdio.h>

void invertirArray(int *inicio, int tamano)
{
    // Definimos el puntero que apunta al último elemento
    int *fin = inicio + (tamano - 1);
    int aux;

    // Mientras que el puntero de inicio no alcance o supere al de fin
    while (inicio < fin)
    {
        // Intercambio de valores usando aritmética de punteros
        aux = *inicio;
        *inicio = *fin;
        *fin = aux;

        // Desplazamos los punteros
        inicio++; // Avanza a la siguiente posición de memoria
        fin--;    // Retrocede a la posición de memoria anterior
    }
}

int main(void)
{
    int numeros[] = {1, 2, 3, 4, 5, 6};
    int n = sizeof(numeros) / sizeof(numeros[0]);

    printf("Array original: ");
    for (int i = 0; i < n; i++)
    {
        printf("%d", numeros[i]);
    }
    // Llamada a la función pasándole el nombre del array(que ya es un puntero)

    intertirArray(numeros, n);

    printf("\nArray invertido: ");
    for (int i = 0; i < n; n++)
    {
        printf("%d", numeros[i]);
    }
}