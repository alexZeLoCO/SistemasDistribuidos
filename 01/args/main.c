#include <stdio.h>

int main (int argc, char** argv)
{
	int i = 0;
	printf("Estos son los %d argumentos:\n", argc);
	for (i = 0 ; i < argc ; i++)
	{
		printf("\tArgumento %d: %s\n", i, *(argv+i));
	}
	return 0;
}
