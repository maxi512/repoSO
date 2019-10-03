#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    FILE *archivo;
    char *path = *(argv + 1);
    char ch;

    archivo = fopen(path, "r");

    if (archivo == NULL)
    {
        printf("Error al abrir archivo\n");
    }
    else
    {

        while ((ch = fgetc(archivo)) != EOF)
            printf("%c", ch);

        fclose(archivo);
    }

    return 0;
}
