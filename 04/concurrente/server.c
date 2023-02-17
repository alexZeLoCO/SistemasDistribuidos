#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/wait.h>
#include <signal.h>


void atrapa_sigchld (int sig)
{
	wait(0);
	return;
}

int main () 
{
	signal(SIGCHLD, atrapa_sigchld);
	int sfd_pasivo, sfd_datos;
	pid_t pid;
	struct sockaddr_in d_local;
	char buffer [100];
	int leidos;
	sfd_pasivo = socket (PF_INET, SOCK_STREAM, 0);
	d_local.sin_family = AF_INET;
	d_local.sin_addr.s_addr = htonl(INADDR_ANY);
	d_local.sin_port = htons (7890);
	bind(sfd_pasivo, (struct sockaddr*) &d_local, sizeof(d_local));
	listen(sfd_pasivo, SOMAXCONN);
	while (1)
	{
		sfd_datos = accept(sfd_pasivo, 0, 0);
		if ((pid=fork()) < 0) // Error de clonacion, se encarga el padre
			while ((leidos = read(sfd_datos, buffer, sizeof(buffer))) > 0)
				write(sfd_datos, buffer, leidos);	
		else if (pid == 0) // Clonacion exitosa, se encarga el hijo
		{
			while ((leidos = read(sfd_datos, buffer, sizeof(buffer))) > 0)
				write(sfd_datos, buffer, leidos);	
			close(sfd_datos);
			return 0;
		}
		close(sfd_datos); // El padre cierra el socket
	}
	return 0;
}
