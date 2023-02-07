#include <stdio.h>
#include <stdlib.h>

#define ARRAY_SIZE 10

void mostrar_array (int* array, int size)
{
	int i;
	for (i = 0 ; i < size ; i++)
		printf("array[%d] = %d\n", i, *(array+i));
	return;
}

void poner_ceros (int* array, int size)
{
	int i;
	for (i = 0 ; i < size ; i++)
		*(array+i) = 0;
	return;
}

int main ()
{
	int * array = (int*) malloc (ARRAY_SIZE * sizeof(int)),
			i;

	poner_ceros(array, ARRAY_SIZE);
	mostrar_array(array, ARRAY_SIZE);

	free(array);

	return 0;
}
