#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

#define cant_pisos 5
#define cant_personas 10

void persona(int arg, int id_cola, int id_cola2);
void ascensor(int id_cola1, int id_cola);
void subir(int id_cola1, int id_cola);
void bajar(int id_cola1, int id_cola);
void trabajoAscensor(long piso, int id_cola1, int id_cola2);

struct msg1
{
    long id;
    int cant_personas_suben;
} msg;

struct msg2
{
    long id;
    int cant_personas_bajan;
} msg2;

void ascensor(int id_cola1, int id_cola2)
{
    for (int i = 0; i < 3; i++)
    {
        subir(id_cola1, id_cola2);
        bajar(id_cola1, id_cola2);
    }
}

void subir(int id_cola1, int id_cola2)
{
    for (int piso = 0; piso < cant_pisos; piso++)
    {
        trabajoAscensor((long)piso, id_cola1, id_cola2);
    }
}

void bajar(int id_cola1, int id_cola2)
{
    for (int piso = cant_pisos - 2; piso >= 1; piso--)
    {
        trabajoAscensor((long)piso, id_cola1, id_cola2);
    }
}

void trabajoAscensor(long piso, int id_cola1, int id_cola2)
{
    struct msg1 *m1;
    printf("Ascensor esta en el piso %li.\n", piso);
    while (msgrcv(id_cola1, (struct msgbuf *)&(*m1), sizeof(struct msg1) - sizeof(long),
                  piso + 1, IPC_NOWAIT) != -1)
    {
        m1->id = piso + 1;

        msgsnd(id_cola2, (struct msgbuf *)&(*m1),
               sizeof(struct msg1) - sizeof(long),
               0);
    }

    
    sleep(2);
}

void persona(int arg, int id_cola, int id_cola2)
{
    srand(getpid());
    int id = arg;

    long piso_actual = rand() % cant_pisos;
    long piso_destino;

    do
    {
        piso_destino = rand() % cant_pisos;
    } while (piso_destino == piso_actual);

    while (1)
    {
        struct msg1 *m;
        struct msg1 *m2;

        printf("Soy la persona %d, estoy esperando el ascensor en el piso %li\n", id, piso_actual);

        m = malloc(sizeof(struct msg1));

        m->id = piso_actual + 1;

        int status = msgsnd(id_cola, (struct msgbuf *)&(*m),
                            sizeof(struct msg1) - sizeof(long),
                            0);

        int flag1 = msgrcv(id_cola2, (struct msgbuf *)NULL, sizeof(struct msg1) - sizeof(long), piso_actual + 1, 0);
        if (flag1 == 0)
        {
            printf("Soy la persona %d, me subi al ascensor. Voy al piso %li\n", id, piso_destino);
        }

        m2 = malloc(sizeof(struct msg1));

        m2->id = piso_destino;

        msgsnd(id_cola, (struct msgbuf *)&(*m2),
               sizeof(struct msg1) - sizeof(long),
               0);

        int flag3 = msgrcv(id_cola2, (struct msgbuf *)NULL, sizeof(struct msg1) - sizeof(long), piso_destino + 1, 0);
        if (flag3 == 0)
        {
            printf("Bajo persona %d en piso %li\n", id, piso_destino);
        }
        sleep(5);
        piso_actual = piso_destino;

        do
        {
            piso_destino = rand() % cant_pisos;
        } while (piso_destino == piso_actual);
    }
}

int main(int argc, char const *argv[])
{
    key_t clave1 = ftok("/bin/ls", 1);
    key_t clave2 = ftok("/bin/ps", 2);

    int id_cola1 = msgget(clave1, 0666 | IPC_CREAT);
    int id_cola2 = msgget(clave2, 0666 | IPC_CREAT);

    msgctl(id_cola1, IPC_RMID, 0);
    msgctl(id_cola2, IPC_RMID, 0);

    id_cola1 = msgget(clave1, 0666 | IPC_CREAT);
    id_cola2 = msgget(clave2, 0666 | IPC_CREAT);

    pid_t pid;

    if (clave1 == (key_t)-1)
    {
        printf("Error al obtener clave para cola mensajes");
        return (0);
    }

    if (id_cola1 == -1)
    {
        printf("Error al obtener identificador para cola mensajes");
        return (0);
    }

    if (id_cola2 == -1)
    {
        printf("Error al obtener identificador para cola mensajes");
        return (0);
    }

    for (int i = 0; i < cant_personas; i++)
    {
        pid = fork();
        if (pid == 0)
        {
            id_cola1 = msgget(clave1, 0666);
            id_cola2 = msgget(clave2, 0666);

            persona(i, id_cola1, id_cola2);
            break;
        }
    }

    if ((int)pid != 0)
    {
        //Proceso padre
        ascensor(id_cola1, id_cola2);
    }

    return 0;
}
