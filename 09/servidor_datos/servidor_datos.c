#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <rpc/types.h>
#include <rpc/rpc.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>

#include "mis_tipos.h"

void err (char* msg)
{
	perror(msg);
	exit(1);
}

int main ()
{
	// XDR
	FILE *fichero;
	XDR operacion;

	Persona alumno;

	// Socket
	int sock_pasivo, sock_datos;	
	struct sockaddr_in d_local;

	// Socket setup
	d_local.sin_family = AF_INET;
	d_local.sin_addr.s_addr = htonl(INADDR_ANY);
	d_local.sin_port = htons(7890);

	bind(sock_pasivo, (struct sockaddr*) &d_local, sizeof(d_local));
	listen(sock_pasivo, SOMAXCONN);
	
	// Accept socket and link to file + check error
	if (fichero = fdopen(sock_datos = accept(sock_pasivo, 0, 0), "w")== NULL)
		err("Al hacer fdopen");
	xdrstdio_create(&operacion, fichero, XDR_ENCODE);
	
	// Datos
	alumno.nombre = "Maria";
	alumno.edad = 22;

	// Codificacion
	xdr_Persona(&operacion, &alumno); // Persona

	// Cleanup
	xdr_destroy(&operacion);
	fclose(fichero);
	close(sock_pasivo);

	return 0;
}
