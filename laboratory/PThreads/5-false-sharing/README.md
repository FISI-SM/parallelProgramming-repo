
# Caso 3: False Sharing

## Contexto
En sistemas con múltiples núcleos, los hilos comparten la memoria. Las cachés de los distintos núcleos utilizan protocolos de coherencia que mantienen sincronizadas las líneas de caché. Sin embargo, puede surgir un fenómeno llamado **false sharing** cuando distintos hilos acceden a variables diferentes que residen en la **misma línea de caché**.

## Versión con bajo rendimiento ❌
La versión inicial tiene dos hilos que modifican los campos `x` y `y` de una misma estructura. Aunque las variables son independientes, al estar en la misma línea de caché:
- Se producen **invalaciones de caché** constantes.
- El rendimiento se ve afectado por las **sincronizaciones implícitas** del hardware.

Este tipo de errores es difícil de detectar, pero tiene un gran impacto en programas paralelos.

## Versión optimizada ✅
En la versión optimizada se introduce un **padding** (relleno) entre las variables `x` e `y`, asegurando que:
- Cada campo reside en líneas de caché distintas.
- No hay interferencia entre los hilos.
- Se elimina el false sharing, mejorando significativamente el rendimiento, i.e **run in lower time.**  

## Relación con Programación Paralela 🔗
Este caso es paradigmático en el diseño de estructuras de datos paralelas. Evitar el false sharing es esencial para lograr una paralelización efectiva, especialmente en arquitecturas con muchos núcleos. Se alinea con la enseñanza de Pacheco sobre minimizar la **contención en memoria compartida**.
