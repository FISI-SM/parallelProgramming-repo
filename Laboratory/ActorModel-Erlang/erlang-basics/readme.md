### **Día 1: Introducción a Erlang y Sintaxis Básica**
**Objetivos**:
- Entender las características únicas de Erlang (inmutabilidad, concurrencia, tolerancia a fallos).
- Aprender a ejecutar código en el shell (`eshell`).
- Conceptos básicos.

**Contenido**:
1. **Instalación**:
   - Descargar Erlang/OTP desde [erlang.org](https://www.erlang.org/downloads).
   - Verificar la instalación con `erl -version`.
2. **Hola Mundo**:
   ```erlang
   % En eshell:
   io:format("Hola, Mundo!~n").
   ```
3. **Tipos de Datos Básicos**:
   - **Números**: `42`, `-3.14`.
   - **Átomos**: `hola`, `'Atomo con espacios'`.
   - **Listas**: `[1, 2, 3]`, `"Hola"` (las strings son listas de números).
   - **Tuplas**: `{nombre, "Juan"}`, `{ok, 200}`.
   - **Binarios**: `<<"datos binarios">>`.

**Ejercicio**:
- Crear un módulo sencillo que a través de varias funciones pueda crear usuarios, actualizar su edad y verificar si tiene un hobby en específico. Luego testear las funciones desde otro módulo, comprobando así el correcto uso de los las funciones definidas anteriormente. 

---

### **Día 2: Pattern Matching y Variables**
**Objetivos**:
- Dominar el pattern matching (la base de Erlang).
- Entender la inmutabilidad y asignación única.

**Contenido**:
1. **Pattern Matching**:
   ```erlang
   % Asignación:
   X = 10.           % X es 10.
   {A, B} = {ok, 42}. % A = ok, B = 42.
   [C | D] = [1,2,3]. % C = 1, D = [2,3].
   ```
2. **Variables Inmutables**:
   - No se pueden reasignar: `X = 5. X = 10.` → Error: **no match of right-hand side**.
3. **Wildcards** (`_`):
   - Ignorar valores: `{_, Status} = {error, 404}`.

**Ejercicio**:
- Desestructura la tupla `{nombre, "Ana", {edad, 30}}` para extraer la edad.
- Intenta reasignar una variable y observa el error.

---

### **Día 3: Funciones y Módulos**
**Objetivos**:
- Escribir funciones básicas.
- Crear y compilar módulos.

**Contenido**:
1. **Funciones Anónimas** (`fun`):
   ```erlang
   Suma = fun(A, B) -> A + B end.
   Suma(3, 5). % Retorna 8.
   ```
2. **Módulos**:
   ```erlang
   % math.erl
   -module(math).
   -export([factorial/1]). % Exporta la función factorial/1.

   factorial(0) -> 1;
   factorial(N) -> N * factorial(N-1).
   ```
3. **Compilar y Ejecutar**:
   - En la terminal: `erlc math.erl` → Genera `math.beam`.
   - En `eshell`: `c(math). math:factorial(5).` → 120.

**Ejercicio**:
- Crea un módulo `geo` con una función `area` que calcule el área de un círculo (radio como argumento).
- Compílalo y prueba con `geo:area(3)` (debe retornar ≈28.27).

---

### **Día 4: Recursión (¡No hay bucles en Erlang!)** 
**Objetivos**:
- Reemplazar bucles con recursión.
- Entender la recursión de cola (*tail recursion*).

**Contenido**:
1. **Recursión Simple**:
   ```erlang
   % Suma de una lista:
   suma_lista([]) -> 0;
   suma_lista([Cabeza | Cola]) -> Cabeza + suma_lista(Cola).
   ```
2. **Tail Recursion** (optimizada):
   ```erlang
   suma_lista_tail(Lista) -> suma_lista_tail(Lista, 0).
   suma_lista_tail([], Acum) -> Acum;
   suma_lista_tail([C | R], Acum) -> suma_lista_tail(R, Acum + C).
   ```

**Ejercicio**:
- Implementa una función recursiva para calcular el n-ésimo número de Fibonacci.
- Convierte la función a tail recursion usando un acumulador.

---

### **Día 5: Funciones de Orden Superior y Guards**
**Objetivos**:
- Usar funciones como `map`, `filter`, y `fold`.
- Aplicar guards para validar argumentos.

**Contenido**:
1. **Funciones de Orden Superior**:
   ```erlang
   Lista = [1, 2, 3].
   lists:map(fun(X) -> X * 2 end, Lista). % [2,4,6].
   lists:filter(fun(X) -> X > 2 end, Lista). % [3].
   ```
2. **Guards** (cláusulas de protección):
   ```erlang
   es_positivo(X) when X > 0 -> true;
   es_positivo(_) -> false.
   ```

**Ejercicio**:
- Crea una función `cuadrados_pares/1` que, usando `map` y `filter`, retorne los cuadrados de los números pares de una lista.
- Añade guards a tu función `factorial` para evitar números negativos.

---

### **Fin de Semana: Proyecto Integrador**
**Objetivo**: Aplicar todo lo aprendido en un mini-proyecto.

**Propuesta**:
- **Calculadora Estadística**:
  1. Módulo `stats` con funciones:
     - `maximo/1`: Retorna el máximo de una lista.
     - `promedio/1`: Calcula el promedio (usa tail recursion).
     - `filtrar_pares/1`: Retorna lista con números pares.
  2. Usa guards para validar entradas no vacías.
  3. **Extra**: Implementa `map` propio sin usar `lists:map`.

---

### **Consejos Clave**:
- **Erlang Shell**: Usa `eshell` para probar código rápidamente.
- **Inmutabilidad**: No forces el estilo imperativo (olvida los bucles `for`).
- **Recursos**:
  - [Erlang Documentation](https://www.erlang.org/doc/)
  - Ejercicios en [Exercism (Erlang Track)](https://exercism.org/tracks/erlang).

Con este ritmo, en 5 días tendrás las bases sólidas para empezar con la concurrencia en la semana 2. ¡Practica cada concepto con los ejercicios! 🚀