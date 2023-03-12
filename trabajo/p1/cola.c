#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cola.h"

// El contenido de este fichero implementa las funciones de la cola.
// Es prácticamente igual a la cola que tienes hecha de las prácticas
// de laboratorio pero adaptándola a la estructura de datos dato_cola
// usada en este ejercicio.
//
// Mira el fichero cola.h para ver las estructuras de datos a utilizar

void err (char* msg)
{
    perror(msg);
    exit(1);
}

void inicializar_cola(Cola *cola, int tam_cola)
{
    // A RELLENAR
    if (tam_cola <= 0) err("ERR. Tamanno cola invalido\n");
    if ((cola->datos = (dato_cola**) malloc (tam_cola * sizeof(dato_cola*))) == NULL) err("datos\n");
    cola->head = 0;
    cola->tail = 0;
    cola->tam_cola = tam_cola;
    if (pthread_mutex_init(&(cola->mutex_head), NULL) != 0) err("mutex_head\n");
    if (pthread_mutex_init(&(cola->mutex_tail), NULL) != 0) err("mutex_tail\n");
    if (sem_init(&(cola->num_huecos), 0, tam_cola) == -1) err("num_huecos\n");
    if (sem_init(&(cola->num_ocupados), 0, 0) == -1) err("num_ocupados\n");
    return;
}


void destruir_cola(Cola *cola)
{
    // A RELLENAR
    if (cola == NULL) err("Puntero invalido\n");
    if (cola->datos != NULL) free(cola->datos); // free all other components?
    if (pthread_mutex_destroy(&(cola->mutex_head)) != 0) err("mutex_head\n");
    if (pthread_mutex_destroy(&(cola->mutex_tail)) != 0) err("mutex_tail\n");
    if (sem_destroy(&(cola->num_huecos)) == -1) err("num_huecos\n");
    if (sem_destroy(&(cola->num_ocupados)) == -1) err("num_ocupados\n");
    return;            
}

void insertar_dato_cola(Cola *cola, dato_cola * dato)
{
    // A RELLENAR
    if (cola == NULL) err("ERR. Cola invalida\n");
    if (sem_wait(&(cola->num_huecos)) == -1) err("num_huecos\n");
    if (pthread_mutex_lock(&(cola->mutex_head)) != 0) err("mutex_head\n");
    *((cola->datos)+(cola->head)) = dato;
    cola->head = (cola->head+1)%(cola->tam_cola);
    if (pthread_mutex_unlock(&(cola->mutex_head)) != 0) err("mutex_head\n");
    if (sem_post(&(cola->num_ocupados)) == -1) err("num_ocupados\n");
    return;
}


dato_cola * obtener_dato_cola(Cola *cola)
{
    dato_cola *p;
    // A RELLENAR
    if (cola == NULL) err("ERR. Cola invalida\n");
    if (sem_wait(&(cola->num_ocupados)) == -1) err("num_ocupados\n");
    if (pthread_mutex_lock(&(cola->mutex_tail)) != 0) err("mutex_tail\n");
    p = *((cola->datos)+(cola->tail));
    cola->tail = (cola->tail+1)%(cola->tam_cola);
    if(pthread_mutex_unlock(&(cola->mutex_tail)) != 0) err("mutex_tail\n");
    if (sem_post(&(cola->num_huecos)) == -1) err("num_huecos\n");
    return p;
}

