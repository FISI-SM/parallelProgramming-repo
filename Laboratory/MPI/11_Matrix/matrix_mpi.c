#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define HEIGHT 30
#define DELAY 100000 // 0.1 segundos (en microsegundos)
#define RESET_CURSOR "\033[0;0H"
#define GREEN "\033[0;32m"
#define CLEAR "\033[2J"

void move_cursor(int row, int col)
{
  printf("\033[%d;%dH", row, col);
  fflush(stdout);
}

int main(int argc, char *argv[])
{
  int rank, size;

  // Deshabilita el buffering de stdout
  setbuf(stdout, NULL);

  // Inicializar MPI
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  // Semilla distinta para cada proceso
  srand(time(NULL) + rank * 100);

  // El proceso 0 limpia la pantalla y posiciona el cursor
  if (rank == 0)
  {
    printf(CLEAR RESET_CURSOR);
    fflush(stdout);
  }
  MPI_Barrier(MPI_COMM_WORLD);

  // Cada proceso maneja su propia columna
  int col = rank + 1;
  while (1)
  {
    // Imprime la columna con números aleatorios
    for (int row = 1; row <= HEIGHT; row++)
    {
      int digit = rand() % 10;
      move_cursor(row, col);
      printf(GREEN "%d", digit);
      fflush(stdout);
      usleep(DELAY);
    }
    // Borra la columna antes de reiniciar
    for (int row = 1; row <= HEIGHT; row++)
    {
      move_cursor(row, col);
      printf(" ");
      fflush(stdout);
    }
    usleep(DELAY);
  }

  MPI_Finalize();
  return 0;
}
