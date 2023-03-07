#include <stdio.h>

int main()
{
	unsigned long int numero = 0xe7b1730b;  // Pon el tuyo
	double segundos_por_anno = 365.25 * 24 * 60 * 60;
	double annos = numero / segundos_por_anno;
	printf("%f\n", annos);
	return 0;
}
