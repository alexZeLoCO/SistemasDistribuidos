#include <stdio.h>
#include <stdlib.h>
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

int main (int argc, char** argv) 
{
	if (argc < 2)
	{
		printf("Forma de uso: %s <num_puerto>\n", argv[0]);
		return 1;
	}
	signal(SIGCHLD, atrapa_sigchld);
	int sfd_pasivo, sfd_datos, leidos, i;
	pid_t pid;
	struct sockaddr_in d_local;
	char buffer [100];
	sfd_pasivo = socket (PF_INET, SOCK_STREAM, 0);
	d_local.sin_family = AF_INET;
	d_local.sin_addr.s_addr = htonl(INADDR_ANY);
	d_local.sin_port = htons (atoi(*(argv+1)));
	bind(sfd_pasivo, (struct sockaddr*) &d_local, sizeof(d_local));
	listen(sfd_pasivo, SOMAXCONN);
	for (i = 0 ; i < 3 ; i++)
	{
		if((pid=fork())<0)
		{
			perror("Fallo en la creacion del pool\n");
		}
		else if (pid==0) break;
	}
	while (1)
	{
		sfd_datos = accept(sfd_pasivo, 0, 0); // Exclusion mutua asegurada por accept
		while ((leidos = read(sfd_datos, buffer, sizeof(buffer))) > 0)
			write(sfd_datos, buffer, leidos);	
		close(sfd_datos);
	}
	return 0;
}
