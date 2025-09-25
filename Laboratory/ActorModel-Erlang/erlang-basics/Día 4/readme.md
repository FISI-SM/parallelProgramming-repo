# **Día 4: Recursión y Tail Recursion**  

### **Objetivo General**

El objetivo es familiarizarse con la forma en que Erlang maneja la iteración. Dado que en Erlang no existen bucles tradicionales como `for` o `while`, se recurre a la **recursión**. Además, se busca aprender no solo a implementar soluciones recursivas, sino a optimizarlas usando **tail recursion**, una técnica que evita el consumo innecesario de memoria en llamadas recursivas profundas.

---

### **1. Recursión Básica**

#### **A. Concepto de Recursión**

- **¿Qué es la recursión?**
  
  La recursión es una técnica en la que una función se llama a sí misma para resolver un problema dividiendo la tarea en subproblemas más simples.  
  Para evitar llamadas infinitas, se define siempre un **caso base** que detiene la recursión.

- **Por qué usarla en Erlang:**

  Erlang, al ser un lenguaje funcional, no incluye bucles imperativos (como `for` o `while`). Por eso, la recursión es la herramienta fundamental para iterar sobre datos o efectuar procesos repetitivos.

- **Ejemplo clásico: Factorial**

  El factorial de un número se define de manera recursiva:
  
  ```erlang
  -module(math).
  -export([factorial/1]).

  % Caso base: el factorial de 0 es 1
  factorial(0) -> 1;
  % Caso recursivo: N * factorial(N - 1)
  factorial(N) -> N * factorial(N - 1).
  ```

  En este ejemplo:
  
  - **Caso base:** `factorial(0) -> 1` detiene la recursión cuando se llega a cero.
  - **Caso recursivo:** Para cualquier otro número `N`, se calcula multiplicando `N` por el factorial de `N - 1`.

---

#### **B. Recursión con Listas**

- **Ejemplo de suma de elementos en una lista:**

  Cuando se trabaja con listas, la recursión permite recorrer cada elemento. Por ejemplo, para sumar los elementos de una lista, se define:
  
  ```erlang
  sum_list([]) -> 0;
  sum_list([Head | Tail]) -> Head + sum_list(Tail).
  ```

  En este caso:
  
  - **Lista vacía (`[]`):** Devuelve `0` (caso base).
  - **Lista no vacía (`[Head | Tail]`):** Suma la cabeza de la lista (`Head`) con el resultado de aplicar `sum_list` al resto de la lista (`Tail`).

---

### **Ejercicio: Función count_elements/1**

El ejercicio consiste en crear una función `count_elements/1` que cuente los elementos de una lista sin utilizar la función integrada `length/1`.

#### **Enfoque básico (no tail recursive):**

Una forma directa, pero no optimizada, sería definir la función de esta manera:

```erlang
count_elements([]) ->
    0;
count_elements([_Head | Tail]) ->
    1 + count_elements(Tail).
```

**Explicación:**  
- Para una lista vacía, se retorna `0`.  
- Para una lista con elementos, se ignora el elemento actual (por eso se usa `_Head` indicando que no nos interesa su valor) y se suma `1` al resultado de contar el resto (`Tail`).

---

#### **Uso de Tail Recursion para Optimización**

La **tail recursion** (recursión en cola) es una optimización en la que la llamada recursiva es la última operación que se realiza en la función. Esto permite al compilador reutilizar el mismo **stack frame** y evita la acumulación de llamadas recursivas, cosa muy útil cuando la lista es muy grande.

Para transformar la función anterior en tail recursive, se utiliza un **acumulador**:

```erlang
count_elements(List) ->
    count_elements(List, 0).

% Caso base: cuando la lista está vacía, se retorna el acumulador
count_elements([], Acc) ->
    Acc;
% Caso recursivo: se incrementa el acumulador y se continúa con la cola de la lista
count_elements([_Head | Tail], Acc) ->
    count_elements(Tail, Acc + 1).
```

**Explicación detallada:**

1. **Función envolvente:**  
   Definimos `count_elements/1` que llama a `count_elements/2` iniciando el acumulador (`Acc`) en `0`. Esto es una técnica común para mantener el contador de elementos mientras se recorre la lista.

