#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main ()
{
	char  *myString = "alex",
				*myOtherString = strdup(myString);

	printf("myOtherString: %s\n", myOtherString);

	free (myOtherString);
	
	return 0;
}
