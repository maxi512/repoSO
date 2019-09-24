#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>

void listarDir(char *path)
{
    DIR *path_directorio;

    struct dirent *dir;

    path_directorio = opendir(path);

    if (path_directorio)
    {
        while ((dir = readdir(path_directorio)) != NULL)
        {
            printf("%s\n", dir->d_name);
        }
        closedir(path_directorio);
    }
   
}

void hacerDir(char *path)
{
    printf("Se detecto comando hacerDir\n");
    mkdir(path, 0777);
    printf("Se creo carpeta %s\n", path);
}

void removerDir(char *path)
{

    printf("Se detecto comando removerDir\n");
    rmdir(path);

    printf("Se removio carpeta %s\n", path);
}

int main(int argc, char **args)
{

    //*strcmp devuelve 0 si los parametros son iguales
    if (!(strcmp(*(args + 1), "hacerDir")))
    {
        hacerDir(*(args + 2));
    }
    else if (!(strcmp(*(args + 1), "removerDir")))
    {
        removerDir(*(args + 2));
    }
    else if (!(strcmp(*(args + 1), "listarDir")))
    {
        listarDir(*(args + 2));
    }

    return 0;
}