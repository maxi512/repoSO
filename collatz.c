#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

/**
 * *Recibe un numero y devuelve la conjetura de collatz asociada a ese numero en un arreglo
 * */
void collatz(int numero, int *size, int **parreglo)
{
    int i = 0;

    int *resultado = (*parreglo);

    resultado[i++] = numero;
    (*size)++;

    if (numero == 1)
    {
        resultado[i++] = 4;
        resultado[i++] = 2;
        resultado[i++] = 1;
        (*size) = 4;
    }

    else
    {
        while (numero != 1)
        {
            if (numero % 2 == 0)
            {
                //*Es par
                numero /= 2;
                resultado[i++] = numero;
            }

            else
            {
                //* Es Impar
                numero = 3 * numero + 1;
                resultado[i++] = numero;
            }

            (*size)++;
        }
    }
}

int main(int argc, char **args)
{
    if (argc > 2)
    {
        printf("Por favor ingresar solo un parametro");
    }
    else
    {
        //*Convierte un string a entero
        int numero = atoi(*(args + 1));

        //atoi devuelve 0 si no pudo realizar la conversion.
        if (numero == 0 || numero < 0)
        {
            printf("Por favor ingrese como parametro un numero entero positivo.\n");
        }
        else
        {

            int size = 0;

            //Maximo 500 enteros
            int *arreglo = (int *)malloc(500 * sizeof(int));
            collatz(numero, &size, &arreglo);

            int i;
            printf("EL SIZE ES: %d\n", size);
            for (i = 0; i < size; i++)
            {

                printf("%d ", arreglo[i]);
            }
            printf("\n");
            free(arreglo);
        }
    }

    return 0;
}
