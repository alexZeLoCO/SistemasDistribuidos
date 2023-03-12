const MAXFACILITIES = 10;
const MAXLEVELS = 8;
const MAXMSG    = 1024;

typedef string texto<MAXMSG>;

struct eventsislog {
   int facilidad;
   int nivel;
   texto msg;
};

struct faclevel {
   int facilidad;
   int nivel;
};

union Resultado switch (int caso){  /* Exito o error? */
   case 0: int valor;               /* Resultado en caso de éxito */
   case 1: texto msg;               /* Mensaje en caso de error */
};

program SISLOG{
   version PRIMERA{
     Resultado inicializar_sislog(faclevel)=1;
     Resultado registrar_evento(eventsislog)=2;
     Resultado obtener_total_facilidad(int)=3;
     Resultado obtener_total_nivel(int)=4;
     Resultado obtener_total_facilidadnivel(faclevel)=5;
     Resultado obtener_num_facilidades(void)=6;
     Resultado obtener_num_niveles(void)=7;
     Resultado obtener_nombre_facilidad(int)=8;
     Resultado obtener_nombre_nivel(int)=9;
   }=1;
}=0x2022f001;

