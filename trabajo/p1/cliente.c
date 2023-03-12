// Archivos de cabecera para manipulación de sockets
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <ctype.h>
#include <pthread.h>
#include <errno.h>
#include "util.h"

#define TAMLINEA  1024
#define FALSO   0
#define CIERTO  1
#define SINASIGNAR -1

// tipo de datos que recibiran los hilos lectores
struct datos_hilo{
  FILE *fp;
  struct sockaddr *dserv;
};

typedef struct datos_hilo datos_hilo;


//
// VARIABLES GLOBALES
//

//IP del proceso syslog
char *ip_syslog;

//Puerto en el que espera el proceso syslog los
int puerto_syslog;

//Numero de hilos lectores
int nhilos;

//Es o no orientado a conexion
unsigned char es_stream=CIERTO;

// nombre del fichero fuente de eventos
char *fich_eventos;

// handler de archivo
FILE * fp;

void procesa_argumentos(int argc,char *argv[])
{
    // A RELLENAR
    |
    |
    |
    |
}

void salir_bien(int s)
{
  fclose(fp);
  exit(0);
}

void *hilo_lector(datos_hilo *p)
{
  int  enviados;
  char buffer[TAMLINEA];
  char *s;
  int sock_dat;

  do
  {
      bzero(buffer,TAMLINEA);
      // Leer la siguiente linea del fichero con fgets
      // (haciendo exclusión mutua con otros hilos)
      // El fichero (ya abierto por main) se recibe en uno de los parámetros
      // A RELLENAR -----------------
      |
      |
      |
      |
      |

      if (s!=NULL)
      {
          // La IP y puerto del servidor están en una estructura sockaddr_in
          // que se recibe en uno de los parámetros
          if (es_stream)  // Enviar la línea por un socket TCP
          {
            // A RELLENAR
            |
            |
            |
            |

          }
          else // Enviar la línea por un socket UDP
          {
            // A RELLENAR
            |
            |
            |
            |

          }
          close(sock_dat);
          printf("%s",s); // Para depuración, imprimios la línea que hemos enviado
      }
  }
  while(s); // Mientras no se llegue al final del fichero
}


void main(int argc, char * argv[])
{
    // La función main crea los hilos lector, pasándoles los parámetros necesarios,
    // y espera a que terminen

    register int i;

    pthread_t *th;
    datos_hilo q;

    int sock_dat, enviados;
    struct sockaddr_in d_serv;

    socklen_t ldir;
    char buffer[50];

    // Instalar la rutina de tratamiento de la señal SIGINT
    // A RELLENAR
    |
    |

    // Procesar los argumentos de la línea de comandos
    procesa_argumentos(argc,argv);

    printf("IP servidor %s, es_stream=%d\n",ip_syslog,es_stream);
    if ((fp=fopen(fich_eventos,"r"))==NULL)
    {
      perror("Error al abrir el fichero de eventos");
      exit(6);
    }

    // creamos espacio para los objetos de datos de hilo
    // A RELLENAR
    |
    |
    |
    |

    // incicializamos los datos que le vamos a pasar como parámetro a los hilo_lector
    // (se pasa a todos el mismo parámetro)
    // A RELLENAR
    |
    |
    |
    |

    for (i=0;i<nhilos;i++)
    {
      // lanzamos el hilo lector
      // A RELLENAR
      |
      |
      |

    }

    // Una vez lanzados todos, hacemos un join sobre cada uno de ellos
    for (i=0;i<nhilos;i++)
    {
      pthread_join(th[i],NULL);
    }
    // Al llegar aquí, todos los hilos han terminado
    fclose(fp);
}
