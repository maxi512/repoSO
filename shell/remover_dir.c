#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    if (argc == 2)
    {
        int status = rmdir(*(argv + 1));

        if (status == 0)
        {
            printf("Se removio la carpeta %s\n", *(argv + 1));
        }
        else
        {
            printf("Error, la carpeta no existe");
        }
    }
    else
    {
        printf("Ingresar como parametro la ruta.\n");
    }

    return 0;
}
