#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main () 
{
	int sfd_pasivo, sfd_datos;
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
		while ((leidos = read(sfd_datos, buffer, sizeof(buffer))) > 0)
		{
			write(sfd_datos, buffer, leidos);	
		}
		close(sfd_datos);
	}
	return 0;
}
