# Instalación de MPI en Linux Mint

Este documento describe cómo instalar y probar MPI (Message Passing Interface) en Linux Mint, utilizando Open MPI.

---

## 🔧 Instalación rápida

```bash
sudo apt update
sudo apt install openmpi-bin openmpi-common libopenmpi-dev
```

---

## ✅ Verificar instalación

```bash
mpirun --version
```

---

## 🧪 Ejemplo en C

Archivo: hola_mpi.c

```c
#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    printf("Hola desde el proceso %d\n", rank);

    MPI_Finalize();
    return 0;
}
```

---

## ⚙️ Compilar y ejecutar

```bash
mpicc hola_mpi.c -o hola_mpi
mpirun -np 4 ./hola_mpi
```

---

## 🔁 Alternativa MPICH

```bash
sudo apt install mpich
```

---

## 🚨 Problemas comunes

### mpirun no encontrado
```bash
sudo apt install openmpi-bin
```

### Error como root
```bash
mpirun --allow-run-as-root -np 4 ./hola_mpi
```

### SSH entre nodos
```bash
ssh-keygen
ssh-copy-id usuario@otro_nodo
```
