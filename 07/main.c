// Fichero: echo-tcp-udp-select.c
#include <stdio.h>       // printf()
#include <stdlib.h>      // exit()
#include <sys/socket.h>  // socket(), bind(), listen(), recv(), send(), etc
#include <arpa/inet.h>   // sockaddr_in
#include <errno.h>       // perror()
#include <sys/select.h>  // select() y fd_set
#include <unistd.h>      // close()

#define MAXCLIENTES 5 // Maximo de clientes conectados admitidos

int CrearSocketTCP(int puerto)
{
    int s;
    struct sockaddr_in dir;
    int r;

    s = socket(PF_INET, SOCK_STREAM, 0);
    if (s==-1) {
        perror("En socket TCP");
        exit(1);
    }
    dir.sin_family = AF_INET;
    dir.sin_port   = htons(puerto);
    dir.sin_addr.s_addr = htonl(INADDR_ANY);
    r = bind(s, (struct sockaddr *) &dir, sizeof(dir));
    if (r==-1) {
        perror("En bind TCP");
        exit(1);
    }
    r = listen(s, SOMAXCONN);
    if (r==-1) {
        perror("En listen");
        exit(1);
    }
    return s;
}

int CrearSocketUDP(int puerto)
{
    int s;
    struct sockaddr_in dir;
    int r;

    s = socket(PF_INET, SOCK_DGRAM, 0);
    if (s==-1) {
        perror("En socket UDP");
        exit(1);
    }
    dir.sin_family = AF_INET;
    dir.sin_port   = htons(puerto);
    dir.sin_addr.s_addr = htonl(INADDR_ANY);
    r = bind(s, (struct sockaddr *) &dir, sizeof(dir));
    if (r==-1) {
        perror("En bind UDP");
        exit(1);
    }
    return s;
}

void dar_servicio_UDP(int s)
{
    // Lee un datagrama del socket s y lo reenvía a su origen
    struct sockaddr_in origen;
    socklen_t tamanio = sizeof(origen);
    char buffer[100];
    int leidos;

    leidos = recvfrom(s, buffer, 100, 0, (struct sockaddr *) &origen, &tamanio);
    sendto(s, buffer, leidos, 0, (struct sockaddr *) &origen, tamanio);
}


int dar_servicio_TCP(int s)
{
    // Lee datos del socket s y si lee distinto de cero, envia eco
    // Retorna el numero de datos leidos

   char buffer[100];
   int leidos;

   leidos = recv(s, buffer, 100, 0);
   if (leidos>0)
       send(s, buffer, leidos, 0);
   return leidos;
}

int max(int a, int b)
{
    // Devuelve el mayor entre a y b
    if (a>b) return a;
    else return b;
}

int buscar_maximo(int tcp, int *cli, int tam)
{
    // La funcion retorna el maximo entre el socket tcp y las
    // posiciones distintas de 0 del array cli.
    int resultado = tcp,
        i;
    for (i = 0 ; i < tam ; i++)
        if (*(cli+i) > resultado)   resultado = *(cli+i);
    return resultado;
}

void inicializa_clientes (int *cli, int tam)
{
    int i;
    for (i = 0 ; i < tam ; i++)
        *(cli+i) = 0;
    return;
}

int* buscar_posicion_libre(int* cli, int tam)
{
    int i;
    for (i = 0 ; i < tam ; i++)
        if (*(cli+i) == 0)
            return cli+i;
}

int main(int argc, char * argv[])
{
    int puerto;
    int s_tcp;        // sockets "de escucha"
    int s_datos [MAXCLIENTES];      // Para la conexion TCP
    fd_set conjunto;  // Para select
                      // Array de 64 bits
                      // El bit n indica si el fd n es vigilado por el select
    int    maximo;    // Para select
    int    num_clientes = 0; // Numero de clientes TCP activos
    int i, pos;

    if (argc<2) {
        printf("Uso: %s puerto\n", argv[0]);
        exit(0);
    }

    puerto = atoi(argv[1]);
    if (puerto < 1024 || puerto > 65535)
    {
        printf("Puerto invalido\n");
        exit(0);
    }
    s_tcp = CrearSocketTCP(puerto);
    inicializa_clientes(s_datos, MAXCLIENTES);

    while (1) {  // Bucle infinito del servidor

        // Vaciar conjunto de descriptores a vigilar
        FD_ZERO(&conjunto);

        // Si el numero de clientes activos es menor que MAXCLIENTES
        // entonces vigilo el socket pasivo
        if (num_clientes < MAXCLIENTES) FD_SET(s_tcp, &conjunto);

        for (i = 0 ; i < MAXCLIENTES ; i++)
            if (*(s_datos+i) != 0)  FD_SET(*(s_datos+i), &conjunto);
 
        maximo = buscar_maximo(s_tcp, s_datos, MAXCLIENTES);

        // Esperar a que ocurra "algo"
        select(maximo + 1, &conjunto, NULL, NULL, NULL);
        printf("Ha ocurrido algo\n");

        // Averiguar que ocurrió
        if ((num_clientes < MAXCLIENTES) && (FD_ISSET(s_tcp, &conjunto)))
        {
            printf("Ha llegado un cliente al socket TCP\n");
            *buscar_posicion_libre(s_datos, MAXCLIENTES) 
                = accept(s_tcp, NULL, NULL);
            num_clientes++;
        }
        for (i = 0 ; i < MAXCLIENTES ; i++)
            if ((*(s_datos+i) != 0) && (FD_ISSET(*(s_datos+i), &conjunto)))
            {
                printf("Han llegado datos por la conexión TCP\n");
                if (dar_servicio_TCP(*(s_datos+i))==0) {
                    printf("El cliente TCP ha desconectado\n");
                    close(*(s_datos+i));
                    *(s_datos+i) = 0;
                    num_clientes--;
                }
            }
    } // del while(1)
    return 0;   // Nunca se ejecuta, pero para que el compilador no proteste
} // de main()
