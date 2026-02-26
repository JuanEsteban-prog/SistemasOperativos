#include<stdio.h>

int main(void){
	int numero, inverso = 0, digito;

    printf("Ingrese un numero: ");
    scanf("%d", &numero);

    while (numero != 0) {
        digito = numero % 10;          // Obtener el último dígito
        inverso = inverso * 10 + digito; // Construir el número invertido
        numero = numero / 10;          // Eliminar el último dígito
    }

    printf("El numero invertido es: %d\n", inverso);

    return 0;
}
