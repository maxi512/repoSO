#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int * collatz(int numero, int * size){
    int i  = 0;
     
    //MAXIMO 50 enteros
    int * resultado  = malloc(50 * sizeof(int));

    if(numero == 1){
       
        *(resultado + 0) = 1;
        *(resultado + 1 )= 4;
        *(resultado + 2) = 2;
        *(resultado + 3) = 1;
        (*size) = 4;  


    }
    return resultado;

}

int main(){
    int size;
    int * arreglo = collatz(1, &size);

    int i;
    printf("EL SIZE ES: %d\n",size);
    for(i = 0; i<size; i++){     

        printf("%d\n",*arreglo);
        
        arreglo++;
        
    }

    //PREGUNTAR
    free(arreglo);

    return 0;
}