2. **Caso base en tail recursion:**  
   Cuando la lista es vacía (`[]`), se retorna el valor acumulado. No se realizan operaciones pendientes tras la llamada recursiva.

3. **Caso recursivo en tail recursion:**  
   En cada llamada, se toma la cola `Tail` de la lista y se llama a la misma función, incrementando el acumulador en `1`. La llamada recursiva es la última operación que se ejecuta, lo que la convierte en tail recursive.

Esta versión tail recursive es más eficiente en cuanto a gestión de memoria y previene posibles desbordamientos de pila cuando se trabaja con listas extensas.

---

El aprendizaje se centra en comprender cómo la recursión puede reemplazar los bucles imperativos en Erlang y cómo transformarla en una versión tail recursive para optimizar el rendimiento.  

Incluso para tareas sencillas, entender y aplicar la recursión de esta forma te prepara para abordar problemas más complejos en Erlang, donde el manejo eficiente de los recursos es clave.

> [!NOTE] 
> ESTO FUE UN BREVE RECORDATORIO DE QUÉ ES LA RECURSIÓN PARA ENTONCES CAER EN EL TAIL RECURSIVE.  

---

### **2. Tarde: Tail Recursion (3-4 horas)**  
Vamos a profundizar en el tema de la **tail recursion** en Erlang y en cómo esta técnica ayuda a evitar problemas asociados a la recursión tradicional.

### **A. Problema de la Recursión Tradicional**

En una recursión tradicional, cada vez que la función se llama a sí misma, se crea un **frame** en la pila que contiene el estado de esa llamada. Por ejemplo, en el caso del factorial implementado de forma tradicional:

```erlang
factorial(0) -> 1;
factorial(N) -> N * factorial(N - 1).
```

Cada llamada a `factorial/1` espera el resultado de `factorial(N - 1)` para luego multiplicarlo por `N`. Esto significa que, a medida que el número `N` crece, se van acumulando operaciones pendientes en la pila. Si `N` es lo suficientemente grande, se corre el riesgo de agotar la memoria de la pila, resultando en un **desbordamiento de pila** (*stack overflow*).

Esta acumulación de frames es el riesgo inherente de la recursión tradicional sin optimización.

### **B. ¿Cómo Funciona la Tail Recursion?**

La **tail recursion** (recursión de cola) es una estrategia para reestructurar la recursión de forma que la última operación que se realiza en la función sea la llamada recursiva. Esto implica que no quedan operaciones pendientes después de la llamada, lo que permite que el compilador o runtime reutilice el mismo frame de la pila. El resultado es un uso de memoria constante, independientemente de la cantidad de llamadas recursivas.

El principio fundamental aquí es:  
> **La última operación en la función debe ser la llamada recursiva sin cálculos pendientes.**

#### **Ejemplo de Suma de Lista Optimizada**

Considera el siguiente ejemplo de una función para sumar los elementos de una lista usando tail recursion:

```erlang
sum_list_tail(List) -> sum_list_tail(List, 0). % Inicializa el acumulador

sum_list_tail([], Acc) -> Acc;
sum_list_tail([H | T], Acc) -> sum_list_tail(T, H + Acc).
```

**Análisis del Código:**  
- La función `sum_list_tail/1` sirve de envoltorio que inicializa el acumulador (`Acc`) en 0.
- En `sum_list_tail([], Acc) -> Acc`, cuando la lista está vacía, se devuelve el valor acumulado. Este es el caso base.
- En `sum_list_tail([H | T], Acc) -> sum_list_tail(T, H + Acc)`, el cálculo `H + Acc` se realiza **antes** de hacer la llamada recursiva, de modo que la llamada recursiva es la última operación que se ejecuta. No queda ninguna operación pendiente que deba realizarse al regresar de la recursión, lo cual es clave para que el compilador optimice la llamada reutilizando el mismo frame de la pila.

---

### **Ejercicio: Reescribir Factorial con Tail Recursion**

El mismo principio se aplica para reescribir la función factorial. En la implementación recursiva tradicional:

```erlang
factorial(0) -> 1;
factorial(N) -> N * factorial(N - 1).
```

