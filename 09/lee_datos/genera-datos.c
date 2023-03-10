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

	// Datos
	{
		{		//		Texto
			cadena = "Probando";
		} { //		Persona
			alumno.nombre = "Maria";
			alumno.edad = 22;
		} { //		Menu
			int opcion;
	
			printf("Elige una opcion:\n\t1. Entero\n\t2. Real\n\t3. Texto\nTu eleccion: ");
			scanf("%d", &opcion);
			while (opcion < 1 || opcion > 3)
				scanf("%d", &opcion);

			res.caso = opcion;
			switch(opcion)
			{
				case 1: printf("Introduce int: ");			scanf("%d", &(res.Resultado_u.n)); break;
				case 2: printf("Introduce double: ");		scanf("%f", &(res.Resultado_u.x)); break;
				case 3: printf("Introduce Texto: ");		res.Resultado_u.error = malloc(sizeof(char)*100);
									getchar(); fgets(res.Resultado_u.error, 99, stdin); break;
			}
		}
	}
	
	// Setup
	fichero = fopen("texto.dat", "w");
	if (fichero == NULL)
		err("Al abrir fichero");
	xdrstdio_create(&operacion, fichero, XDR_ENCODE);

	// Codificacion
	xdr_Texto(&operacion, &cadena); // Cadena
	xdr_Persona(&operacion, &alumno); // Persona
	xdr_Resultado(&operacion, (Resultado*) &res); // Menu

	// Cleanup
	xdr_destroy(&operacion);
	fclose(fichero);

	return 0;
}
