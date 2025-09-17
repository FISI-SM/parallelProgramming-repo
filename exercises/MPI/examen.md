# Lista de Ejercicios de MPI

**Descripción:** Realizar un informe detallado de la solución de cada ejercicio.
Se considerará la correcta interpretación y abordaje de cada uno de ellos.

**Repositorio de código:** [https://github.com/FISI-SM/parallelProgramming-repo/tree/main/exercises/MPI](https://github.com/FISI-SM/parallelProgramming-repo/tree/main/exercises/MPI)

---

## Ejercicio 1: Combinación de Mensajes utilizando Tags

**Archivo de Consulta:** [`comunicacion_basica.c`](https://github.com/FISI-SM/parallelProgramming-repo/blob/main/exercises/MPI/comunicacion_basica.c)
**Archivo de Respuesta:** `comunicacion_basica_solucion.c`

**Descripción:** Una aplicación puede utilizar el parámetro tag en las funciones send y receive para distinguir mensajes. Utilice el programa [`comunicacion_basica.c`](https://github.com/FISI-SM/parallelProgramming-repo/blob/main/exercises/MPI/comunicacion_basica.c) y modifícalo para que el maestro envíe dos mensajes a cada esclavo, utilizando diferentes tags. Haga que cada esclavo reciba los mensajes en orden inverso, utilizando las tags y luego responda al maestro como en el archivo original.

---

## Ejercicio 2: Convertir un código serial en paralelo

**Archivo de Consulta:** [`aproximacion_pi.c`](https://github.com/FISI-SM/parallelProgramming-repo/blob/main/exercises/MPI/aproximacion_pi.c)
**Archivo de Respuesta:** `aproximacion_pi_solucion.c`
**Datos de Entrada:** `datos_valores`

**Descripción:** El programa [`aproximacion_pi.c`](https://github.com/FISI-SM/parallelProgramming-repo/blob/main/exercises/MPI/aproximacion_pi.c) calcula el valor de π usando una aproximación integral. Modifique este algoritmo para una versión paralela utilizando el enfoque SPMD.

---

## Ejercicio 3: Comunicación no bloqueante vs bloqueante

**Archivo de Consulta:** [`bloqueo_mutuo.c`](https://github.com/FISI-SM/parallelProgramming-repo/blob/main/exercises/MPI/bloqueo_mutuo.c)
**Archivo de Respuesta:** `bloqueo_mutuo_corregido.c`

**Descripción:** Compile el programa [`bloqueo_mutuo.c`](https://github.com/FISI-SM/parallelProgramming-repo/blob/main/exercises/MPI/bloqueo_mutuo.c), especifique dos nodos a ser utilizados y ejecute el programa. El programa mostrará algunas líneas en la pantalla y luego se colgará. Es necesario finalizar el programa matando el proceso (Control+C). Observe el programa [`bloqueo_mutuo.c`](https://github.com/FISI-SM/parallelProgramming-repo/blob/main/exercises/MPI/bloqueo_mutuo.c), ¿es capaz de identificar y entender por qué se cuelga? Corrija el programa para que pueda finalizarse, sustituyendo la comunicación bloqueante por la no bloqueante.

---

## Ejercicio 4: Método de los mínimos cuadrados

**Archivos de Consulta:**
- [`minimos_cuadrados.c`](https://github.com/FISI-SM/parallelProgramming-repo/blob/main/exercises/MPI/minimos_cuadrados.c)
- [`pausa_personalizada.c`](https://github.com/FISI-SM/parallelProgramming-repo/blob/main/exercises/MPI/pausa_personalizada.c)
- [`minimos_cuadrados_serial.c`](https://github.com/FISI-SM/parallelProgramming-repo/blob/main/exercises/MPI/minimos_cuadrados_serial.c)
- [`datos_xy.txt`](https://github.com/FISI-SM/parallelProgramming-repo/blob/main/exercises/MPI/datos_xy.txt)

**Archivo de Respuesta:** Variable según el sub-ejercicio

**Descripción:** El método de los mínimos cuadrados es una técnica estándar de optimización matemática para encontrar el mejor ajuste para un conjunto de datos, intentando minimizar la suma de los cuadrados de las diferencias entre el valor estimado y los datos observados.

Este ejercicio presenta varias oportunidades de paralelización, especialmente en la comunicación punto a punto y en la descomposición del dominio. Puede comenzar utilizando el programa [`minimos_cuadrados.c`](https://github.com/FISI-SM/parallelProgramming-repo/blob/main/exercises/MPI/minimos_cuadrados.c) y solucionar cada problema independientemente. Como alternativa puede utilizar el programa [`minimos_cuadrados.c`](https://github.com/FISI-SM/parallelProgramming-repo/blob/main/exercises/MPI/minimos_cuadrados.c) e ir incrementando el programa para solucionar todos los problemas.

### Instrucciones específicas:

1. El programa [`pausa_personalizada.c`](https://github.com/FISI-SM/parallelProgramming-repo/blob/main/exercises/MPI/pausa_personalizada.c) debe ser utilizado solamente en procesadores Intel Xeon y HP Itanium en los cuales la función `sleep()` no puede ser utilizada.

2. Observe todo el código fuente y entienda cómo funciona el algoritmo. Observe cómo se utilizan las llamadas usando send y receive bloqueantes y cómo se realiza la descomposición de los datos.

3. Una versión serial del programa está presentada en [`minimos_cuadrados_serial.c`](https://github.com/FISI-SM/parallelProgramming-repo/blob/main/exercises/MPI/minimos_cuadrados_serial.c).

4. En caso de que se utilice la función [`pausa_personalizada.c`](https://github.com/FISI-SM/parallelProgramming-repo/blob/main/exercises/MPI/pausa_personalizada.c), la forma correcta de compilar es:
   ```bash
   mpicc minimos_cuadrados.c pausa_personalizada.o -o nombre_programa
   ```

5. Ejecute el programa modificando el número de procesos (entre 2 y 10).

6. Experimente cambiar las comunicaciones bloqueantes por las no bloqueantes.

7. El programa mostrado no está optimizado y es necesario realizar un balanceo de carga para mejorar su rendimiento. Esto se debe al hecho de que el último proceso posee el mayor número de datos que serán trabajados.

8. En el paso 4, el proceso 0 recibe todas las sumas parciales de los otros procesos. Reescriba este paso utilizando el árbol binario descrito a continuación:
   - Divida los procesos en dos grupos. Cada proceso del grupo 2 envía su suma parcial al grupo 1.
   - El primer grupo entonces es dividido en 2 y entonces el paso anterior es repetido hasta que el proceso 0 posea todas las sumas parciales (el proceso 0 debe estar en el primer grupo).

**Nota:** Es necesario utilizar la opción `-lm` en la compilación.
**Sugerencia:** Combine todos los ejercicios en un único archivo.

---

## Ejercicio 5: Práctica de Comunicación Colectiva

**Archivos de Consulta:**
- [`comunicacion_colectiva.c`](https://github.com/FISI-SM/parallelProgramming-repo/blob/main/exercises/MPI/comunicacion_colectiva.c)
- [`semilla.seed`](https://github.com/FISI-SM/parallelProgramming-repo/blob/main/exercises/MPI/semilla.seed)

**Archivos de Respuesta:**
- `comunicacion_colectiva_solucion.c`
- [`datos_salida.data`](https://github.com/FISI-SM/parallelProgramming-repo/blob/main/exercises/MPI/datos_salida.data)

**Descripción:** El programa está estructurado de la siguiente forma:

1. El proceso cero lee un número aleatorio ([`semilla.seed`](https://github.com/FISI-SM/parallelProgramming-repo/blob/main/exercises/MPI/semilla.seed)).
2. Ese número es enviado a todos los otros procesos.
3. Cada proceso calcula un número aleatorio basado en el número recibido y su rank.
4. El proceso con el mayor rank calcula el valor medio de los números aleatorios.
5. Cuatro (4) nuevos números aleatorios son generados por cada nodo.
6. El valor máximo y la desviación estándar de todos los números aleatorios son calculados.

### Pasos a realizar:

1. Lea el programa e identifique la estructura de cada uno de los pasos mostrados arriba.
2. Observe y describa cómo la rutina `ObtenerEstadisticas` calcula el valor máximo y la desviación estándar de un vector de números.
3. Inserte la rutina necesaria para realizar una comunicación colectiva en los puntos indicados en el código fuente.
4. Compile el programa:
   ```bash
   mpicc -o comunicacion_colectiva comunicacion_colectiva.c -lm
   ```
5. Especifique el número de procesos de 1 hasta 8.
6. Ejecute el programa. Si desea comparar su salida con el archivo de solución, cambie el valor en el archivo de datos:
   - `semilla.seed` a `123456` para C
7. Verifique la exactitud de su trabajo comparando la salida del programa con el archivo [`datos_salida.data`](https://github.com/FISI-SM/parallelProgramming-repo/blob/main/exercises/MPI/datos_salida.data) para C.

---

## Ejercicio 6: Práctica de Comunicación Punto a Punto

**Archivos de Consulta:**
- [`latencia_mpi.c`](https://github.com/FISI-SM/parallelProgramming-repo/blob/main/exercises/MPI/latencia_mpi.c)
- [`ancho_banda_mpi.c`](https://github.com/FISI-SM/parallelProgramming-repo/blob/main/exercises/MPI/ancho_banda_mpi.c)

**Descripción:** Este ejercicio intenta mostrarte cómo elegir una buena conexión básica. En particular, al ejecutar [`latencia_mpi.c`](https://github.com/FISI-SM/parallelProgramming-repo/blob/main/exercises/MPI/latencia_mpi.c) una comunicación punto a punto es determinada. Solo se utilizan 2 (dos) procesos. La latencia puede ser muy diferente dependiendo de la "distancia" de los nodos en los cuales los procesos son ejecutados.

En el segundo experimento, se determinará el ancho de banda de la comunicación punto a punto. Actualmente, cualquier número par de procesos puede ser utilizado. Realice experimentos con diferentes tamaños de mensaje y diferentes números de proceso.

### Pasos a realizar:

1. Analice el programa [`latencia_mpi.c`](https://github.com/FISI-SM/parallelProgramming-repo/blob/main/exercises/MPI/latencia_mpi.c) y entienda cómo funciona.
2. Compile el programa normalmente.
3. Ejecútelo con al menos 2 (dos) nodos y 2 (dos) procesos.
4. Lea el programa [`ancho_banda_mpi.c`](https://github.com/FISI-SM/parallelProgramming-repo/blob/main/exercises/MPI/ancho_banda_mpi.c) e intente entender todos los parámetros.
5. Compile el programa variando el número de procesos. Explique cómo funciona el cambio en el ancho de banda.
6. Fije el número de procesos en 2 (dos). Modifique el tamaño del mensaje a 10000, 100000 y 1000000 y estime el ancho de banda. ¿Qué consigue observar?

**Obs.:** Para mensajes muy largos, disminuya el número de repeticiones; de lo contrario, el proceso demorará mucho en ejecutarse.

---

## Archivos auxiliares disponibles

- [`ex1.c.orig`](https://github.com/FISI-SM/parallelProgramming-repo/blob/main/exercises/MPI/ex1.c.orig) - Archivo original de respaldo
- [`ex1_c.mak`](https://github.com/FISI-SM/parallelProgramming-repo/blob/main/exercises/MPI/ex1_c.mak) - Makefile para compilación

---

*Todos los archivos de código fuente han sido traducidos al español para facilitar la comprensión y evitar búsquedas directas en internet.*