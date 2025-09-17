Lista de Ejercicios de MPI
Descripción: Realizar un informe detallado de la solución de cada ejercicio.
Se considerará la correcta interpretación y abordaje de cada uno de ellos.

Repositorio de codigo: https://github.com/FISI-SM/parallelProgramming-repo/tree/main/exercises/MPI

Ejercicio 1:
Combinación de Mensajes utilizando Tags
Archivo de Consulta: hola-ex1.c
Archivo de Respuesta: hola-ex1-solucion.c
Descripción: una aplicación puede utilizar el parámetro tag en las funciones send y receive para distinguir mensajes. Utilice el programa hola-ex1.c y modifícalo para que el maestro envíe dos mensajes a cada esclavo, utilizando diferentes tags. Haga que cada esclavo reciba los mensajes en orden inverso, utilizando las tags y luego responda al maestro como en el archivo hola-ex1.c.
Ejercicio 2:
Convertir un código serial en paralelo
Archivo de Consulta: karp.c
Archivo de Respuesta: karp.soln.c
Datos de Entrada: data_values
Descripción: el programa karp.c calcula el valor de π usando una aproximación integral. Modifique este algoritmo para una versión paralela utilizando el enfoque SPMD.

Ejercicio 3:
Mostrar que la rutina de comunicación no bloqueante es más segura que la comunicación bloqueante
Archivo de Consulta: deadlock.c
Archivo de Respuesta: fixed.c
Descripción: compile el programa deadlock.c, especifique dos nodos a ser utilizados y ejecute el programa. El programa mostrará algunas líneas en la pantalla y luego se colgará. Es necesario finalizar el programa matando el proceso (Control+C). Observe el programa deadlock.c, ¿es capaz de identificar y entender por qué se cuelga? Corrija el programa para que pueda finalizarse, sustituyendo la comunicación bloqueante por la no bloqueante.
Ejercicio 4:
El método de los mínimos cuadrados es una técnica estándar de optimización matemática para encontrar el mejor ajuste para un conjunto de datos, intentando minimizar la suma de los cuadrados de las diferencias entre el valor estimado y los datos observados.
Archivo de Consulta: least-squares-pt2pt.c, new_sleep.c, least-squares.c, xydata
Archivo de Respuesta:
Descripción: Este ejercicio presenta varias oportunidades de paralelización, especialmente en la comunicación punto a punto y en la descomposición del dominio. Puede comenzar utilizando el programa least-squares-pt2pt.c y solucionar cada problema independientemente. Como alternativa puede utilizar el programa least-squares-pt2pt.c e ir incrementando el programa para solucionar todos los problemas.
El programa new_sleep.c debe ser utilizado solamente en procesadores Intel Xeon y HP Itanium en los cuales la función sleep() no puede ser utilizada.
Observe todo el código fuente y entienda cómo funciona el algoritmo. Observe cómo se utilizan las llamadas usando send y receive bloqueantes y cómo se realiza la descomposición de los datos.
Una versión serial del programa está presentada en least-squares.c.
En caso de que se utilice la función new_sleep.c, la forma correcta de compilar es:

mpicc least-squares-pt2pt.c new_sleep.o -o nombre_programa
Ejecute el programa modificando el número de procesos (entre 2 y 10).
Experimente cambiar las comunicaciones bloqueantes por las no bloqueantes (pt2_pt-nblk-comm.c).
El programa mostrado no está optimizado y es necesario realizar un balanceo de carga para mejorar su rendimiento. Esto se debe al hecho de que el último proceso posee el mayor número de datos que serán trabajados. Para mejorar el algoritmo es necesario reescribir los pasos 2 y 3 de least-squares-pt2pt.c. Una posible solución es observada en pt2pt-dat-decomp.c. Analice y entienda lo que fue realizado.
En el paso 4, el proceso 0 recibe todas las sumas parciales de los otros procesos. Reescriba este paso utilizando el árbol binario descrito a continuación:
➤ Divida los procesos en dos grupos. Cada proceso del grupo 2 (dos) envía su suma parcial al grupo 1 (uno).
➤ El primer grupo entonces es dividido en 2 y entonces el paso anterior es repetido hasta que el proceso 0 posea todas las sumas parciales (el proceso 0 debe estar en el primer grupo).

La Figura anterior muestra los dos pasos anteriores para 8 procesos.
Solución: pt2pt-bi-reduc.c (es necesario utilizar la opción -lm en la compilación).
Sugerencia: Combine todos los ejercicios en un único archivo.
Ejercicio 5:
Práctica de Comunicación Colectiva.
Archivo de Consulta: ex1.c, c.seed
Archivo de Respuesta: ex1.solved.c, ex1.c.data
Descripción: El programa está estructurado de la siguiente forma:
El proceso cero lee un número aleatorio (c.seed).
Ese número es enviado a todos los otros procesos.
Cada proceso calcula un número aleatorio basado en el número recibido y su rank.
El proceso con el mayor rank calcula el valor medio de los números aleatorios.
Cuatro (4) nuevos números aleatorios son generados por cada nodo.
El valor máximo y la desviación estándar de todos los números aleatorios son calculados.
Realice los siguientes pasos:
Lea el programa e identifique la estructura de cada uno de los pasos mostrados arriba.
Observe y describa cómo la rutina GetStats calcula el valor máximo y la desviación estándar de un vector de números.
Inserte la rutina necesaria para realizar una comunicación colectiva en los puntos indicados en el código fuente.
Compile el programa:

mpicc -o ex1 ex1.c -lmf
Especifique el número de procesos de 1 hasta 8.
Ejecute el programa. Si desea comparar su salida con el archivo de solución, cambie el valor en el archivo de datos:
f.seed a 12345.67890 para Fortran
c.seed a 123456 para C
Verifique la exactitud de su trabajo comparando la salida del programa con el archivo ex1.f.data para Fortran y ex1.c.data para C.
Ejercicio 6:
Práctica de Comunicación Punto a Punto.
Archivo de Consulta: mpi_latency.c, mpi_bandwidth.c
Archivo de Respuesta:
Descripción: Este ejercicio intenta mostrarte cómo elegir una buena conexión básica. En particular, al ejecutar mpi_latency una comunicación punto a punto es determinada. Solo se utilizan 2 (dos) procesos. La latencia puede ser muy diferente dependiendo de la “distancia” de los nodos en los cuales los procesos son ejecutados.
En el segundo experimento, se determinará el ancho de banda de la comunicación punto a punto. Actualmente, cualquier número par de procesos puede ser utilizado. Realice experimentos con diferentes tamaños de mensaje y diferentes números de proceso.
Analice el programa mpi_latency.c y entienda cómo funciona.
Compile el programa normalmente.
Ejecútelo con al menos 2 (dos) nodos y 2 (dos) procesos.
Lea el programa mpi_bandwidth.c e intente entender todos los parámetros.
Compile el programa variando el número de procesos. Explique cómo funciona el cambio en el ancho de banda.
Fije el número de procesos en 2 (dos). Modifique el tamaño del mensaje a 10000, 100000 y 1000000 y estime el ancho de banda. ¿Qué consigue observar?
Obs.: Para mensajes muy largos, disminuya el número de repeticiones; de lo contrario, el proceso demorará mucho en ejecutarse.
