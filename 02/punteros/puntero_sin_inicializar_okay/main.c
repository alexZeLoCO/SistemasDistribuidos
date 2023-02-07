#include <stdio.h>

int main ()
{
	int *p_i = NULL;	// Si las vars se inicializan a NULL, se evitan comportamientos erraticos
										// a cambio de un SIGSEGV.
	if (*p_i != NULL)
	{
		*p_i = 100;
		printf("El puntero apunta a la dirección: %p\n", p_i);
	}
	return 0;
}
