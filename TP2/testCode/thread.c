#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <pthread.h>

void *myThreadRun(){
    sleep(1);
    printf("Imprimiendo desde hilo\n");
}

void main(){
    pthread_t hilo01;
    printf( "Antes del hilo\n" );
    pthread_create( &hilo01, NULL, myThreadRun, NULL );
    printf( "Despues del hilo\n" );
    pthread_join( hilo01, NULL );
}