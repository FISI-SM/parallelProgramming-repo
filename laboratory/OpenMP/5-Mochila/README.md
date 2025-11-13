# 🧭 Problema de la Mochila 0/1 Paralela con OpenMP

## *Misión: Operación "Carga Inteligente"*

### 📜 Historia narrativa

Eres parte del equipo de logística avanzada de la **Base Científica
Andina (BCA)**...

## 📂 Formato de entrada

    c 6
    o 4 3
    o 2 4
    o 3 2
    o 1 1
    o 3 3

## 📈 Diagrama de flujo -- Programación Dinámica (DP)

``` mermaid
flowchart TD
    A[Inicio] --> B[Leer archivo]
    B --> C[Leer capacidad y objetos]
    C --> D[Inicializar tabla DP]
    D --> E[i = 1]

    E --> F{ i ≤ n ? }
    F -- No --> G[Reconstruir solución]
    G --> H[Mostrar resultados]
    H --> I[Fin]

    F -- Sí --> J[w = 0]
    J --> K{ w ≤ C ? }

    K -- Sí --> L{ peso[i] ≤ w ? }
    L -- Sí --> M[dp[i][w] = max(...)]
    L -- No --> N[dp[i][w] = dp[i-1][w]]

    M --> O[w = w + 1]
    N --> O
    O --> K

    K -- No --> P[i = i + 1]
    P --> F
```

## 🧮 Pseudocódigo -- Mochila 0/1 con DP

### 1️⃣ Versión secuencial

    func MochilaDP(C, n, peso[], valor[]):

        para i = 0 hasta n:
            para w = 0 hasta C:
                dp[i][w] = 0

        para i = 1 hasta n:
            para w = 0 hasta C:
                si peso[i] <= w entonces
                    dp[i][w] = max(dp[i-1][w], valor[i] + dp[i-1][w - peso[i]])
                si no
                    dp[i][w] = dp[i-1][w]

### 2️⃣ Versión paralela (idea)

    para i = 1 hasta n:
        #pragma omp parallel for
        para w = 0 hasta C:
            ...

## 🚀 Compilación

    gcc principal1.c -o mochila -fopenmp -Wall
    gcc principal1_par.c -o mochila_par -fopenmp -Wall
