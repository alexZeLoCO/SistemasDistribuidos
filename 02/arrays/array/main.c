#include <stdio.h>
#include <stdlib.h>

#define ARRAY_SIZE 10

int main ()
{
	int	*array = (int*) malloc (ARRAY_SIZE * sizeof(int)),
	    i;

	for (i = 0 ; i < ARRAY_SIZE ; i++) *(array+i) = i;

	for (i = 0 ; i < ARRAY_SIZE ; i++)
		printf("array[%d] = %d\n", i, *(array+i));

	free(array);
	return 0;
}
