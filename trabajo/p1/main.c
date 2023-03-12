#include <stdio.h>
#include "util.h"
#include "cola.h"

#include <stdlib.h>

int main (int argc, char** argv)
{
	Cola *la_cola = NULL;
	la_cola = (Cola*) malloc (sizeof(Cola*));
	dato_cola
		*uno = (dato_cola*) malloc (sizeof(dato_cola)),
		*dos = (dato_cola*) malloc (sizeof(dato_cola)),
		*tres = (dato_cola*) malloc (sizeof(dato_cola*)),
		*cuatro = (dato_cola*) malloc (sizeof(dato_cola*));
		
	uno->facilidad = '0';
	uno->nivel = '0';

	dos->facilidad = '1';
	dos->nivel = '1';

	tres->facilidad = '2';
	tres->nivel = '2';

	cuatro->facilidad = '3';
	cuatro->nivel = '3';

	inicializar_cola(la_cola, 3);

	printf("Inserta '0', '0'\n");
	insertar_dato_cola(la_cola, uno);

	printf("Inserta '1', '1'\n");
	insertar_dato_cola(la_cola, dos);

	printf("Inserta '2', '2'\n");
	insertar_dato_cola(la_cola, tres);


	printf("%c\n", obtener_dato_cola(la_cola)->nivel);
	printf("%c\n", obtener_dato_cola(la_cola)->nivel);

	printf("Inserta '3', '3'\n");
	insertar_dato_cola(la_cola, cuatro);

	printf("%c\n", obtener_dato_cola(la_cola)->nivel);
	printf("%c\n", obtener_dato_cola(la_cola)->nivel);

	destruir_cola(la_cola);


	return 0;
}
