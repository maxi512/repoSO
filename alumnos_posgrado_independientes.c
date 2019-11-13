#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


void *alumnoA(void * arg){
    int tiempo= 3;
    for(int i=1; i<=10; i++){
        printf("Soy el alumno A, voy a cursar el curso [%d]\n",i);
        sleep(tiempo);
        printf("Soy A, termine de cursar [%d]\n", i);
    }
}

void *alumnoB(void * arg){
    int tiempo= 5;
    for(int i=1; i<=10; i++){
        printf("Soy el alumno B, voy a cursar el curso [%d]\n",i);
        sleep(tiempo);
        printf("Soy B, termine de cursar [%d]\n", i);
    }
}

void *alumnoC(void * arg){
    int tiempo= 2;
    for(int i=1; i<=10; i++){
        printf("Soy el alumno C, voy a cursar el curso [%d]\n",i);
        sleep(tiempo);
        printf("Soy C, termine de cursar [%d]\n", i);
    }
}

void *alumnoD(void * arg){
    int tiempo= 3;
    for(int i=1; i<=10; i++){
        printf("Soy el alumno D, voy a cursar el curso [%d]\n",i);
        sleep(tiempo);
        printf("Soy D, termine de cursar [%d]\n", i);
    }
}

void *alumnoE(void * arg){
    int tiempo= 4;
    for(int i=1; i<=10; i++){
      printf("Soy el alumno E, voy a cursar el curso [%d]\n",i);
        sleep(tiempo);
        printf("Soy E, termine de cursar [%d]\n", i);
    }
}

int main(int argc, char const *argv[]) {
    //Se crean los threads para cada alumno
    pthread_t thread_al1,thread_al2,thread_al3,thread_al4,thread_al5;

    //Se inician los threads de cada alumno, asociandole la funcion correspondiente
    pthread_create(&thread_al1, NULL, &alumnoA, NULL);
    pthread_create(&thread_al3, NULL, &alumnoB, NULL);
    pthread_create(&thread_al2, NULL, &alumnoC, NULL);
    pthread_create(&thread_al4, NULL, &alumnoD, NULL);
    pthread_create(&thread_al5, NULL, &alumnoE, NULL);

    //Se espera a que los hilos terminen.
    pthread_join(thread_al1, NULL);
    pthread_join(thread_al2, NULL);
    pthread_join(thread_al3, NULL);
    pthread_join(thread_al4, NULL);
    pthread_join(thread_al5, NULL);


    return 0;
}
