#include <sys/socket.h>
#include <stdio.h>
#include <time.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main(int argc, char* argv[]) {
	int sock_dat, nrecibidos;
	struct sockaddr_in d_serv;
	socklen_t ldir = sizeof(d_serv);
	char buffer[50];
	unsigned long int numero;

	sock_dat = socket(PF_INET, SOCK_DGRAM, 0);
	d_serv.sin_family = AF_INET;
	d_serv.sin_addr.s_addr = inet_addr("129.6.15.28");
	d_serv.sin_port = htons(37);
	{
		// Enviar datagrama vacio
		sendto(sock_dat, buffer, 0, 0, (struct sockaddr *) &d_serv, ldir);
		// Recibir datos
		nrecibidos = recvfrom(sock_dat, &numero, sizeof(numero), 0,
			(struct sockaddr *) &d_serv, &ldir);
		numero = ntohl(numero) - 2208988800;		// subtract secs from 1900-1970
		printf("Recibido: %lu\n", numero);
		/*
		double segundos_por_anno = 365.25 * 24 * 60 * 60;
		double annos = numero / segundos_por_anno;
		printf("Annos: %f\n", annos);
		*/
		printf("Fecha actual %s\n", ctime((time_t *) &numero));
	}
}

