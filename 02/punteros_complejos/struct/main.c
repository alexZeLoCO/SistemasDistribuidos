#include <stdio.h>

struct Complejo {
	double real;
	double imag;
};
	
int main ()
{
	struct Complejo c;
	c.real = 10.5;
	c.imag = 11.5;
	struct Complejo *p;

	p = &c;

	printf("(*p).real;=;%f\n", (*p).real);
	printf("p->real;=;%f\n", p->real);

	return 0;
}
