#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

struct parametros
{
    int numero;
    int * size;
    int **parreglo;
};

/**
 * *Recibe un numero y devuelve la conjetura de collatz asociada a ese numero en un arreglo
 * 
 */
void * collatz(void * arg)
{

    struct parametros * param = (struct parametros *)arg;

    int numero = param->numero;
    int * size = param->size;
    int ** parreglo = param->parreglo;

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
            }
            else
            {
                //* Es Impar
                numero = 3 * numero + 1; 
            }
            resultado[i++] = numero;
            (*size)++;
        }
    }

    pthread_exit((void *)resultado);

}

int main(int argc, char **args)
{
    if (argc > 2 || argc == 1)
    {
        printf("Por favor ingresar un parametro\n");
    }
    else
    {
        //*Convierte un string a entero
        int numero = atoi(*(args + 1));
        //! atoi devuelve 0 si no pudo realizar la conversion.
        if (numero <= 0)
        {
            printf("Por favor ingrese como parametro un numero entero positivo.\n");
        }
        else
        {
            pthread_t hilo_hijo;

            int size = 0;

            //Maximo 500 enteros
            int *arreglo = (int *)malloc(500 * sizeof(int));

            //creo struct para parametrizar
            struct parametros * param = malloc(sizeof(struct parametros));

            param->numero = numero;
            param->parreglo = &arreglo;
            param->size = &size;

            pthread_create(&hilo_hijo, NULL, &collatz,(void *)param);

            pthread_join(hilo_hijo,(void *)&arreglo);

            int i;

            printf("EL SIZE ES: %d\n", size);
            for (i = 0; i < size; i++)
            {

                printf("%d ", arreglo[i]);
            }
            printf("\n");
            free(arreglo);
            free(param);
        }
    }

    return 0;
}
