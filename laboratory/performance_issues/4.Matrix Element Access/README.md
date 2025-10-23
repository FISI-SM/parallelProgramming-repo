
# Caso 4: Orden de Acceso en Matrices (Row Major vs Column Major)

## Contexto
En C y C++, las matrices se almacenan en **orden de filas (row-major)**. Esto significa que los elementos consecutivos de una fila están almacenados uno al lado del otro en memoria. Acceder a la memoria de forma alineada con este orden permite aprovechar mejor la **localidad espacial** y la **caché**.

## Versión con bajo rendimiento ❌
En esta versión, el bucle externo recorre las columnas y el interno las filas (`j-i`). Esto implica:
- Accesos no contiguos en memoria.
- Bajo aprovechamiento de la caché.
- Alto número de fallos de caché (cache misses).

## Versión optimizada ✅
Invertir el orden de los bucles para recorrer primero las filas y luego las columnas (`i-j`) permite:
- Accesos secuenciales a memoria.
- Mejor uso del prefetcher y de la jerarquía de caché.
- Rendimiento notablemente superior, sin cambiar la lógica del programa.

## Relación con Programación Paralela 🔗
El orden de acceso a datos afecta la **distribución de carga** y la **eficiencia del paralelismo**. Un patrón de acceso mal diseñado puede inutilizar los beneficios de tener múltiples hilos si todos compiten por líneas de caché de forma ineficiente.
