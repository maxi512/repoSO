#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char **args)
{

    if (!(strcmp(*(args + 1), "hacerDir")))
    {
        printf("Se detecto comando hacerDir\n");
        mkdir(*(args + 2), 0777);

        printf("Se creo carpeta %s\n", *(args + 2));
    }
    else if (!(strcmp(*(args + 1), "removerDir")))
    {
        printf("Se detecto comando removerDir\n");
        rmdir(*(args + 2));

        printf("Se removio carpeta %s\n", *(args + 2));
    }

    return 0;
}