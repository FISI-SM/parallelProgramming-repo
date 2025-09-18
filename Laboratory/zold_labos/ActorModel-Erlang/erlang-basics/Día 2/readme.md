El **plan del Día 2** del aprendizaje de Erlang está enfocado en **Pattern Matching y Variables**, con un enfoque práctico y directo para que puedas avanzar sin perder tiempo. Aquí está el cronograma detallado:

---

### **Cronograma del Día 2: Pattern Matching y Variables**
**Objetivo Principal**:  
Dominar el pattern matching (la base de la programación en Erlang) y entender la inmutabilidad de variables.

---

### **1. Mañana: Conceptos Clave (2-3 horas)**
#### **A. Pattern Matching Básico**
- **Qué es**: es el mecanismo central en Erlang para deconstruir y analizar estructuras de datos. A diferencia de otros lenguajes imperativos donde el operador `=` es una asignación, en Erlang `=` se utiliza para comparar estructuras y unir (ligar) variables a valores, siempre que la forma (la "forma estructural") del dato coincida.
- **Ejemplos**:
  1. Unión de Variables:
        ```erlang
        X = 10.
        ```
        Aquí, la variable X se une (binds) al valor 10. Si posteriormente usas X, ya tiene ese valor.
  2. Desestructuración de Estructuras:
        ```erlang
        {A, B} = {ok, 42}.
        ```
        Se descompone la tupla {ok, 42} y se asigna A = ok y B = 42, siempre que la estructura (dos elementos, en este orden) coincida.

  3. Fallos en el Pattern Matching:
        ```erlang
        {C, D} = {error}.
        ```
        Aquí intentamos desestructurar una tupla con dos elementos usando un patrón que espera dos elementos, pero {error} es una tupla de un solo elemento. Esto provoca un error de coincidencia (match error).

> El pattern matching se utiliza en múltiples contextos: en definiciones de función, en cláusulas case, y en construcciones receive para la concurrencia. Es una herramienta poderosa para garantizar que los datos cumplen con la estructura que esperamos antes de procesarlos.

#### **B. Inmutabilidad de Variables**
- **Regla**: En Erlang, **una vez que una variable se une a un valor, este vínculo es permanente en ese ámbito**. Esto significa que no se puede "re-asignar" una variable a un valor distinto. Esta característica es fundamental en la programación funcional y aporta ventajas como la ausencia de efectos secundarios impredecibles y la facilidad en la concurrencia.
  ```erlang
  Y = 5.
  Y = 5.   % Ok (mismo valor).
  Y = 10.  % Error: no match.
  ```

> La inmutabilidad facilita el razonamiento del código y es especialmente útil en sistemas concurrentes, ya que al no existir cambios en los datos, no se producen condiciones de carrera al compartir valores entre procesos.

#### **C. Wildcards (`_`)**
- **Uso**: El wildcard, representado por el guion bajo `_` en Erlang, se utiliza en pattern matching para indicar que cierta parte del dato debe ignorarse. El wildcard no une el valor a ninguna variable, de modo que se descarta ese elemento.

  ```erlang
  {_, Status} = {error, 404}. % Status = 404.
  ```
  El wildcard, representado por el guion bajo _ en Erlang, se utiliza en pattern matching para indicar que cierta parte del dato debe ignorarse. El wildcard no une el valor a ninguna variable, de modo que se descarta ese elemento.

> Esta herramienta es útil cuando no te interesa trabajar con toda la estructura, sino únicamente con algunas partes específicas.  

---
### **Ejercicio Práctico**:  
Crea una función `extraer_edad/1` que acepte una tupla `{usuario, nombre, edad}` y retorne la edad usando pattern matching.

#### Explicación y posible implementación: 

El objetivo es crear una función que reciba una tupla con la estructura `{usuario, nombre, edad}` y retorne el valor asociado a la edad. Podemos aprovechar el pattern matching para extraer directamente la edad y, si no se cumple el patrón esperado, el código fallará inmediatamente, lo cual es común en Erlang para detectar errores temprano.

```erlang
extraer_edad({usuario, _Nombre, Edad}) ->
    Edad.
```

Explicación del código:
- La función `extraer_edad/1` recibe una tupla de tres elementos.
- El patrón `{usuario, _Nombre, Edad}` indica que:
    - El primer elemento debe ser el átomo usuario.
    - El segundo elemento (nombre) se ignora utilizando _Nombre (porque no nos interesa en este caso).
    - El tercer elemento se une a la variable Edad, que es el valor que se devolverá.

Si la tupla no cumple exactamente con este patrón, se producirá un error de coincidencia, señalando que se pasó un dato con formato no esperado.

---

### 2. Tarde: Aplicación Práctica 
> (3-4 horas)
## A. Pattern Matching en Funciones

En Erlang, el pattern matching es la forma en que el lenguaje **desestructura** y **verifica** la conformidad de los datos. Cuando defines una función, puedes tener varias cláusulas (o definiciones) para la misma función, cada una con diferentes patrones en sus parámetros. Erlang evalúa las cláusulas en el orden definido y selecciona aquella cuyo patrón coincide con los argumentos (y, si es necesario, que cumpla con las guardas opcionales).

#### Ejemplo: Factorial

```erlang
-module(math).
-export([factorial/1]).

factorial(0) -> 1;
factorial(N) -> N * factorial(N - 1).
```

