#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <arpa/inet.h>

/*
 * Es necesario hacer comprobacion de errores para las lineas marcadas
 */
int main(int argc, char* argv[])
{
	int sock_dat, recibidos;
	struct sockaddr_in d_local, d_cliente;
	socklen_t ldir = sizeof(d_cliente);
	char buffer[50];
	sock_dat = socket(PF_INET, SOCK_DGRAM, 0); // Puede fallar
	d_local.sin_family = AF_INET;
	d_local.sin_addr.s_addr = htonl(INADDR_ANY);
	d_local.sin_port = htons(7890);
	bind(sock_dat, (struct sockaddr *)&d_local, sizeof(d_local)); // Puede fallar
	while (1) // Bucle infinito de atención a clientes
	{ 
		recibidos = recvfrom(sock_dat, buffer, 50, 0,
				(struct sockaddr *) &d_cliente, &ldir); // Puede fallar
		printf("Cliente desde %s (%d)\n",
				inet_ntoa(d_cliente.sin_addr), ntohs(d_cliente.sin_port));
		sendto(sock_dat, buffer, recibidos, 0,
				(struct sockaddr *) &d_cliente, ldir); // Puede fallar
	}
}
