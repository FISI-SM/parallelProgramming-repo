# Visualización del problema de N-cuerpos con FLTK

Este proyecto implementa una simulación bidimensional del problema de N‑cuerpos con gravitación newtoniana y la visualiza usando la biblioteca gráfica FLTK.  
Todo el contenido matemático ha sido adaptado para que sea **100% compatible con GitHub Markdown**, sin depender de LaTeX.

---

## 1. Teoría básica del problema de N‑cuerpos

### 1.1. Formulación física

El problema de N‑cuerpos consiste en determinar el movimiento de N partículas que interactúan entre sí mediante fuerzas gravitacionales.

Para cada partícula i:

- **Masa:** m_i  
- **Posición:** s_i(t) = (x_i(t), y_i(t))  
- **Velocidad:** v_i(t) = (v_x,i(t), v_y,i(t))

### Fuerza gravitacional

La fuerza ejercida sobre la partícula i por la partícula k es:

F_ik = - G * (m_i * m_k) / r_ik^3 * (s_i - s_k)

donde:

- G es la constante de gravitación universal  
- r_ik es la distancia entre las partículas i y k  
- s_i - s_k es el vector que une a ambas partículas  

### Fuerza total

F_i = suma(k != i) de F_ik

### Segunda ley de Newton

m_i * a_i = F_i  
=>  
a_i = F_i / m_i

---

## 1.2. Discretización (método de Euler)

El integrador utilizado es Euler explícito.

Actualización de posición:

s_i(t + dt) = s_i(t) + dt * v_i(t)

Actualización de velocidad:

v_i(t + dt) = v_i(t) + dt * a_i(t)

Este método es simple pero puede generar errores de energía en simulaciones largas.

---

## 1.3. Complejidad computacional

Para cada paso se evalúan todas las interacciones entre pares de partículas:

Complejidad por paso: O(N^2)  
Complejidad total: O(T * N^2)

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
```
sudo apt update
sudo apt install libfltk1.3-dev
```

Ver versión:
```
fltk-config --version
```

### Windows (MSYS2 MinGW 64-bit)
```
pacman -Syu
pacman -S --needed base-devel mingw-w64-x86_64-toolchain
pacman -S mingw-w64-x86_64-fltk
```

Verificar instalación:
```
which fltk-config
```

### macOS (Homebrew)
```
brew install fltk
```

---

## 4. Compilación y ejecución

Compilar:
```
make
```

Ejecutar:
```
make run
```

Ejecutar con parámetros:
```
./nbody_fltk [n_particulas] [delta_t]
```

Ejemplos:
```
./nbody_fltk 20
./nbody_fltk 30 0.005
```

Limpiar:
```
make clean
```

---

## 5. Notas importantes

- El integrador es Euler explícito.  
- Las posiciones se escalan automáticamente a la ventana.  
- Las condiciones iniciales alternan las velocidades.  

---

## 6. Extensiones sugeridas

- Integradores más precisos (RK4, Verlet)  
- Algoritmo Barnes–Hut para mejorar de O(N^2) a O(N log N)  
- Botones de control (pausa, reinicio)  
- Visualización de trayectorias  

---

Archivo generado con compatibilidad total para GitHub.
