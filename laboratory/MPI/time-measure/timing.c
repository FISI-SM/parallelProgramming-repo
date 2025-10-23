/*
 * Emilio Francesquini <e.francesquini@ufabc.edu.br>
 * 2018-10-01
 */

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <time.h>
#include <sys/time.h>
#include <x86intrin.h>

#define MICRO ((unsigned long) 1000000)
#define NANOS ((unsigned long)1000000000)
#define ITERS 300000000
long int temp = 0;

void foo () {
  for (int i = 0; i< ITERS; i++)
    temp+=temp;
}

int main() {

  printf("---------------------------------------\n");
  printf("gettimeofday()\n");
  struct timeval before, after;
  time_t         elapsedUs;
  gettimeofday(&before, NULL);
  foo();
  gettimeofday(&after, NULL);
  elapsedUs = after.tv_usec - before.tv_usec + (after.tv_sec - before.tv_sec) * MICRO;
  printf("Tiempo total: %lu us - %lf s - Resolución: %lu ns\n",  elapsedUs, (double)elapsedUs/MICRO, NANOS/MICRO);


  /*===============================================
    ===============================================
    ===============================================*/

  printf("---------------------------------------\n");
  printf("clock()\n");
  clock_t start = clock(); // Desbordamiento en 72 minutos en máquinas de 32 bits
  foo();
  double elapsedTime = (double)(clock() - start) / CLOCKS_PER_SEC;
  printf ("Tiempo total: %lf Resolución: %ld ns\n", elapsedTime, NANOS/CLOCKS_PER_SEC);

  /*===============================================
    ===============================================
    ===============================================*/

  printf("---------------------------------------\n");
  printf("clock_get_time()\n");
  uint64_t diff;
  struct timespec tick, tock;
  clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &tick);
  foo();
  clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &tock);
  diff = NANOS * (tock.tv_sec - tick.tv_sec) + tock.tv_nsec - tick.tv_nsec;
  printf("Tiempo total: %" PRIu64 " ns - %lf s\n", diff, (double)diff/NANOS);

  /* Tipos de relojes. Ver: man clock_gettime

     CLOCK_REALTIME
     Reloj del sistema que mide el tiempo real (es decir, tiempo de reloj de pared).

     CLOCK_REALTIME_COARSE (desde Linux 2.6.32; específico de Linux)
     Una versión más rápida pero menos precisa de CLOCK_REALTIME.

     CLOCK_MONOTONIC
     Reloj que no puede ser ajustado y representa el tiempo monótono desde un punto de inicio no especificado.

     CLOCK_MONOTONIC_COARSE (desde Linux 2.6.32; específico de Linux)
     Una versión más rápida pero menos precisa de CLOCK_MONOTONIC. Úsalo cuando necesitas marcas de tiempo muy rápidas, aunque no detalladas.

     CLOCK_MONOTONIC_RAW (desde Linux 2.6.28; específico de Linux)
     Similar a CLOCK_MONOTONIC, pero proporciona acceso a un tiempo basado en hardware sin ajustes de NTP ni incrementos de adjtime(3).

     CLOCK_BOOTTIME (desde Linux 2.6.39; específico de Linux)
     Igual que CLOCK_MONOTONIC, pero incluye el tiempo en que el sistema estuvo suspendido.

     CLOCK_PROCESS_CPUTIME_ID (desde Linux 2.6.12)
     Reloj de tiempo de CPU por proceso (mide el tiempo de CPU consumido por todos los hilos del proceso).

     CLOCK_THREAD_CPUTIME_ID (desde Linux 2.6.12)
     Reloj de tiempo de CPU específico del hilo.
  */

  struct timespec res;
  clock_getres(CLOCK_REALTIME, &res);
  printf("Resolución CLOCK_REALTIME: %" PRIu64 " ns\n",
         (uint64_t) NANOS * res.tv_sec + res.tv_nsec);
  clock_getres(CLOCK_REALTIME_COARSE, &res);
  printf("Resolución CLOCK_REALTIME_COARSE: %" PRIu64 " ns\n",
         (uint64_t) NANOS * res.tv_sec + res.tv_nsec);
  clock_getres(CLOCK_MONOTONIC, &res);
  printf("Resolución CLOCK_MONOTONIC: %" PRIu64 " ns\n",
         (uint64_t) NANOS * res.tv_sec + res.tv_nsec);
  clock_getres(CLOCK_MONOTONIC_COARSE, &res);
  printf("Resolución CLOCK_MONOTONIC_COARSE: %" PRIu64 " ns\n",
         (uint64_t) NANOS * res.tv_sec + res.tv_nsec);
  clock_getres(CLOCK_PROCESS_CPUTIME_ID, &res);
  printf("Resolución CLOCK_PROCESS_CPUTIME_ID: %" PRIu64 " ns\n",
         (uint64_t) NANOS * res.tv_sec + res.tv_nsec);
  clock_getres(CLOCK_THREAD_CPUTIME_ID, &res);
  printf("Resolución CLOCK_THREAD_CPUTIME_ID: %" PRIu64 " ns\n",
         (uint64_t) NANOS * res.tv_sec + res.tv_nsec);
  clock_getres(CLOCK_BOOTTIME, &res);
  printf("Resolución CLOCK_BOOTTIME: %" PRIu64 " ns\n",
         (uint64_t) NANOS * res.tv_sec + res.tv_nsec);


   /*===============================================
    ===============================================
    ===============================================*/

  /*
    Solo para información. Es complicado de usar porque existen varios
    problemas como:
    - No es compatible con todas las arquitecturas
    - No es compatible con todos los compiladores
    - Reordenamiento de instrucciones por el procesador
    - Variaciones de frecuencia
    - No mide en tiempo, sino en ciclos de reloj (desconocido y
      variable)
      - A menos que el procesador soporte "invariant TSC"
   */
  printf("---------------------------------------\n");
  printf("__rdtsc()\n");
  uint64_t tsc = __rdtsc();
  foo();
  uint64_t tsc2 = __rdtsc();
  uint64_t tscDiff = tsc2 - tsc;
  printf ("Tiempo total: %" PRIu64 " ciclos - Suponiendo 2.9GHz: %lf s\n", tscDiff, (double)tscDiff/2900000000.0);

  printf("---------------------------------------\n");
}
