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

    int status = mkdir(path, 0777);

    if (status = 0)
    {
        printf("Se creo carpeta %s\n", path);
    }

    else
    {
        printf("La carpeta %s ya existe\n", path);
    }
}

void removerDir(char *path)
{

    printf("Se detecto comando removerDir\n");

    int status = rmdir(path);

    if (status == 0)
    {
        printf("Se removio la carpeta %s\n", path);
    }
    else{
        printf("Error, la carpeta no existe");
    }
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