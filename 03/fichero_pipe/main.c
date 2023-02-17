#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main (int argc, char** argv)
{
	if (argc < 2)
	{
		printf("ERR. Uso: %s <nombre_fichero>\n", *(argv));
		return 1;
	}
	int fds[2];
	int fd;
	char buff[100];
	pid_t pid;
	pipe(fds); // Se crea el pipe

	if ((fd=open(*(argv+1, O_RDONLY)))<0)
	{
		perror("Open\n");
		return 2;
	}

	if ((pid = fork()) < 0) // Errores
	{
		perror("No ha sido posible clonar el primer proceso.\n");
		return 1;
	}
	else if (pid == 0)
	{
		dup2(fds[1], 1);  // fds[1] es la salida estandar
		close(fds[0]); // Se cierra el pipe que no se utiliza (entrada)
		while((cuantos=read(fd, buff, siezeof(buff))) > 0)
			write(fds[1], buff, cuantos);
		close(fd);
		close(fds[1]);
	}
	else if ((pid = fork()) < 0)
	{
		perror("No ha sido posible clonar el segundo proceso.\n");
		return 1;
	}
	else if (pid == 0)
	{
		dup2(fds[0], 0); // Duplicar los datos correspondientes a la entrada estandar (fds[0])
		close(fds[1]); // Se cierra el pipe que no se utiliza (salida estandar)
		while ((cuantos=read(fds[0], buff, sizeof(buff))) > 0)
			write(STDOUT_FILENO, buff, cuantos);
		close(fds[0]);
	}
	else
	{
		close(fds[0]);
		close(fds[1]);
		close(fd);
		wait(0);
		wait(0);
	}
	return 0;
}
