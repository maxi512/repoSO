#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#define cant_pisos 5

pthread_mutex_t hay_gente[cant_pisos];
pthread_mutex_t se_baja[cant_pisos];
sem_t sem_protector;

int cant_personas[cant_pisos];

void personasEligenPiso(int piso)
{
    int piso_destino;
    for (int i = 0; i < cant_personas[piso]; i++)
    {
        do
        {
            piso_destino = rand() % cant_pisos;
        } while (piso_destino == piso);

        printf("Una persona se dirige al piso %d\n",piso_destino);

        pthread_mutex_unlock(&se_baja[piso_destino]);
    }
}

void subir()
{
    for (int i = 0; i < cant_pisos; i++)
    {
        printf("Ascensor esta en el piso %d.\n", i);
        sem_wait(&sem_protector);
        if (!(pthread_mutex_trylock(&hay_gente[i])))
        {

            printf("Hay gente esperando en este piso, se detiene el ascensor.\n");
            printf("Suben %d personas en este piso\n", cant_personas[i]);

            personasEligenPiso(i);

            cant_personas[i] = 0;
        }

        if (!(pthread_mutex_trylock(&se_baja[i])))
        {
            printf("Se baja gente en el piso %d\n", i);
        }
        sem_post(&sem_protector);

        printf("\n");
        sleep(2);
    }
}

void bajar()
{
    for (int i = cant_pisos - 2; i >= 1; i--)
    {
        printf("Ascensor esta en el piso %d.\n", i);
        
        sem_wait(&sem_protector);
        if (!(pthread_mutex_trylock(&hay_gente[i])))
        {

            printf("Hay gente esperando en este piso\n");
            printf("Suben %d personas en este piso\n", cant_personas[i]);

            personasEligenPiso(i);

            cant_personas[i] = 0;
        }

        if (!(pthread_mutex_trylock(&se_baja[i])))
        {
            printf("Se baja gente en el piso %d\n", i);
        }
        sem_post(&sem_protector);
        printf("\n");
        sleep(2);
    }
}

void *ascensor(void *arg)
{
    for (int i = 0; i < 3; i++)
    {
        subir();
        bajar();
    }
}

void *colocarPersonas(void *arg)
{
    while (1)
    {
        int piso = rand() % cant_pisos;
        sem_wait(&sem_protector);
        cant_personas[piso]++;

        pthread_mutex_unlock(&hay_gente[piso]);

        printf("\nHay una nueva persona esperando en el piso %d\n\n", piso);
        sem_post(&sem_protector);
        sleep(4);
        
    }
}

int main(int argc, char const *argv[])
{
    pthread_t asc, personas;

    for (int i = 0; i < cant_pisos; i++)
    {
        pthread_mutex_init(&hay_gente[i], NULL);
        pthread_mutex_lock(&hay_gente[i]);

        pthread_mutex_init(&se_baja[i], NULL);
        pthread_mutex_lock(&se_baja[i]);
    }

    sem_init(&sem_protector,0,1);

    pthread_create(&asc, NULL, &ascensor, NULL);
    pthread_create(&personas, NULL, &colocarPersonas, NULL);

    pthread_join(asc, NULL);
    pthread_join(personas, NULL);
    return 0;
}
