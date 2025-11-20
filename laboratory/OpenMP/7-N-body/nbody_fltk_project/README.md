
# Visualización del problema de N-cuerpos con FLTK

Este proyecto implementa una simulación bidimensional simple del problema de N-cuerpos (N-body) con gravitación newtoniana y la visualiza usando la biblioteca gráfica FLTK.

---

## 1. Teoría básica del problema de N-cuerpos

### 1.1. Formulación física

El problema de N-cuerpos consiste en determinar el movimiento de \(N\) partículas que interactúan entre sí mediante fuerzas gravitacionales.

Para cada partícula \(i\):

- Masa: \(m_i\)
- Posición: \(\mathbf{s}_i(t) = (x_i(t), y_i(t))\)
- Velocidad: \(\mathbf{v}_i(t) = (v_{x,i}(t), v_{y,i}(t))\)

La fuerza gravitacional sobre \(i\) debida a otra partícula \(k\) viene dada por la ley de gravitación universal de Newton:

\[
\mathbf{F}_{ik} = -G \frac{m_i m_k}{r_{ik}^3} (\mathbf{s}_i - \mathbf{s}_k)
\]

donde:

- \(G\) es la constante de gravitación universal,
- \(\mathbf{s}_i - \mathbf{s}_k\) es el vector que une a \(k\) con \(i\),
- \(r_{ik} = \|\mathbf{s}_i - \mathbf{s}_k\|\) es la distancia entre las partículas \(i\) y \(k\).

La fuerza total sobre la partícula \(i\) es:

\[
\mathbf{F}_i = \sum_{\substack{k=1 \\ k \neq i}}^{N} \mathbf{F}_{ik}.
\]

Aplicando la segunda ley de Newton:

\[
m_i\, \mathbf{a}_i = \mathbf{F}_i \quad \Rightarrow \quad \mathbf{a}_i = \frac{\mathbf{F}_i}{m_i}.
\]

### 1.2. Discretización (método de Euler)

El método utilizado en el proyecto es Euler explícito:

\[
\mathbf{s}_i(t + \Delta t) = \mathbf{s}_i(t) + \Delta t\, \mathbf{v}_i(t)
\]

\[
\mathbf{v}_i(t + \Delta t) = \mathbf{v}_i(t) + \Delta t\, \mathbf{a}_i(t)
\]

Es simple pero no conserva bien la energía para integraciones largas.

### 1.3. Complejidad

Cada paso calcula todas las interacciones \(i \leftrightarrow k\); esto implica:

- Complejidad por paso: \(O(N^2)\).
- Complejidad total con \(T\) pasos: \(O(TN^2)\).

---

## 2. Estructura del proyecto

```
nbody_fltk_project/
├── Makefile
├── include/
│   ├── nbody_basic.h
│   └── nbody_view.h
├── src/
│   ├── nbody_basic.c
│   └── nbody_view.cpp
└── app/
    └── main.cpp
```

---

## 3. Instalación de FLTK

### Linux (Ubuntu / Debian)

```bash
sudo apt update
sudo apt install libfltk1.3-dev
```

Comprobar:

```bash
fltk-config --version
```

### Windows (MSYS2 MinGW 64-bit)

```bash
pacman -Syu
pacman -S --needed base-devel mingw-w64-x86_64-toolchain
pacman -S mingw-w64-x86_64-fltk
```

Comprobar:

```bash
which fltk-config
```

### macOS (Homebrew)

```bash
brew install fltk
```

---

## 4. Compilación y ejecución

Desde la carpeta del proyecto:

```bash
make
make run
```

Ejecutar con parámetros:

```bash
./nbody_fltk [n_particulas] [delta_t]
```

Ejemplos:

```bash
./nbody_fltk 20
./nbody_fltk 30 0.005
```

Limpiar:

```bash
make clean
```

---

## 5. Notas

- El integrador es Euler explícito (simple pero no estable a largo plazo).
- Las posiciones se escalan automáticamente a la ventana.
- Las condiciones iniciales alternan las velocidades en el eje Y.

---

## 6. Extensiones posibles

- Integradores de mayor orden (RK4, Verlet).
- Barnes–Hut para optimizar a \(O(N \log N)\).
- Botones para pausar, reiniciar o cambiar parámetros.
- Trayectorias de partículas.
