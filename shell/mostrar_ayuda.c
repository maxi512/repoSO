#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    FILE *archivo;
    char ch;

    archivo = fopen("./shell_ayuda", "r");
    if (archivo == NULL)
    {
        printf("Error al abrir archivo de ayuda\n");
    }
    else
    {

        while ((ch = fgetc(archivo)) != EOF)
            printf("%c", ch);

        fclose(archivo);
    }

    return 0;
}