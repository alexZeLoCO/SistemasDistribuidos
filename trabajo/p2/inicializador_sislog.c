/*
Cliente de RPC que inicializa el servidor de sislog
*/
#include <rpc/rpc.h>
#include <sys/types.h>
#include <sys/times.h>
#include <unistd.h>
#include <pthread.h>
#include "sislog.h"
#include "util.h"


int  main(int argc,char *argv[])
{
   CLIENT *cl;
   faclevel params;
   char *ip_sislog;

   if (argc!=4)
   {
      fprintf(stderr,"Forma de uso: %s <max_facilidades> <max_levels> <ip_sislog>\n",argv[0]);
      exit(1);
   }
   if ((atoi((char *) argv[1])<=0) || (atoi((char *) argv[1])>MAXFACILITIES))
   {

      fprintf(stderr,"El parametro  <max_facilidades> debe ser >=0 y <=%d\n",MAXFACILITIES);
      exit(3);
   }
   if ((atoi((char *) argv[2])<=0) || (atoi((char *) argv[2])>MAXLEVELS))
   {
      fprintf(stderr,"El parametro  <max_levels> debe ser >=0 y <=%d\n",MAXLEVELS);
      exit(3);
   }
   ip_sislog=strdup(argv[3]);
   if (! valida_ip(argv[3]))
   {
      fprintf(stderr, "Error: El parámetro IP no es valido\n");
      exit(4);
   }

   // Conectamos con el servidor RPC pasándole los parámetros apropiados
   // para que inicialice sus estructuras de datos con el tamaño requerido
   // RELLENA ESTE HUECO
   |
   |
   |
   |

   printf("Sislog inicializado\n");
   return 0;
}
