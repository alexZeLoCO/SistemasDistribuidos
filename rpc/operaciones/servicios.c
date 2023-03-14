#include "calculadora.h"

int * sumar_1_svc(Operandos * op,  struct svc_req *r) // No usaremos r
{
	static int resultado; // Variable que contendrá la respuesta del servicio
	// Lógica del servicio, algoritmo, etc..
	resultado = op->op1 + op->op2;
	return(&resultado);  // se retorna por referencia
}

// Etc... de igual modo el resto de servicios
int * restar_1_svc(Operandos * op,  struct svc_req *r) // No usaremos r
{
	static int resultado; // Variable que contendrá la respuesta del servicio
	resultado = op->op1 - op->op2;
	return(&resultado);  // se retorna por referencia
}

int * multiplicar_1_svc(Operandos * op,  struct svc_req *r) // No usaremos r
{
	static int resultado; // Variable que contendrá la respuesta del servicio
	resultado = op->op1 * op->op2;
	return(&resultado);  // se retorna por referencia
}

Resultado * dividir_1_svc(Operandos * op,  struct svc_req *r) // No usaremos r
{
	static Resultado resultado; // Variable que contendrá la respuesta del servicio
	resultado.Resultado_u.error = NULL;
	if (op->op2 == 0)
	{
		resultado.tipo = 3;
		resultado.Resultado_u.error = "Division por 0";
	}
	else if ((op->op1 % op->op2) != 0) 
	{
		resultado.tipo = 2;
		resultado.Resultado_u.real = (double) op->op1 / op->op2;
	}
	else
	{
		resultado.tipo = 1;
		resultado.Resultado_u.entero = op->op1 / op->op2;
	}
	return(&resultado);  // se retorna por referencia
}

