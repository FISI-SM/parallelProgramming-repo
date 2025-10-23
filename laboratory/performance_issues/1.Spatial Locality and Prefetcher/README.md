
# Caso 1: Localidad Espacial y Prefetcher

## Contexto
En arquitecturas modernas de computadoras, la jerarquía de memoria juega un papel fundamental en el rendimiento. Cuando accedemos a datos en la memoria, idealmente queremos que estén presentes en la caché para evitar latencias elevadas. Esto es posible gracias al principio de **localidad espacial**, y a mecanismos como el **prefetcher**, que intenta anticiparse a los accesos cargando datos contiguos en la caché.

## Versión con bajo rendimiento ❌
En esta implementación, se accede a un vector de 100 MB de forma **aleatoria**. Esto rompe la localidad espacial porque los accesos a memoria no siguen un patrón predecible ni secuencial. Como resultado:
- El **prefetcher** no puede predecir los accesos.
- Se producen muchas **fallas de caché (cache misses)**.
- El rendimiento del programa se ve seriamente afectado.

Este patrón es típico de algoritmos que manipulan estructuras dispersas o no secuenciales, y si no se maneja adecuadamente, puede convertirse en un cuello de botella para la paralelización eficiente.

## Versión optimizada ✅
La versión mejorada también genera números aleatorios, pero **accede secuencialmente** al arreglo (`vec[i]` en vez de `vec[pos]`). Esto aprovecha:
- La **localidad espacial**: los elementos contiguos son cargados en bloques a la caché.
- El **prefetcher**, que trabaja de forma más efectiva al detectar el patrón secuencial.

Aunque sigue usando números aleatorios para mantener similitud con la lógica anterior, el acceso a memoria es mucho más eficiente.

## Relación con Programación Paralela 🔗
En programación paralela, el acceso eficiente a la memoria compartida entre hilos (threads) o procesos es esencial para la escalabilidad. Incluso con múltiples núcleos, si cada hilo accede a memoria de manera ineficiente (aleatoriamente o sin considerar la jerarquía de caché), los beneficios del paralelismo se ven anulados.

Este ejemplo refuerza un principio clave de Peter Pacheco: **el paralelismo efectivo depende tanto de la computación como del movimiento de datos**. Acceder eficientemente a la memoria es tan importante como dividir bien el trabajo entre hilos.
