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
void ascensor();
void subir();
void bajar();
void trabajoAscensor(int piso);

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

void trabajoAscensor(int piso, int id_cola, int id_cola2)
{
    struct msg2 *m2;
    printf("Ascensor esta en el piso %d.\n", piso);
    int flag = msgrcv(id_cola2, (struct msgbuf *)&(*m2), sizeof(int),
                      piso + 1, IPC_NOWAIT);
    if(flag == 0){
        while(m2->cant_personas_bajan != 0){
            
        }
    }
    
}

void persona(int arg, int id_cola, int id_cola2)
{
    int id = arg;

    int piso_actual = rand() % cant_pisos;
    int piso_destino;

    do
    {
        piso_destino = rand() % cant_pisos;
    } while (piso_destino == piso_actual);

    while (1)
    {
        struct msg1 *m;
        struct msg2 *m2;

        printf("Soy la persona %d, estoy esperando el ascensor en el piso %d\n", id, piso_actual);
        int flag = msgrcv(id_cola, (struct msgbuf *)&(*m), sizeof(int), piso_actual + 1, IPC_NOWAIT);
        if (flag == 0)
        {
            (m->cant_personas_suben) = (m->cant_personas_suben) + 1;
        }
        else
        {
            printf("Soy la persona %d, me subi al ascensor. Voy al piso %d\n", id, piso_destino);

            m = malloc(sizeof(struct msg1));
            m->id = piso_actual + 1;
            (m->cant_personas_suben) = 1;
        }

        msgsnd(id_cola, (struct msgbuf *)&(*m),
               sizeof(int),
               IPC_NOWAIT);

        int flag = msgrcv(id_cola, (struct msgbuf *)NULL, sizeof(int), piso_actual + cant_pisos + 1, 0);
        if (flag == 0)
        {
            printf("Soy la persona %d, me subi al ascensor. Voy al piso %d\n", id, piso_destino);
        }

        int flag1 = msgrcv(id_cola, (struct msgbuf *)&(*m2), sizeof(int), piso_destino + 1, IPC_NOWAIT);
        if (flag1 == 0)
        {
            (m2->cant_personas_bajan) = (m2->cant_personas_bajan) + 1;
        }
        else
        {
            m2 = malloc(sizeof(struct msg1));
            m2->id = piso_actual + 1;
            (m2->cant_personas_bajan) = 1;
        }

        msgsnd(id_cola, (struct msgbuf *)&(*m2),
               sizeof(int),
               IPC_NOWAIT);

        int flag = msgrcv(id_cola2, (struct msgbuf *)NULL, sizeof(int), piso_destino + cant_pisos + 1, 0);
        if (flag == 0)
        {
            printf("Bajo persona %d en piso %d\n", id, piso_destino);
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
    key_t clave = ftok("/bin/ls", 1);
    key_t clave2 = ftok("/bin/ps", 2);

    int id_cola = msgget(clave, 0600 | IPC_CREAT);
    int id_cola2 = msgget(clave2, 0600 | IPC_CREAT);

    msgctl(id_cola, IPC_RMID, 0);
    msgctl(id_cola2, IPC_RMID, 0);

    id_cola = msgget(clave, 0600 | IPC_CREAT);
    id_cola2 = msgget(clave2, 0600 | IPC_CREAT);

    pid_t pid;

    if (clave == (key_t)-1)
    {
        printf("Error al obtener clave para cola mensajes");
        return (0);
    }

    if (id_cola == -1)
    {
        printf("Error al obtener identificador para cola mensajes");
        return (0);
    }

    pid = fork();

    if ((int)pid != 0)
    {
        //Proceso padre
        ascensor(id_cola, id_cola2);
    }
    else
    {
        gente(id_cola);
    }

    msgctl(id_cola, IPC_RMID, (struct msqid_ds *)NULL);

    return 0;
}
