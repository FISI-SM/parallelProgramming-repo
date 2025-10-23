# Resumen de Ejemplos OpenMP en C

| Archivo | Descripción |
|---------|-------------|
| `01_hello_parallel.c` | Este programa imprime un mensaje desde cada hilo usando la directiva #pragma omp parallel. |
| `02_set_num_threads.c` | Este programa muestra cómo fijar el número de hilos manualmente usando omp_set_num_threads. |
| `03_pi_reduction.c` | Este programa calcula una aproximación de PI utilizando reducción paralela con OpenMP. |
| `04_vector_add_parallel_for.c` | Este programa realiza la suma de dos vectores en paralelo usando #pragma omp parallel for. |
| `05_sections_example.c` | Este programa ejecuta diferentes secciones de código en paralelo utilizando la directiva sections. |
| `06_schedule_dynamic.c` | Este programa muestra cómo se distribuyen iteraciones dinámicamente entre los hilos. |
| `07_critical_example.c` | Este programa usa una región crítica para evitar condiciones de carrera al incrementar un contador. |
| `08_atomic_example.c` | Este programa utiliza la directiva atomic para asegurar una suma segura entre hilos. |
| `09_barrier_example.c` | Este programa usa una barrera para sincronizar los hilos en un punto determinado. |
| `10_master_example.c` | Este programa ejecuta una sección de código únicamente por el hilo maestro con la directiva master. |
| `11_private_firstprivate.c` | Este programa demuestra el uso de variables private y firstprivate dentro de un bloque paralelo. |
| `12_lastprivate_example.c` | Este programa ilustra cómo obtener el valor de la última iteración usando lastprivate. |
| `13_ordered_example.c` | Este programa garantiza el orden de impresión usando la directiva ordered en un bucle paralelo. |
| `14_single_example.c` | Este programa usa la directiva single para ejecutar una sección en un único hilo. |
| `15_lock_example.c` | Este programa protege una región crítica usando cerrojos explícitos con omp_lock_t. |
| `16_nested_parallelism.c` | Este programa demuestra el uso de paralelismo anidado (nested parallelism). |
| `17_get_wtime_example.c` | Este programa mide el tiempo de ejecución usando omp_get_wtime. |