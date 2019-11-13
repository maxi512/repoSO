#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

#define cant_pisos 5
#define cant_personas 10

void *persona(void *arg);
void *ascensor(void *arg);
void subir();
void bajar();
void trabajoAscensor(int piso);

sem_t cant_gente_esperando[cant_pisos];
sem_t esperando_ascensor[cant_pisos];
sem_t esperando_bajar[cant_pisos];
sem_t cant_gente_bajar[cant_pisos];

/*
Este metodo, representa el comportamiento de una persona. Inicialmente se ubica en un piso aleatorio, y se elige un piso destino
distinto del que se encuentra.
Cuando el ascensor llega al piso de la persona, esta se sube y avisa a que piso desea ir. Cuando se llega al piso destino,
la persona se baja y espera un rato para volver nuevamente a pedir el ascensor.
*/
void *persona(void *arg)
{
    int *id= (int*) arg;
    int id_persona = *id;
    int piso_actual = rand() % cant_pisos;
    int piso_destino;

    do
    {
        piso_destino = rand() % cant_pisos;
    } while (piso_destino == piso_actual);

    while(1)
    {
        printf("Soy la persona %d, estoy esperando el ascensor en el piso %d\n",id_persona,piso_actual);

        sem_post(&cant_gente_esperando[piso_actual]);
        sem_wait(&esperando_ascensor[piso_actual]);

        printf("Soy la persona %d, me subi al ascensor. Voy al piso %d\n",id_persona,piso_destino);

        sem_post(&cant_gente_bajar[piso_destino]);
        sem_wait(&esperando_bajar[piso_destino]);

        printf("Bajo persona %d en piso %d\n",id_persona,piso_destino);

        sleep(5);

        piso_actual = piso_destino;

        do
        {
            piso_destino = rand() % cant_pisos;
        } while (piso_destino == piso_actual);
    }
}

/*
Este metodo simula el movimiento del ascenso, haciendo que baje y suba durante 3 ciclos.
*/
void *ascensor(void *arg)
{
    for (int i = 0; i < 3; i++)
    {
        subir();
        bajar();
    }
}

void subir()
{
    for(int piso=0; piso<cant_pisos; piso++){
        trabajoAscensor(piso);
    }
}

void bajar()
{
    for(int piso=cant_pisos -2; piso>=1; piso--){
        trabajoAscensor(piso);
    }
}

/*
Este metodo es el encargado de simular el trabajo del ascensor en cada piso.
Cuando se llega a un piso, se muestra un mensaje indicando en que piso se encuentra, y luego se bajan, si es que hay,
las personas correspondientes, y se suben las que estaban esperando.
*/
void trabajoAscensor(int piso)
{
    printf("Ascensor esta en el piso %d.\n", piso);

    //La gente se baja del ascensor.
    while(! sem_trywait(&cant_gente_bajar[piso]) )
    {
        sem_post(&esperando_bajar[piso]);
    }

    //La gente se sube al ascensor.
    while(! sem_trywait(&cant_gente_esperando[piso]) )
    {
        sem_post(&esperando_ascensor[piso]);
    }
    sleep(2);
}


int main(int argc, char const *argv[])
{
    pthread_t personas[cant_personas];
    pthread_t t_ascensor;

    //Se inicializan los semaforos
    for(int i=0; i<cant_pisos; i++) {
        sem_init(&cant_gente_esperando[i],0,0);
        sem_init(&cant_gente_bajar[i],0,0);
        sem_init(&esperando_bajar[i],0,0);
        sem_init(&esperando_ascensor[i],0,0);
    }

    pthread_create(&t_ascensor,NULL,&ascensor,NULL);

    //Se inician los threads del arreglo asociandole el comportamiento de una persona a cada uno.
    for(int i=0; i<cant_personas; i++)
    {
        int *p = (int*)malloc(sizeof(int));
        *p = i;
        pthread_create(&personas[i],NULL,&persona,(void*)p);
    }

    //Se espera que todas las personas finalicen.
    for(int j=0; j<cant_personas; j++)
    {
        pthread_join(personas[j],NULL);
    }

    //Se espera a que el hilo ascensor finalice.
    pthread_join(t_ascensor, NULL);

    return 0;
}
