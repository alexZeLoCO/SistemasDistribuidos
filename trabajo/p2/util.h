#ifndef __UTIL_H__

#define CIERTO            1
#define FALSO             0

int valida_numero(char *str);
int valida_ip(char *ip);
double randRange(double min, double max);
void log_debug(char *msg);
void mostrar_recuento_eventos(int ncols, int nfils, char **filas,char ** columnas,int **valores);

#define __UTIL_H__
#endif
