# Simulador N-Body con OpenGL Moderno y Pthreads

Este proyecto implementa una simulación de cuerpos en interacción gravitacional (N-body problem) utilizando:

- **Paralelismo con Pthreads**
- **Visualización en tiempo real con OpenGL moderno (GLFW + GLEW)**
- **Colisiones con fusión de masas**

Cada cuerpo posee posición, velocidad y masa, y todos se influyen mutuamente de acuerdo con la ley de la gravitación universal de Newton. Los resultados se visualizan como puntos en una ventana gráfica.

---

## 🧠 ¿Qué es el problema N-Body?

El **problema de N cuerpos** consiste en predecir el movimiento de múltiples cuerpos que interactúan entre sí por una fuerza física, típicamente la **gravitación**. Tiene aplicaciones en astrofísica (órbitas planetarias, formación de galaxias), dinámica molecular y simulaciones de partículas.

Esta implementación resuelve las ecuaciones mediante un esquema de integración de Euler y detecta colisiones, fusionando los cuerpos para simular una coalescencia.

---

## 🚀 Cómo ejecutar el proyecto

### 🔧 Requisitos

- C++ compiler (g++ recomendado)
- CMake (opcional)
- **Linux** o **Windows (WSL o MinGW)**

### 📦 Dependencias

- GLFW
- GLEW
- OpenGL
- pthreads (ya integrado en Linux, en Windows se requiere MinGW o WSL)

### 🐧 Instalación en Linux (Ubuntu/Debian)

```bash
sudo apt update
sudo apt install build-essential libglfw3-dev libglew-dev libglm-dev
```

### 🪟 Instalación en Windows

#### Opción 1: Usar WSL (recomendado)
1. Instala WSL2 y Ubuntu desde Microsoft Store.
2. Sigue los pasos de instalación de Linux.

#### Opción 2: Usar MinGW
1. Instala MinGW con soporte para `pthread`, `glew`, `glfw`, y `opengl32`.
2. Asegúrate de agregar `glew32.dll` y `glfw3.dll` a tu PATH.

---

## 🧪 Compilación

### En Linux:

```bash
g++ main.cpp -o nbody -lglfw -lGLEW -lGL -lpthread
./nbody
```

### En Windows (MinGW):

```bash
g++ main.cpp -o nbody.exe -lglfw3 -lglew32 -lopengl32 -lpthread
nbody.exe
```

---

## 📂 Estructura del proyecto

```
.
├── main.cpp            # Código fuente principal
├── points.vert         # Vertex shader
├── points.frag         # Fragment shader
├── README.md           # Este archivo
```

---

## ✨ Características destacadas

- Simulación con hasta 1000 cuerpos simultáneos
- Paralelismo automático con 4 hilos (ajustable)
- Visualización en tiempo real con OpenGL moderno
- Colisiones por proximidad: los cuerpos se fusionan conservando masa y momento
- Ventana fija (sin maximizar)

---

## 📸 Captura esperada

Una ventana donde puntos blancos se mueven e interactúan gravitacionalmente. Al colisionar, algunos desaparecen y otros crecen (por fusión).

---

## 📜 Licencia

MIT License. Puedes usar, modificar y distribuir libremente este código con fines educativos y de investigación.