- **Primer cláusula (`factorial(0) -> 1`)**:  
  Este patrón se activa cuando el argumento es exactamente `0`. Funciona como el caso base en la recursión.
  
- **Segunda cláusula (`factorial(N) -> ...`)**:  
  Aquí el patrón acepta cualquier valor `N` que no haya sido capturado por la cláusula anterior. Se aplica de forma recursiva: la función multiplica `N` por el factorial de `N - 1`.  
  
Si llamas, por ejemplo, `factorial(3)`, Erlang evaluará las cláusulas en orden y aplicará la segunda, ya que `3` no coincide con el patrón `0`. Luego el proceso recursivo continuará hasta llegar a la cláusula base.

> **Dato Clave:** El operador `=` no es asignación en sentido imperativo, sino que realiza una **unión condicional** comprobando que las estructuras tengan la misma forma y luego uniendo valores a las variables correspondientes.


## B. Pattern Matching en Estructuras de Datos

El pattern matching se extiende a diversas estructuras de datos de Erlang, como listas y tuplas. Veamos cómo se utiliza con cada una:

### Listas

La forma más común de desestructurar una lista es usando el operador cons (`|`):

```erlang
[Primero | Resto] = [1, 2, 3].
```

- **`Primero`** se une al primer elemento (`1`).
- **`Resto`** se une a la lista restante (`[2, 3]`).

Esto es muy útil para procesar listas de forma recursiva, ya que permite separar fácilmente el primer elemento de la cola.

### Tuplas

El pattern matching en tuplas requiere que la estructura y la cantidad de elementos sean exactamente las del patrón:

```erlang
{ok, Resultado} = {ok, "Éxito"}.
```

- Aquí se verifica que la tupla tenga dos elementos y el primer elemento sea exactamente el átomo `ok`.  
- Luego, el segundo valor se une a la variable `Resultado`.


## Ejercicio Práctico: Implementa `suma_lista/1`

El objetivo es crear una función recursiva que reciba una lista de números y devuelva la suma de todos sus elementos. Con pattern matching, distinguiremos dos casos: el caso base (lista vacía) y el caso recursivo (lista no vacía, con cabeza y cola).

### Implementación

```erlang
-module(math).
-export([suma_lista/1]).

suma_lista([]) ->
    0;  % Caso base: la suma de una lista vacía es 0.
suma_lista([Cabeza | Cola]) ->
    Cabeza + suma_lista(Cola).
```

### Explicación del Código

1. **Caso Base:**
   ```erlang
   suma_lista([]) -> 0;
   ```
   - Si la lista es vacía (`[]`), la función retorna `0`. Esto previene llamadas infinitas y define el fin de la recursión.

2. **Caso Recursivo:**
   ```erlang
   suma_lista([Cabeza | Cola]) ->
       Cabeza + suma_lista(Cola).
   ```
   - El patrón `[Cabeza | Cola]` descompone la lista en dos partes:
     - **`Cabeza`**: el primer elemento de la lista.
     - **`Cola`**: el resto de la lista.
   - La función devuelve la suma del primer elemento (`Cabeza`) con el resultado de la suma de los elementos restantes (`suma_lista(Cola)`).

Cada llamada recursiva trabaja con una lista más pequeña hasta que se alcanza la lista vacía, en la que se devuelve `0` y se van sumando los valores en el camino de regreso.

---

### **3. Noche: Proyecto Mini-Integrador**
> (1-2 horas) Opcional

**Descripción**:  
Crea un módulo `user_handler` que:
1. Defina una función `crear_usuario/3` (similar al Día 1, pero con pattern matching).
2. Use pattern matching para manejar diferentes formatos de entrada:
   - Ejemplo: `{ok, Usuario}` vs `{error, Reason}`.

**Código de Ejemplo**:
```erlang
-module(user_handler).
-export([crear_usuario/3, manejar_respuesta/1]).

crear_usuario(nombre, Edad, Hobbies) when is_list(Hobbies) ->
    {usuario, nombre, Edad, Hobbies}.

manejar_respuesta({ok, Data}) -> io:format("Éxito: ~p~n", [Data]);
manejar_respuesta({error, Msg}) -> io:format("Error: ~s~n", [Msg]).
```

---

### **Errores Comunes (¡Evítalos!)**
1. **Confundir `=` con asignación**:
   ```erlang
   % Incorrecto:
   X = 10,
   X = X + 1. % Error: no match.
   ```
2. **Olvidar que `_` es irrestricto**:
   ```erlang
   {_, _} = {1, 2}. % Válido, pero oculta datos.
   ```

---

### **Recursos para el Día 2**
- **Libro**: "Learn You Some Erlang" (Capítulos 2 y 3).
- **Ejercicios**: [Erlang.org > Examples](https://www.erlang.org/doc/programming_examples/funs.html).
- **Práctica Interactiva**: Usa el shell (`erl`) para probar todos los ejemplos.

---

### **Checklist del Día 2**
✅ Entender que `=` es pattern matching, no asignación.  
✅ Aprender a usar variables inmutables.  
✅ Dominar el uso de `_` para ignorar valores.  
✅ Implementar funciones con múltiples cláusulas.  
✅ Practicar con listas, tuplas y estructuras anidadas.  

---

Con esto, estarás listo para avanzar al **Día 3: Funciones y Módulos**. ¡No copies código, escríbelo desde cero para reforzar tu aprendizaje! 🚀