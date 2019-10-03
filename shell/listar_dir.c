#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    DIR *path_directorio;

    struct dirent *dir;

    path_directorio = opendir(*(argv + 1));

    if (path_directorio != NULL)
    {
        while ((dir = readdir(path_directorio)) != NULL)
        {
            printf("%s\n", dir->d_name);
        }
        closedir(path_directorio);
    }
    else{
        printf("ERROR al abrir directorio.\n");
    }
    return 0;
}
