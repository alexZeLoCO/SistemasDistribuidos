#include <stdio.h>

int main (int argc, char** argv) 
{
	char			c = 'a';
	int				i = 0;
	double		z = 0.0;
	printf("tipo;operacion;resultado\n");

	printf("char;sizeof(c);%lu\n", sizeof(c));
	printf("int;sizeof(i);%lu\n", sizeof(i));
	printf("double;sizeof(z);%lu\n", sizeof(z));

	printf("char;&c;%p\n", &c);
	printf("int;&i;%p\n", &i);
	printf("double;&z;%p\n", &z);

	printf("char;sizeof(&c);%lu\n", sizeof(&c));
	printf("int;sizeof(&i);%lu\n", sizeof(&i));
	printf("double;sizeof(&z);%lu\n", sizeof(&z));

	return 0;
}
