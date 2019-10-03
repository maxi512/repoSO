#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char **args)
{
    while (1)
    {
        printf("\nIngrese comando a ejecutar.\n");
        printf("-> ");
        char string_usuario[100];

        fgets(string_usuario, 100, stdin);

        char *comando;
        char *parametros;

        comando = strtok(string_usuario, " \n");
        parametros = strtok(NULL, "\n");

        //*strcmp devuelve 0 si los parametros son iguales
        if (!(strcmp(comando, "listarDir")))
        {
            pid_t pid;

            pid = fork();
            if ((int)pid == 0)
            {
                execl("./listar_dir", "listar_dir", parametros, NULL);
            }
            else
            {
                wait(NULL);
            }
        }
        else if (!(strcmp(comando, "removerDir")))
        {
            pid_t pid;

            pid = fork();
            if ((int)pid == 0)
            {
                execl("./remover_dir", "remover_dir", parametros, NULL);
            }
            else
            {
                wait(NULL);
            }
        }
        else if (!(strcmp(comando, "hacerDir")))
        {
            pid_t pid;

            pid = fork();
            if ((int)pid == 0)
            {
                execl("./hacer_dir", "hacer_dir", parametros, NULL);
            }
            else
            {
                wait(NULL);
            }
        }
        else if (!(strcmp(comando, "exit")))
        {
            printf("-> Bye.\n");
            break;
        }
        else if (!(strcmp(comando, "help")))
        {
            pid_t pid;

            pid = fork();
            if ((int)pid == 0)
            {
                execl("./mostrar_ayuda", "mostrar_ayuda", NULL);
            }
            else
            {
                wait(NULL);
            }
        }
        else
        {
            printf("-> Ingrese 'help' para obtenter ayuda.\n");
        }
    }

    return 0;
}