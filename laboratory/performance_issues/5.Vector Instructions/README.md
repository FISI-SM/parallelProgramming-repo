
# Caso 5: Instrucciones Vectoriales (SIMD)

## Contexto
Los procesadores modernos ofrecen **extensiones SIMD (Single Instruction, Multiple Data)** que permiten realizar la misma operación sobre múltiples datos en paralelo, usando registros vectoriales. Para aprovechar esto, el código debe ser **vectorizable**.

## Versión común ❌
En la versión original, el compilador no necesariamente puede aplicar vectorización automáticamente porque:
- Falta información explícita sobre la independencia de datos.
- El código es interpretado como escalar.

Esto resulta en un uso subóptimo del hardware.

## Versión vectorizada ✅
Usando tipos vectoriales explícitos (`v4si`) y un acceso adecuado a los datos, se logra:
- Procesamiento de 4 enteros por instrucción.
- Reducción del número de iteraciones del bucle.
- Uso pleno de los registros SIMD del procesador.

## Relación con Programación Paralela 🔗
La vectorización y la paralelización **no son excluyentes**, sino complementarias. Un programa eficiente puede usar SIMD dentro de cada hilo (nivel de instrucción), y múltiples hilos para procesar diferentes partes del problema (nivel de tarea), como se discute en los capítulos finales del libro de Pacheco.
