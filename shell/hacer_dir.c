#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main(int argc, char **argv)
{

    int status = mkdir(*(argv + 1), 0777);

    if (status == 0)
    {
        printf("Se creo carpeta %s\n", *(argv + 1));
    }

    else
    {
        printf("La carpeta %s ya existe\n", *(argv + 1));
    }
    return 0;
}
