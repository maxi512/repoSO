#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    char string_usuario[100];

    fgets(string_usuario, 100, stdin);

    char * comando;

    comando = strtok(string_usuario, " ");

    while (p != NULL)
    {
        printf("%s\n", p);
        p = strtok(NULL, " ");
    }
    return 0;
}
