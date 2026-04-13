/*
Sin usar <stdio.h> ni <string.h>.
Hacer un programa que utilice la llamada al sistema write para imprimir: "Ingresa tu contraseña: "
Luego utilizar read para capturarla en un buffer de máximo 10 caractéres.
Si el usuario ingresa exactamente "unix123\n", usa write para imprimir "Acceso concedido\n". Si falla, imprimir "Denegado\n".
*/

#include <unistd.h>

int main()
{
    char msg[] = "Ingresa tu contraseña: ";
    char input[10];
    char correct[] = "unix123\n";

    write(1, msg, sizeof(msg) - 1);

    int n = read(0, input, 10);

    int ok = 1;

    // comparar "unix123\n" (8 caracteres)
    if (n != 8)
    {
        ok = 0;
    }
    else
    {
        for (int i = 0; i < 8; i++)
        {
            if (input[i] != correct[i])
            {
                ok = 0;
                break;
            }
        }
    }

    if (ok)
    {
        write(1, "Acceso concedido\n", 18);
    }
    else
    {
        write(1, "Denegado\n", 10);
    }

    return 0;
}