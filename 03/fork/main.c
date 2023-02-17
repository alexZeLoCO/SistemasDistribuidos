#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main () {
	int pid,
			status;

	if ((pid = fork()) < 0) {
		perror("Imposible crear subproceso\n");
	} else  if (pid == 0) {
		printf("Proceso hijo\n");
	} else {
		printf("Proceso padre\n");
		wait(&status);
		printf("Hijo terminado con estado %d\n", status);
	}


	return 0;
}
