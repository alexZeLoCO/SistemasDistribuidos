#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include "util.h"

// Función de utilidad que determina si los caracteres de una cadena son todos numericos
int valida_numero(char *str) {
  // A RELLENAR 4
  int i = 0;
  for (i = 0 ; *(str+i) != '\0' ; i++)
    if (*(str+i) < '0' || *(str+i) > '9') return FALSO;
  return CIERTO;
}

// Q: 0000.0000.0000.0000 es ip valida?
// Q: 255.255.255.255 es ip valida?
// Función de utilidad que valida si una cadena de caracteres representa una IPv4 valida
int valida_ip(char *ip)
{
    // Comprueba si la cadena contiene una ip válida
    // A RELLENAR 4
    int i = 0,
        dot_count = 4,
        int_count = 0,
        last_was_dot = FALSO;
    for (i = 0 ; *(ip+i) != '\0' ; i++)
    {
      if (*(ip+i) == '.')
      {
        if (dot_count--==0 || last_was_dot) {
          return FALSO;
        }
        last_was_dot = CIERTO;
        int_count = 0;
      }
      else
      {
        if (
            atoi(ip+i) > 255 || // ip section can't go over 255
            int_count++>3 || // ip can't have 1523
            *(ip+i) < '0' || *(ip+i) > '9' // Nan
            ) return FALSO;
        last_was_dot = FALSO;
      }
    }
    return CIERTO;
}

// Función de utilidad, para generar los tiempos aleatorios entre un
// min y un max
double randRange(double min, double max)
{
  return min + (rand() / (double) RAND_MAX * (max - min + 1));
}


// Función de utilidad para depuración. Emite por pantalla el mensaje
// que se le pasa como parámetro, pero pone delante del mensaje un
// timestamp, para poder ordenar la salida por si saliera desordenada
//
// Ejemplo de uso:
//
//  log_debug("Mensaje a mostrar por pantalla")
//
void log_debug(char *msg){
  struct timespec t;
  clock_gettime(_POSIX_MONOTONIC_CLOCK, &t);
  printf("[%ld.%09ld] %s", t.tv_sec, t.tv_nsec, msg);
}