La multiplicación `N * ...` se realiza *después* de que la llamada recursiva retorne, lo que impide que la función sea considerado tail recursive.

Para transformarla en tail recursive, se introduce un **acumulador** que almacena el producto acumulado. De esta forma, se realiza la operación de multiplicación antes de hacer la llamada recursiva:

```erlang
factorial_tail(N) -> factorial_tail(N, 1).

factorial_tail(0, Acc) -> Acc;
factorial_tail(N, Acc) -> factorial_tail(N - 1, N * Acc).
```

**Explicación Detallada:**  
- La función `factorial_tail/1` actúa como un envoltorio que inicia el acumulador con el valor `1`.
- En `factorial_tail(0, Acc) -> Acc`, se define el caso base: cuando `N` es 0, el acumulador contiene el resultado final.
- En `factorial_tail(N, Acc) -> factorial_tail(N - 1, N * Acc)`, calculamos `N * Acc` **antes** de llamar recursivamente a la función, garantizando que no quedan operaciones pendientes después de la llamada recursiva. La llamada recursiva es la última acción de la función, por lo que el compilador puede optimizarla en términos de memoria.

---

### **Ventajas de la Tail Recursion**

1. **Optimización de la Pila:**  
   Gracias a que no se acumulan frames en la pila, la tail recursion permite que funciones recursivas se ejecuten en un espacio de pila constante, evitando desbordamientos en casos de recursión profunda.
   
2. **Claridad en el Control del Flujo:**  
   Usar acumuladores permite tener un control explícito del estado a lo largo de la ejecución, haciendo que el flujo de la función sea más predecible y eficiente.

3. **Compatibilidad con Grandes Estructuras de Datos:**  
   Cuando se trabaja con listas o números muy grandes, la tail recursion es casi indispensable para no caer en errores de capacidad de la pila.

---

### **Profundizando: ¿Por Qué No Permitir Cálculos Pendientes?**

La idea central es que cualquier operación pendiente después de una llamada recursiva obliga al sistema a mantener el estado de esa operación, lo que requiere un espacio adicional en la pila. Si, por ejemplo, usamos la versión tradicional del factorial, cada multiplicación queda “esperando” a que la recursión subsecuente se resuelva:

```erlang
N * factorial(N - 1)
```

Aquí, la multiplicación es una operación pendiente hasta que `factorial(N - 1)` retorne su valor. En cambio, con la tail recursion, la multiplicación se realiza y se pasa el resultado ya calculado como argumento, eliminando la necesidad de “guardar” esa operación en el stack.

---

### **Conclusión**

La tail recursion es una técnica poderosa para escribir funciones recursivas de manera eficiente en Erlang. Al garantizar que la llamada recursiva sea la última operación en la función, podemos evitar la acumulación de llamadas en la pila y manejar procesos que requieren una alta profundidad recursiva sin temor a desbordamientos.

Si te interesa profundizar más, podríamos explorar cómo aplicar la tail recursion en otros patrones de procesamiento de datos, o incluso cómo se integran estas técnicas en procesos concurrentes en Erlang, aprovechando su modelo de actor. ¿Te gustaría indagar en estos temas?

---

### **3. Noche: Proyecto Integrador (1-2 horas)**  
**Descripción**:  
Crea un módulo `list_utils` que implemente:  
1. `map/2`: Aplica una función a cada elemento de una lista (usando recursión).  
2. `filter/2`: Filtra elementos basados en una condición (ej: números pares).  
3. **Requisito**: Usa tail recursion en ambas funciones.  

**Código de Ejemplo (map/2)**:
```erlang
-module(list_utils).
-export([map/2]).

map(Fun, List) -> map(Fun, List, []).

map(_, [], Acc) -> lists:reverse(Acc); % Invierte el acumulador
map(Fun, [H | T], Acc) -> map(Fun, T, [Fun(H) | Acc]).
```

**Cómo probarlo**:  
```erlang
1> c(list_utils).
2> Doble = fun(X) -> X * 2 end.
3> list_utils:map(Doble, [1, 2, 3]). % [2, 4, 6]
```

---

