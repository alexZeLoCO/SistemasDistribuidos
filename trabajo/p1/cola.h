#include <netinet/in.h> // Necesario para sockaddr_in
#include <pthread.h>
#include <semaphore.h>

#define TAMMAXMSG 1024

typedef struct {
  unsigned char facilidad; // origen del evento
  unsigned char nivel;     // severidad del evento
  char msg[TAMMAXMSG];     // mensaje explicativo del evento
} dato_cola;


struct Cola {
    dato_cola **datos; // la cola en si es un array de punteros a dato_cola
    int head;
    int tail;
    int tam_cola;
    pthread_mutex_t mutex_head;
    pthread_mutex_t mutex_tail;
    sem_t num_huecos;
    sem_t num_ocupados;
};
typedef struct Cola Cola;

void inicializar_cola(Cola *cola, int tam_cola);
void destruir_cola(Cola *cola);
void insertar_dato_cola(Cola *cola, dato_cola * dato);
dato_cola * obtener_dato_cola(Cola *cola);
