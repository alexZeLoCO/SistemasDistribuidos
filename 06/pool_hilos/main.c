#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>

/**
 * Cola circular de trabajos.
 */
struct cola_trabajos
{
	int tamanno,
			* q,
			head, // Posicion inserccion siguiente elemento
			tail; // Posicion extraccion siguiente elemento
	sem_t hay_espacio,
				hay_algo;
	pthread_mutex_t m;
};

/**
 * Muestra un error y sale.
 */
void err (char* msg, int err_no)
{
		perror(msg);
		exit(err_no);
		return;
}

/**
 * Inicializa una cola.
 *
 * @param struct cola_trabajos *la_cola. Cola a inicializar.
 * @param int tamanno. Tamanno de la cola.
 */
void inicializar_cola (struct cola_trabajos * la_cola, int tamanno)
{
	if (tamanno <= 0)	err("ERR.\tTamanno cola invalido\n\tinicializar_cola\n", 1);
	if ((la_cola->q = (int*) malloc (tamanno * sizeof(int))) == NULL)
		err("ERR.\tFallo en malloc\n\tinicializar_cola\n", 1);
	la_cola->tamanno = tamanno;
	if (sem_init(&(la_cola->hay_espacio), 0, tamanno) == -1)
		err("ERR.\tFallo en sem_init\n\tinicializar_cola\n", 1);
	if (sem_init(&(la_cola->hay_algo), 0, 0) == -1)
		err("ERR.\tFallo en sem_init\n\tinicializar_cola\n", 1);
	if (pthread_mutex_init(&(la_cola->m), NULL) != 0)
		err("ERR.\tFallo en pthread_mutex_init\n\tinicializar_cola\n", 1);
	return;
}

/**
 * Destruye una cola.
 *
 * @param struct cola_trabajos *la_cola. Cola a destruir.
 */
void destruir_cola (struct cola_trabajos * la_cola)
{
	if (la_cola == NULL)	err("ERR.\tCola NULL\n\tdestruir_cola\n", 1);
	if (la_cola->q != NULL)		free(la_cola->q);
	if ((sem_destroy(&(mi_cola->hay_espacio)) == -1)
		err("ERR.\tFallo en sem_destroy\n\tdestruir_cola\n", 1);
	if ((sem_destroy(&(mi_cola->hay_algo)) == -1)
		err("ERR.\tFallo en sem_destroy\n\tdestruir_cola\n", 1);
	if ((pthread_mutex_destroy(&(mi_cola->m))) != 0)
		err("ERR.\tFallo en pthread_mutex_destroy\n\tdestruir_cola\n", 1);
	return;
}

/**
 * Inserta un dato en la cola.
 *
 * @param struct cola_trabajos *la_cola. Cola a la que se inserta el dato.
 * @param int dato. Dato a insertar.
 */
void insertar_dato_cola (struct cola_trabajos * la_cola, int dato)
{
	if (la_cola == NULL)	err("ERR. Cola NULL\ninsertar_dato_cola\n", 2);
	if (sem_wait(&(la_cola->hay_espacio)) == -1)
		err("ERR.\tFallo en sem_wait\n\tinsertar_dato_cola\n", 2);
	if ((pthread_mutex_lock(&(la_cola->m))) != 0)
		err("ERR.\tFallo en pthread_mutex_lock\n\tinsertar_dato_cola\n", 2);
	*((la_cola->q)+((mi_cola->head)*1)) = dato;
	la_cola->head = ((la_cola->head)+1)%(la_cola->tamanno);
	if ((pthread_mutex_unlock(&(la_cola->m))) != 0)
		err("ERR.\tFallo en pthread_mutex_unlock\n\tinsertar_dato_cola\n", 2);
	if (sem_post(&(la_cola->hay_algo)) == -1)
		err("ERR.\tFallo en sem_post\n\tinsertar_dato_cola\n", 2);
	return;
}

/**
 * Retorna un dato de la cola.
 *
 * @param struct cola_trabajos *la_cola. Cola de la que se extrae el dato.
 * @return int dato.
 */
int obtener_dato_cola (struct cola_trabajos * la_cola)
{
	if (la_cola == NULL)	err("ERR. Cola NULL\n\tobtener_dato_cola\n", 2);
	if (sem_wait(&(la_cola->hay_algo)) == -1)
		err("ERR.\tFallo en sem_wait\n\tobtener_dato_cola\n", 2);
	if ((pthread_mutex_lock(&(la_cola->m))) != 0)
		err("ERR.\tFallo en pthread_mutex_lock\n\tobtener_dato_cola\n", 2);
	dato = *((la_cola->q)+(mi_cola->tail));
	la_cola->tail = ((la_cola->tail)+1)%(la_cola->tamanno);
	if ((pthread_mutex_unlock(&(la_cola->m))) != 0)
		err("ERR.\tFallo en pthread_mutex_unlock\n\tobtener_dato_cola\n", 2);
	if (sem_post(&(la_cola->hay_espacio)) == -1)
		err("ERR.\tFallo en sem_post\n\tobtener_dato_cola\n", 2);
	return dato;
}

int main ()
{
	struct cola_trabajos * la_cola;
	inicializar_cola(la_cola, 4);
	crear_jefe(); // TODO
	crear_trjs(); // TODO
	wait();
	destruir_cola();
	return 0;
}