### **Errores Comunes (¡Evítalos!)**  
1. **Olvidar el caso base**:  
   ```erlang
   factorial(N) -> N * factorial(N - 1). % ¡Falta el caso base! Crash infinito.
   ```
2. **No invertir el acumulador en tail recursion**:  
   ```erlang
   map(Fun, [H | T], Acc) -> map(Fun, T, [Fun(H) | Acc]).
   % Si no se usa lists:reverse/1, el resultado estará al revés.
   ```

---

### Respuesta al Proyecto Integrador

Vamos a desmenuzar este proyecto integrador y a explicar en profundidad cada parte, para que entiendas tanto el propósito como la implementación y las consideraciones clave de la tail recursion en Erlang.

### **Contexto del Proyecto**

La idea es crear un módulo llamado `list_utils` que contenga funciones útiles para manipular listas. Se te pide que implementes dos funciones principales:

1. **`map/2`**: Aplica una función a cada elemento de una lista.
2. **`filter/2`**: Filtra los elementos de la lista de acuerdo a una condición (por ejemplo, seleccionar números pares).

Un requisito fundamental es que ambas funciones deben estar implementadas usando **tail recursion**. Esto es importante porque Erlang no dispone de bucles imperativos (for/while) y al usar recursión tradicional podrías enfrentarte a desbordamientos de pila en listas muy grandes.

### **Tail Recursion: El Concepto y su Aplicación**

### **¿Por qué usar Tail Recursion?**

En recursión tradicional, cada llamada a la función crea un nuevo *frame* en la pila que, en algunos casos, acumula operaciones pendientes. Por ejemplo, en un factorial hecho de forma "tradicional":  
```erlang
factorial(0) -> 1;
factorial(N) -> N * factorial(N - 1).
```  
La multiplicación `N * ...` queda pendiente hasta obtener el valor de `factorial(N - 1)`, lo que puede llevar a un desbordamiento de pila si la recursión es muy profunda.

La **tail recursion**, en cambio, se estructura de tal forma que la última operación de la función es la llamada recursiva. Eso permite al compilador reutilizar el mismo *stack frame*, haciendo el proceso muy eficiente en términos de memoria.

### **La Estrategia del Acumulador**

Para lograr tail recursion, frecuentemente se introduce un **acumulador** que lleva el estado parcial de la operación. En lugar de acumular operaciones pendientes, se calcula el resultado intermedio y se pasa como argumento a la siguiente llamada.

### **Explicación del Código de `map/2`**

El código de ejemplo para `map/2` es el siguiente:

```erlang
-module(list_utils).
-export([map/2]).

map(Fun, List) -> map(Fun, List, []).

map(_, [], Acc) -> lists:reverse(Acc); % Invierte el acumulador
map(Fun, [H | T], Acc) -> map(Fun, T, [Fun(H) | Acc]).
```

### **Desglose Línea por Línea**

1. **Definición del Módulo y de la Exportación:**  
   ```erlang
   -module(list_utils).
   -export([map/2]).
   ```  
   Se define el módulo `list_utils` y se indica que la función `map/2` estará disponible para usar desde fuera del módulo.

2. **Función Envolvente (`map/2`):**  
   ```erlang
   map(Fun, List) -> map(Fun, List, []).
   ```  
   Aquí se usa una función envolvente que llama a una versión interna (`map/3`) que utiliza un acumulador. Se inicia el acumulador en una lista vacía (`[]`).

3. **Caso Base de la Función Recursiva:**  
   ```erlang
   map(_, [], Acc) -> lists:reverse(Acc);
   ```  
   Cuando la lista que se está recorriendo está vacía, significa que ya procesamos todos los elementos. Como en cada llamada se ha ido agregando el resultado de aplicar `Fun` en forma de cabeza (usando `[Fun(H) | Acc]`), el acumulador contiene los elementos en **orden inverso**. Se utiliza `lists:reverse/1` para invertirlo y obtener el orden original.

4. **Caso Recursivo con Tail Recursion:**  
   ```erlang
   map(Fun, [H | T], Acc) -> map(Fun, T, [Fun(H) | Acc]).
   ```  
   Para una lista no vacía, se separa el primer elemento (`H`) y la cola (`T`). Se aplica la función `Fun` a `H` y se añade el resultado al frente del acumulador. La llamada recursiva es la última operación que se hace, lo que la convierte en una tail call.

