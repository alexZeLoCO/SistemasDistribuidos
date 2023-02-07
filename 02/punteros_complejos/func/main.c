#include <stdio.h>

int* round_mult (double* a, double* b) {
	return &((int)(a*b));
}

int main ()
{
	int* (*foo_ptr) (double*, double*) = round_mult;
	printf("%d\n" *(foo_ptr(0.5, 2.0)));
	return 0;
}
