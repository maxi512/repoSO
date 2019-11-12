#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

sem_t semA,semB,semC,semD,semE;

void *alumnoA(void * arg){
    int tiempo= 3;
    for(int i=1; i<4; i++){
        sem_wait(&semB);
        sem_wait(&semC);
        sem_wait(&semD);
        sem_wait(&semE);
        printf("Soy el alumno A, voy a cursar el curso [%d]\n",i);
        sleep(tiempo);
        printf("Soy A, termine de cursar [%d]\n", i);
        sem_post(&semA);
        sem_post(&semA);
        sem_post(&semA);
        sem_post(&semA);
    }
}

void *alumnoB(void * arg){
    int tiempo= 5;
    for(int i=1; i<4; i++){
        sem_wait(&semA);
        sem_wait(&semC);
        sem_wait(&semD);
        sem_wait(&semE);
        printf("Soy el alumno B, voy a cursar el curso [%d]\n",i);
        sleep(tiempo);
        printf("Soy B, termine de cursar [%d]\n", i);
        sem_post(&semB);
        sem_post(&semB);
        sem_post(&semB);
        sem_post(&semB);
    }
}

void *alumnoC(void * arg){
    int tiempo= 2;
    for(int i=1; i<4; i++){
        sem_wait(&semB);
        sem_wait(&semA);
        sem_wait(&semD);
        sem_wait(&semE);
        printf("Soy el alumno C, voy a cursar el curso [%d]\n",i);
        sleep(tiempo);
        printf("Soy C, termine de cursar [%d]\n", i);
        sem_post(&semC);
        sem_post(&semC);
        sem_post(&semC);
        sem_post(&semC);
    }
}

void *alumnoD(void * arg){
    int tiempo= 3;
    for(int i=1; i<4; i++){
        sem_wait(&semB);
        sem_wait(&semC);
        sem_wait(&semA);
        sem_wait(&semE);
        printf("Soy el alumno D, voy a cursar el curso [%d]\n",i);
        sleep(tiempo);
        printf("Soy D, termine de cursar [%d]\n", i);
        sem_post(&semD);
        sem_post(&semD);
        sem_post(&semD);
        sem_post(&semD);
    }
}

void *alumnoE(void * arg){
    int tiempo= 4;
    for(int i=1; i<4; i++){
      sem_wait(&semB);
      sem_wait(&semC);
      sem_wait(&semD);
      sem_wait(&semA);
      printf("Soy el alumno E, voy a cursar el curso [%d]\n",i);
        sleep(tiempo);
        printf("Soy E, termine de cursar [%d]\n", i);
        sem_post(&semE);
        sem_post(&semE);
        sem_post(&semE);
        sem_post(&semE);
    }
}

int main(int argc, char const *argv[]) {

    pthread_t thread_al1,thread_al2,thread_al3,thread_al4,thread_al5;

    sem_init(&semA,0,4);
    sem_init(&semB,0,4);
    sem_init(&semC,0,4);
    sem_init(&semD,0,4);
    sem_init(&semE,0,4);

    pthread_create(&thread_al1, NULL, &alumnoA, NULL);
    pthread_create(&thread_al3, NULL, &alumnoB, NULL);
    pthread_create(&thread_al2, NULL, &alumnoC, NULL);
    pthread_create(&thread_al4, NULL, &alumnoD, NULL);
    pthread_create(&thread_al5, NULL, &alumnoE, NULL);


    pthread_join(thread_al1, NULL);
    pthread_join(thread_al2, NULL);
    pthread_join(thread_al3, NULL);
    pthread_join(thread_al4, NULL);
    pthread_join(thread_al5, NULL);


    return 0;
}