### **Cómo Probar la Función**

El siguiente ejemplo de línea de comandos muestra cómo compilar y probar la función:

```erlang
1> c(list_utils).
2> Doble = fun(X) -> X * 2 end.
3> list_utils:map(Doble, [1, 2, 3]). % Esto debería devolver: [2, 4, 6]
```

- Se compila el módulo `list_utils`.
- Se define una función anónima `Doble` que multiplica un número por 2.
- Se llama a `list_utils:map/2` con la función `Doble` y la lista `[1, 2, 3]`, obteniendo una lista donde cada elemento ha sido duplicado.

### **Implementación Sugerida de `filter/2`**

Aunque en el ejemplo solo se muestra `map/2`, la idea para `filter/2` es similar en cuanto al uso de tail recursion. Una posible implementación sería:

```erlang
-module(list_utils).
-export([map/2, filter/2]).

filter(Pred, List) -> filter(Pred, List, []).

filter(_, [], Acc) ->
    lists:reverse(Acc);
filter(Pred, [H | T], Acc) ->
    NewAcc = case Pred(H) of
        true -> [H | Acc];
        false -> Acc
    end,
    filter(Pred, T, NewAcc).
```

Aquí se recorre la lista y, para cada elemento, se evalúa el predicado `Pred`. Si el elemento cumple la condición (`true`), se agrega al acumulador; si no, se sigue sin modificarlo. Al final se invierte el acumulador para recuperar el orden correcto.

---

### **Errores Comunes y Cómo Evitarlos**

1. **Olvidar el Caso Base:**  
   Un error frecuente es escribir una función recursiva sin incluir un caso base. Por ejemplo, en el siguiente ejemplo para el factorial:
   ```erlang
   factorial(N) -> N * factorial(N - 1). % ¡Falta el caso base! Se produciría un ciclo infinito.
   ```
   Sin un caso base, la función nunca termina de llamar a sí misma, lo que puede provocar un cierre inesperado y un crash en la ejecución.

2. **No Invertir el Acumulador en Tail Recursion:**  
   Cuando se utiliza un acumulador de manera tail recursive, el resultado se va construyendo en orden inverso. Si te olvidas de aplicar `lists:reverse/1` al final (en el caso base), el resultado estará invertido respecto al orden original de la lista.  
   ```erlang
   map(Fun, [H | T], Acc) -> map(Fun, T, [Fun(H) | Acc]).
   % Sin la reversión, la salida estará en el orden inverso.
   ```

---

### **Ventajas de Usar este Enfoque en Erlang**

- **Eficiencia en el Manejo de la Pila:**  
  Al garantizar que la llamada recursiva es la última operación (tail call), se evita la acumulación de marcos de pila, lo que es crucial para manejar listas largas sin provocar desbordamientos.

- **Código Más Predecible:**  
  El uso de acumuladores permite tener un control explícito sobre el estado durante la recursión, facilitando la depuración y mejorando la comprensión del flujo del programa.

- **Reutilización de Patrones:**  
  Este patrón (envolver una función recursiva en una versión tail recursive con acumulador) es común en Erlang. Una vez entendido, puedes aplicarlo a una gran variedad de problemas, desde operaciones en listas hasta procesamiento de estructuras más complejas.

---



### **Checklist del Día 4**  
✅ Entender la recursión como reemplazo de bucles.  
✅ Implementar funciones recursivas con casos base.  
✅ Dominar tail recursion con acumuladores.  
✅ Aplicar tail recursion en operaciones con listas.  

---

### **Recursos Clave**  
- **Libro**: *Learn You Some Erlang*, [Capítulo sobre recursión](http://learnyousomeerlang.com/recursion).  
- **Ejercicios**: [99 Prolog Problems adaptados a Erlang](https://www.ic.unicamp.br/~meidanis/courses/mc336/2009s2/prolog/problemas/).  

**Próximo paso**: En el Día 5 aprenderás **funciones de orden superior y guards**, que complementarán tu manejo de recursión.  

¡Practica escribiendo todo desde cero y usa el shell para ver los resultados en tiempo real! 🚀