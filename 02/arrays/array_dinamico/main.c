#include <stdio.h>
#include <stdlib.h>


void mostrar_array (int* array, int size)
{
	int i;
	for (i = 0 ; i < size ; i++)
		printf("array[%d] = %d\n", i, *(array+i));
	return;
}

int main ()
{
	int *array,
			array_size;

	printf("Introduzca tamanno del array: ");
	scanf("%d", &array_size);

	array = (int*) malloc (array_size * sizeof(int));
	
	mostrar_array(array, array_size);

	free(array);

	return 0;
}
