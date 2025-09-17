/*
 * https://es.wikipedia.org/wiki/N%C3%BAmero_%CF%80
 *  ============================================================================
 * Name        : CalculoPI_Secuencial
 * Author      : Herminio Paucar
 * Description : Aproximación del número PI mediante la suma de Riemann.
 *               Este código es secuencial (no usa MPI). La fórmula utilizada:
 *               π = ∫₀¹ 4 / (1 + x²) dx
 *               Se divide el área en 'n' rectángulos, mientras mayor n, más preciso.
 * Objetivo    : Ver la mejora de precisión en función de n.
 * Compile     : mpicc -o build/CalculoPI_Secuencial CalculoPI_Secuencial.c -lm
 * Run         : ./build/CalculoPI_Secuencial 1000000
 * ============================================================================
 */

#include <math.h>   // Para fabs()
#include <stdio.h>  // Para printf()
#include <stdlib.h> // Para atoi()

int main(int argc, char *argv[])
{
  // Verifica que se pase el argumento de precisión
  if (argc < 2)
  {
    fprintf(stderr, "Uso: %s <precision>\n", argv[0]);
    exit(1);
  }

  // Obtiene la cantidad de divisiones (mayor n → mayor precisión)
  int n = atoi(argv[1]);

  if (n <= 0)
  {
    fprintf(stderr, "Error: la precision debe ser > 0\n");
    exit(1);
  }

  // Valor real de PI para comparar
  double PI25DT = 3.141592653589793238462643;
  double pi = 0.0;

  // Muestra el resultado y el error absoluto
  printf("PI25DT: %.30f\n", PI25DT);
  printf("My PI:  %.30f\n", pi);
  printf("Error:  %.30f\n", fabs(pi - PI25DT));

  return 0;
}
