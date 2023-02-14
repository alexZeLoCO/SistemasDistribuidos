#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main ()
{
	/*
	 * fds contiene 2 posiciones.
	 * fds[0] es la salida estandar (pantalla por defecto)
	 * fds[1] es la entrada estandar (teclado por defecto)
	 *
	 * El proceso que genera datos los debe dejar en la salida estandar del pipe (fds[1])
	 * El proceso que recibe datos los debe recibir de la entrada estandar del pipe (fds[0])
	 *
	 * Por convenio se crean primero los hijos que leen y despues los que escriben.
	 */
	int fds[2];
	pid_t pid;
	pipe(fds); // Se crea el pipe

	if ((pid = fork()) < 0) // Errores
	{
		perror("No ha sido posible clonar el primer proceso.\n");
		return 1;
	}
	else if (pid == 0)
	{
		dup2(fds[0], 0);  // fds[0] es la entrada estandar
		close(fds[1]); // Se cierra el pipe que no se utiliza (salida estandar)
		execlp("sort", "sort", NULL); // Un hijo va a ejecutar SORT
		perror("No ha sido posible cambiar el contexto de ejecucion del primer hijo.\n");
		return 1;
	}
	else if ((pid = fork()) < 0)
	{
		perror("No ha sido posible clonar el segundo proceso.\n");
		return 1;
	}
	else if (pid == 0)
	{
		dup2(fds[1], 1); // Duplicar los datos correspondientes a la salida estandar (fds[1])
		close(fds[0]); // Se cierra el pipe que no se utiliza (entrada estandar)
		execlp("who", "who", NULL);
		perror("No ha sido posible cambiar el contexto de ejecucion del segundo hijo.\n");
		return 1;
	}
	else
	{
		close(fds[0]);
		close(fds[1]);
		wait(0);
		wait(0);
	}
	return 0;
}
