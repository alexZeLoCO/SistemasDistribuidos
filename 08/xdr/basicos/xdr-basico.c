#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <rpc/rpc.h>
#include <rpc/types.h>

void err (char* msg)
{
	perror(msg);
	exit(1);
}

int main ()
{
	int var_int,
			aux;
	char var_char;
	FILE *fichero;
	XDR operacion;

	fichero = fopen("basicos.dat", "w");
	if (fichero == NULL)
		err("Al abrir el fichero");

	xdrstdio_create(&operacion, fichero, XDR_ENCODE);

	printf("Introducir int: ");
	scanf("%d", &var_int);
	aux = getchar(); // Consume el retorno de carro
	printf("Introducir char: ");
	var_char = (char) fgetc(stdin);

	xdr_int(&operacion, &var_int); // Codifica el char
	xdr_char(&operacion, &var_char); // Codifica el char
	xdr_destroy(&operacion);
	fclose(fichero);

	return 0;
}
