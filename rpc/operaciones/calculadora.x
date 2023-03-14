/* Fichero calculadora.x */

/* Declaración de tipos xdr usados por las funciones */
/* (a rellenar por el alumno) */
typedef string Texto<100>;

struct Operandos
{
	int op1;
	int op2;
};
typedef struct Operandos Operandos;

union Resultado switch (int tipo)
{
	case 1: int entero;
	case 2: double real;
	case 3: Texto error;
};
typedef union Resultado Resultado;

/* A continuación va la descripción del interfaz en idl */
program CALCULADORA {
	version BASICA {
		int sumar(Operandos) = 1;
		/* Resto de las funciones del interfaz a rellenar por el alumno*/
		int restar(Operandos) = 2;
		int multiplicar(Operandos) = 3;
		Resultado dividir(Operandos) = 4;
	} = 1;  /* Este es el número de versión */
} = 0x40001234;  /* Este es el número de programa [0x40000000 - 0x5FFFFFFF]*/

