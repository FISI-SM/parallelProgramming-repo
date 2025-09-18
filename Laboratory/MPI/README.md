# Instalación y Uso de MPI en Windows con WSL

Este documento explica cómo instalar y ejecutar programas MPI en **Windows Subsystem for Linux (WSL)**.

---

## 1. Verificar que WSL esté activo
En PowerShell (ejecutar como administrador):
```powershell
wsl --install
```

Si ya lo tienes, asegúrate de estar en **WSL2**:
```powershell
wsl --set-default-version 2
```

---

## 2. Instalar Ubuntu (si no lo tienes)
En la Microsoft Store instala **Ubuntu 22.04 LTS** (o la que prefieras).  
Luego abre Ubuntu desde el menú Inicio.

---

## 3. Actualizar paquetes
Dentro de Ubuntu (WSL):
```bash
sudo apt update && sudo apt upgrade -y
```

---

## 4. Instalar OpenMPI
```bash
sudo apt install -y openmpi-bin libopenmpi-dev
```

Esto instala:
- `mpicc` (compilador MPI para C).
- `mpirun` / `mpiexec` (ejecutores de programas MPI).

---

## 5. Verificar instalación
```bash
mpirun --version
```

---

## 6. Probar un programa MPI sencillo

### Crear archivo `hello.c`
```c
#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    printf("Hello from rank %d out of %d\n", rank, size);
    MPI_Finalize();
    return 0;
}
```

### Compilar
```bash
mpicc hello.c -o hello
```

### Ejecutar con 4 procesos
```bash
mpirun -np 4 ./hello
```

---

## 7. Alternativa: Instalar MPICH
Si prefieres **MPICH** en lugar de OpenMPI:
```bash
sudo apt install -y mpich
```

---

## 8. (Opcional) Crear Makefile básico para MPI
Ejemplo de `Makefile`:

```makefile
CC = mpicc
CFLAGS = -O2

all: hello

hello: hello.c
	$(CC) $(CFLAGS) hello.c -o hello

clean:
	rm -f hello
```

Compilar con:
```bash
make
```

Ejecutar con:
```bash
mpirun -np 4 ./hello
```

---
