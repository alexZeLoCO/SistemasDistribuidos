#include "calculadora.h"
#include <stdio.h>
#include <stdlib.h>
#include <rpc/pmap_clnt.h>
#include <string.h>
#include <memory.h>
#include <sys/socket.h>
#include <netinet/in.h>

// Faltarian mas includes...

int main(int argc, char *argv[]) {
	CLIENT *clnt; // contendrá información sobre el servicio remoto que buscamos
	Operandos op;   // Esta variable será el parámetro al servicio
	int *res1; // Y aquí guardaremos la respuesta del servicio
	Resultado *res2

	// Inicializar la estructura con la información del servicio buscado
	// Hay que pasarle:
	//  1. IP o nombre de la máquina donde está el servidor (la obtenemos
	//     en este caso de la línea de comandos)
	//  2. Número de programa (o la constante que lo representa)
	//  3. Número de versión (o la constante que lo representa)
	//  4. Protocolo "tcp" o "udp"
	clnt = clnt_create(argv[1], CALCULADORA, BASICA, "udp");
	if (clnt==NULL) {
		clnt_pcreateerror("No puedo inicializar cliente");
		exit(1);
	}

	// ... A completar: inicialización de la variable op
	//     pidiéndole al usuario un par de números a sumar
	printf("Introduce el primer operando: ");
	scanf("%d", &op.op1);
	printf("Introduce el segundo operando: ");
	scanf("%d", &op.op2);

	// Realizar invocacion remota
	res1 = sumar_1(&op, clnt);
	// Mostrar resultado, recordar que devuelve un puntero
	if (res1 == NULL) {
		clnt_perror(clnt, "Fallo en la invocacion remota");
		exit(1);
	}
	// ... A completar, imprime el valor recibido
	printf("Resultado suma: %d\n", *res1);

	// Realizar invocacion remota
	res1 = restar_1(&op, clnt);
	// Mostrar resultado, recordar que devuelve un puntero
	if (res1 == NULL) {
		clnt_perror(clnt, "Fallo en la invocacion remota");
		exit(1);
	}
	// ... A completar, imprime el valor recibido
	printf("Resultado resta: %d\n", *res1);

	// Realizar invocacion remota
	res1 = multiplicar_1(&op, clnt);
	// Mostrar resultado, recordar que devuelve un puntero
	if (res1 == NULL) {
		clnt_perror(clnt, "Fallo en la invocacion remota");
		exit(1);
	}
	// ... A completar, imprime el valor recibido
	printf("Resultado multiplicacion: %d\n", *res1);

	clnt_destroy(clnt);
	return 0;
}
