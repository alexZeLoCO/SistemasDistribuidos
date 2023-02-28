// Fichero: echo-tcp-udp-select.c
#include <stdio.h>       // printf()
#include <stdlib.h>      // exit()
#include <sys/socket.h>  // socket(), bind(), listen(), recv(), send(), etc
#include <arpa/inet.h>   // sockaddr_in
#include <errno.h>       // perror()
#include <sys/select.h>  // select() y fd_set
#include <unistd.h>      // close()

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

int buscar_maximo(int tcp, int udp, int datos)
{
    // La funcion debería devolver el maximo de estos tres, pero si datos==0
    // entonces datos no se tiene en cuenta, pero si datos!=0 es tcp el que
    // no se tiene en cuenta ya que no se vigila para admitir mas clientes

    int resultado;

    if (datos==0)
        resultado = max(tcp, udp);
    else
        resultado = max(datos, udp);
    return resultado;
}

int main(int argc, char * argv[])
{
    int puerto;
    int s_tcp, s_udp; // sockets "de escucha"
    int s_datos;      // Para la conexion TCP
    fd_set conjunto;  // Para select
                      // Array de 64 bits
                      // El bit n indica si el fd n es vigilado por el select
    int    maximo;    // Para select

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
    s_udp = CrearSocketUDP(puerto);
    s_datos = 0;  // De momento no tenemos cliente

    while (1) {  // Bucle infinito del servidor

        // Vaciar conjunto de descriptores a vigilar
        FD_ZERO(&conjunto);

        // Meter solo los que haya que vigilar
        // El UDP siempre:
        FD_SET(s_udp, &conjunto);
        // Si hay cliente meto el de datos, si no meto el de escucha
        if (s_datos!=0)
            FD_SET(s_datos, &conjunto);
        else
            FD_SET(s_tcp, &conjunto);

        maximo = buscar_maximo(s_tcp, s_udp, s_datos);

        // Esperar a que ocurra "algo"
        select(maximo + 1, &conjunto, NULL, NULL, NULL);
        printf("Ha ocurrido algo\n");


        // Averiguar que ocurrió
        if (FD_ISSET(s_udp, &conjunto))
        {
            printf("Ha ocurrido algo en el socket UDP\n");
            dar_servicio_UDP(s_udp);
        }
        if (FD_ISSET(s_tcp, &conjunto))
        {
            printf("Ha llegado un cliente al socket TCP\n");
            s_datos = accept(s_tcp, NULL, NULL);
        }
        if (FD_ISSET(s_datos, &conjunto))
        {
            printf("Han llegado datos por la conexión TCP\n");
            if (dar_servicio_TCP(s_datos)==0) {
                printf("El cliente TCP ha desconectado\n");
                s_datos = 0; // Reiniciamos s_datos => s_udp volvera al conjunto
            }
        }
    } // del while(1)
    return 0;   // Nunca se ejecuta, pero para que el compilador no proteste
} // de main()
