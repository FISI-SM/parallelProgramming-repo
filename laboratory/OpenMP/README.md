# Instalación de OpenMP en Git Bash (Windows)

Git Bash **no incluye un compilador**, por lo que **no es posible
instalar OpenMP directamente en Git Bash**.\
Para usar OpenMP, debes instalar un compilador compatible como
**MSYS2/GCC** o **MinGW‑w64**.

------------------------------------------------------------------------

## ✅ Opción 1 (RECOMENDADA): MSYS2 + GCC con soporte OpenMP

### 1. Instalar MSYS2

Descargar desde: https://www.msys2.org/

### 2. Abrir la terminal

Usar **MSYS2 Mingw64**.

### 3. Instalar GCC con OpenMP

``` bash
pacman -Syu
pacman -S mingw-w64-x86_64-gcc
```

### 4. Compilar con soporte OpenMP

``` bash
gcc -fopenmp programa.c -o programa.exe
```

### 5. (Opcional) Usar GCC desde Git Bash

Agregar al PATH:

``` bash
echo 'export PATH="/c/msys64/mingw64/bin:$PATH"' >> ~/.bashrc
source ~/.bashrc
```

------------------------------------------------------------------------

## ✅ Opción 2: MinGW‑w64 (simple y rápida)

### 1. Descargar desde:

https://www.mingw-w64.org/

Recomendado: build **UCRT64** o **SEH**.

### 2. Instalar MinGW‑w64

Ruta típica:

    C:\mingw-w64\mingw64\bin

### 3. Agregar al PATH de Windows.

### 4. Verificar en Git Bash:

``` bash
gcc --version
```

### 5. Compilar con OpenMP

``` bash
gcc -fopenmp main.c -o main.exe
```

------------------------------------------------------------------------

## ❌ ¿Por qué no se "instala OpenMP" en Git Bash?

Git Bash es solo una terminal.\
Todo el soporte de OpenMP depende del **compilador**, no de Git Bash.

------------------------------------------------------------------------

## 🔥 Código ejemplo para probar OpenMP

``` c
#include <stdio.h>
#include <omp.h>

int main() {
    #pragma omp parallel
    {
        printf("Hola desde el hilo %d\n", omp_get_thread_num());
    }
}
```

Compilar:

``` bash
gcc -fopenmp test.c -o test.exe
```

------------------------------------------------------------------------

¿Quieres que también genere un `Makefile` listo para usar?
