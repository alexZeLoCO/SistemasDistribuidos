#include <stdio.h>
#include <errno.h>
#include <rpc/types.h>
#include <rpc/rpc.h>

#include "mis_tipos.h"

void err (char* msg)
{
	perror(msg);
	exit(1);
}

int main ()
{
	// Variables
	FILE *fichero;
	XDR operacion;

	Lista lis;

	// Setup
	fichero = fopen("Lista.dat", "r");
	if (fichero == NULL)
		err("Al abrir fichero");
	xdrstdio_create(&operacion, fichero, XDR_DECODE);

	lis.siguiente = NULL;


	// Cleanup
	xdr_destroy(&operacion);
	fclose(fichero);
	return 0;
}
