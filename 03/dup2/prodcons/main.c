/*
	 GIJÓN
	 GRADO EN INGENIERIA INFORMATICA
	 SISTEMAS DISTRIBUIDOS - CURSO 3º
	 MATERIAL DE LA ASIGNATURA
	 -------------------------
	 MECANISMO   : PIPES
	 FICHERO     : prodcons.c
	 DESCRIPCION : Se propone la realizacion de un programa en el que dos
	 procesos se envien a traves de un pipe un fichero de texto donde 
	 el que recibe debe mostrarlo por su salida standard.
	 */
#include <unistd.h>
#include <stdio.h>
int main(int argc, char** argv)
{
	int fds[2];
	pipe(fds);                  /*Crea un pipe */
					
	/*
	 * Este proceso debera enviar el fichero al otro proceso a traves
	 *        del pipe.
	 */
	if (fork() == 0) {
		/*Añadir algo */ 
		close(fds[1]);

	}
	 /* 
		* Este otro proceso es el que se debe encargar de obtener el
	 	*        fichero del pipe y mostrarlo por su salida standard. 
		*/
	else if ( fork() == 0) {
		/*Añadir algo */  
		close(fds[0]);
	}
	 /* 
		* El padre cierra ambos descriptores del pipe
		*         y espera la finalizacion de sus hijos 
		*/
	else {
		/* Añadir algo */
		close(fds[0]);
		close(fds[1]);
		wait(0);
		wait(0);
	}
	return 0;
}

