#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int max_size = 2048;

void collatz(int numero, char **arreglo)
{

    int i = 0;

    char *resultado = (*arreglo);

    sprintf(resultado, "%d ", numero);

    do
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

        //*Lo paso a char y lo concateno
        char str[11];
        sprintf(str, "%d ", numero);
        strcat(resultado, str);

    } while (numero != 1);
}

int main(int argc, char **args)
{

    int pipe_salida[2];

    pid_t pid;

    int numero_entrada;

    if (argc > 2 || argc == 1)
    {
        printf("Por favor ingresar un parametro\n");
    }

    else
    {
        //*Convierte un string a entero
        numero_entrada = atoi(*(args + 1));

        //! atoi devuelve 0 si no pudo realizar la conversion.
        if (numero_entrada <= 0)
        {
            printf("Por favor ingrese como parametro un numero entero positivo.\n");
        }
        else
        {
            pipe(pipe_salida);

            pid = fork();

            if ((int)pid != 0)
            {
                //Estoy en el proceso padre

                wait(NULL);
                char imprimir[max_size];

                close(pipe_salida[1]);

                //*ACA SE RECIBE RESULTADO DESDE PROCESO HIJO
                read(pipe_salida[0], imprimir, max_size);

                printf("%s\n", imprimir);
                close(pipe_salida[0]);
            }
            else
            {
                //proceso hijo
                char *resultado = malloc(max_size * sizeof(char));
                char numero[max_size];

                collatz(numero_entrada, &resultado);

                close(pipe_salida[0]);

                //*PASO RESULTADO AL PADRE
                write(pipe_salida[1], resultado, max_size);
                close(pipe_salida[1]);

                free(resultado);
            }
        }
    }

    return 0;
}
