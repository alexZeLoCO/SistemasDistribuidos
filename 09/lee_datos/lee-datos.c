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

	Texto cadena;
	Persona alumno;
	Resultado res;

	// Setup
	fichero = fopen("texto.dat", "r");
	if (fichero == NULL)
		err("Al abrir fichero");
	xdrstdio_create(&operacion, fichero, XDR_DECODE);

	// Datos
	{
		{		//		Texto
			cadena = NULL;		// Las variables de tipo * hay que inicializarlas a NULL antes de decodificar
			xdr_Texto(&operacion, &cadena); // Cadena
			printf("Cadena: %s\n", cadena);
		} { //		Persona
			alumno.nombre = NULL;
			// alumno.edad = 22; // Las variables que no sean * no hace falta inicializarlas
			xdr_Persona(&operacion, &alumno); // Persona
			printf("Nombre: %s\n", alumno.nombre);
			printf("Edad: %d\n", alumno.edad);
	 } { //		Menu
		  res.Resultado_u.error = NULL;
		  xdr_Resultado(&operacion, &res); // Menu
			switch(res.caso)
			{
				case 1: printf("int: %d\n", res.Resultado_u.n); break;
				case 2: printf("double: %f\n", res.Resultado_u.x); break;
				case 3: printf("Texto: %s\n", res.Resultado_u.error); break;
				default: printf("Valor erroneo del selector\n");
			}
		}
	}

	// Cleanup
	xdr_destroy(&operacion);
	fclose(fichero);
	return 0;
}
