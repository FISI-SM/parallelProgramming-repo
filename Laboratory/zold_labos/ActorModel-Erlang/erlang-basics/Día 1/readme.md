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
   - **Números**: 
      - Enteros: 
        ```erlang
           Entero = 1. 
           Charles = 16.
           LH = 44. 
        ```
       - Flotantes:
           ```erlang
           Flotante = 1,24. 
           Pi = 3,1416. 
            ```
       - **Operaciones aritméticas:**
            ```erlang
            Suma = 5 + 2. % 7
            Resta = 5 - 2. % 3
            Multiplicacion = 5 * 2. % 10
            Division = 5 / 2.         % 2,5 -> todas las divisiones normales en Erlang 
                                      % devuelven números de punto flotante 
                                      % excepto las divisiones enteras
            DivisionEntera = 5 div 2. % 2 -> devuelven enteros 
            Modulo = 5 mod 2. % 1 -> Resto 
            ```
    ---
    - **Átomos**: Los átomos son constantes cuyo nombre indica literalmente su valor por lo que se utilizan mucho para definir estados o declarar tipos.
        - Ejemplo: 
            ```erlang
            Estado = ok.
            Error = {error, "Mensaje"}.
            % Más adelante se entenderá mejor el uso de los átomos
            ```
    ---
    ### **Listas**: 
    
    Las listas en Erlang son una de las estructuras fundamentales para almacenar colecciones ordenadas de elementos. Se representan utilizando corchetes `[]` y pueden contener cualquier tipo de dato (números, átomos, tuplas, otras listas, etc.), lo que las hace estructuras heterogéneas.
        
    - Ejemplo: 
        ```erlang
        ListaNumerica = [1, 2, 3, 4].
        ListaHeterogenea = [123, hola, {a, b}, "cadena"].
        ```
    ### Características Principales
    Implementación como Lista Ligada: Las listas en Erlang se implementan internamente como listas ligadas (o listas encadenadas). Esto significa que cada elemento (la cabeza de la lista) apunta a la lista que le sigue (la cola). Esta característica permite:
    - Acceso eficiente al primer elemento.
    - Facilidad para usar pattern matching y recursión.
    - Lista Vacía: La lista vacía se denota con `[]`. Es el caso base en muchas funciones recursivas que procesan listas.
    #### Operador Cons (|): Se utiliza para descomponer o construir listas. La sintaxis [Cabeza | Cola] permite separar el primer elemento del resto de la lista. Por ejemplo:
    ```erlang
        Lista = [1, 2, 3, 4],
        % Usando pattern matching para separar la cabeza y la cola:
        [PrimerElemento | Resto] = Lista.
        % PrimerElemento = 1, Resto = [2, 3, 4].
    ```
    #### Funciones de la Biblioteca lists: Erlang cuenta con el módulo lists que provee muchas funciones útiles, como:
    - length/1: Obtiene la cantidad de elementos.
    - member/2: Verifica si un elemento está en la lista.
    - map/2: Aplica una función a cada elemento.
    Además, existen muchas funciones para transformar, filtrar y trabajar con listas.
    #### Ejemplo de Uso con Recursión
    Un ejemplo clásico es sumar todos los elementos de una lista utilizando recursión y pattern matching:
    ```erlang
    sumar([]) ->
        0;  % Caso base: la lista vacía suma 0.
    sumar([Cabeza | Cola]) ->
        Cabeza + sumar(Cola).
    ```
    Aquí: La función `sumar/1` verifica si la lista está vacía (`[]`).
    Si no lo está, usa el patrón `[Cabeza | Cola]` para separar el primer elemento `(Cabeza)` y la lista restante `(Cola)`, sumándolos recursivamente.

    #### Listas y Cadenas de Texto
    
    En Erlang las cadenas de texto se representan como listas de números (donde cada número corresponde al código ASCII de uncarácter). Por ejemplo, la cadena "Hola" internamente es la lista [72, 111, 108, 97]. No obstante, en versiones modernas de Erlangse suele trabajar también con binarios para representar cadenas, ya que resultan más eficientes en ciertas operaciones.
        
    ---

    ### **Tuplas**: 
    Las tuplas en Erlang son estructuras de datos ordenadas e inmutables que permiten agrupar varios valores (que pueden ser de diferentes tipos) en una sola entidad. A continuación, desglosamos el ejemplo para entender mejor cómo funcionan:

    1. **Definición de Tuplas**
        - **Tupla vacía:**  
          ```erlang
          TuplaVacia = {}.
          ```  
          Esta línea define una tupla sin ningún elemento. Es poco común pero útil en ciertos contextos donde se quiere representar “nada” o algún estado particular.

        - **Tupla con elementos simples:**  
          ```erlang
          Coordenada = {x, y}.
          ```  
          Aquí se crea una tupla con dos elementos: los átomos `x` e `y`. Aunque parece una representación de coordenadas, ten en cuenta que simplemente se agrupan dos valores sin dotarlos de significado semántico, a diferencia de, por ejemplo, un registro.

        - **Tupla que combina información de un “usuario”:**  
          ```erlang
          Usuario = {nombre, "Ana", edad, 30}.
          ```  
          Este ejemplo muestra cómo se pueden agrupar datos heterogéneos. Aunque parece que estamos creando un "mapa" con etiquetas y valores, en Erlang esto es simplemente una tupla con cuatro elementos en orden: el átomo `nombre`, la cadena `"Ana"`, el átomo `edad` y el número `30`.

    2. **Pattern Matching con Tuplas** 

        El poder de las tuplas en Erlang reside en el **pattern matching**. Esto permite extraer valores directamente de la estructura:

        ```erlang
        {nombre, Nombre, edad, Edad} = Usuario.
        ```

        - En esta línea se hace *pattern matching* contra la tupla `Usuario`.  
        - Se espera que el primer elemento sea el átomo `nombre` y el tercero sea el átomo `edad`; de lo contrario, la coincidencia fallaría.
        - Las variables `Nombre` y `Edad` se vinculan con los valores correspondientes de la tupla, por lo que después de esta asignación, `Nombre` contendrá `"Ana"` y `Edad` contendrá `30`.

        El pattern matching en Erlang es muy poderoso y se utiliza para desestructurar datos de forma directa y concisa, facilitando el manejo de datos complejos.



    3. **Funciones Útiles para Tuplas**

        Erlang incluye funciones incorporadas para trabajar con tuplas, entre ellas:

        - **Acceso a un elemento específico:**  
          ```erlang
          Elemento = element(2, {a, b, c}).
          ```  
          La función `element/2` recibe dos argumentos: la posición (índice) y la tupla de donde extraer el elemento.  
          **Importante:** Los índices en Erlang comienzan en **1**. Por lo tanto, `element(2, {a, b, c})` devolverá el segundo elemento, es decir, `b`.

        - **Obtener el tamaño de una tupla:**  
          ```erlang
          Tamaño = tuple_size({a, b, c}).
          ```  
          La función `tuple_size/1` devuelve el número de elementos que contiene la tupla. En este caso, la tupla `{a, b, c}` tiene 3 elementos, por lo que `Tamaño` será `3`.

---
   ### **Binarios**: 

Los **binarios** en Erlang se usan para trabajar de forma eficiente con datos en bruto, como datos provenientes de archivos o de la red. Se representan utilizando la sintaxis `<<>>` y cada número dentro de la construcción representa un byte. Vamos a desglosar el ejemplo y explicar cada parte:


1. **Binario Simple:**

   ```erlang
   BinarioSimple = <<1, 2, 3>>.
   ```

   - Aquí se crea un binario que contiene tres bytes: 1, 2 y 3.
   - Este binario es inmutable y cada número se corresponde con un byte.

2. **Binario de Texto:**

   ```erlang
   TextoBinario = <<"Hola">>.  % Equivale a <<72, 111, 108, 97>>
   ```

   - Se construye un binario a partir de la cadena `"Hola"`.
   - Cada carácter se convierte en su código ASCII:  
     - `"H"` → 72  
     - `"o"` → 111  
     - `"l"` → 108  
     - `"a"` → 97  
   - El resultado es el binario `<<72, 111, 108, 97>>`.

3. **Binario Anidado:**

   ```erlang
   BinarioAnidado = << <<1,2>>, <<3,4>> >>.  % <<1,2,3,4>>
   ```

   - Se combinan dos binarios pequeños: `<<1,2>>` y `<<3,4>>`.
   - Al construir el binario anidado, Erlang "aplana" la estructura, resultando en `<<1,2,3,4>>`.

    #### Operaciones con Binarios

    1. **Obtener el Tamaño en Bytes:**

    ```erlang
    Tamaño = byte_size(<<1,2,3>>).  % Retorna 3
    ```

    - La función `byte_size/1` devuelve la cantidad de bytes que contiene el binario.
    - En este caso, `<<1,2,3>>` tiene 3 bytes.

    2. **Extraer una Parte con `binary:part/3`:**

       ```erlang
       Parte = binary:part(<<"Hola">>, 1, 2).  % Retorna <<"ol">>
       ```

       - **Función `binary:part/3`:**  
         Esta función se utiliza para extraer un segmento (sub-binario) del binario original. Toma tres argumentos:

         - **El binario original:** En este ejemplo, `<<"Hola">>`.
         - **La posición de inicio:** Aquí se usa `1`.  
           - En Erlang, los **índices en los binarios comienzan en 0**, al igual que en C++.
           - Esto significa que el índice `0` corresponde al primer byte, `1` al segundo, y así sucesivamente.
         - **La longitud en bytes a extraer:** En el ejemplo es `2`, por lo que extrae 2 bytes a partir del byte en la posición 1.
    
       - **Aplicación en el Ejemplo:**  
         El binario `<<"Hola">>` equivale a `<<72, 111, 108, 97>>`.  
         - El byte en el índice `0` es `72` (corresponde a `"H"`).
         - El índice `1` es `111` (corresponde a `"o"`).
         - El índice `2` es `108` (corresponde a `"l"`).  

         Con `binary:part(<<"Hola">>, 1, 2)` se extraen los bytes en las posiciones `1` y `2`, que representan `"o"` y `"l"`, es decir, se obtiene el binario `<<"ol">>`.

---

4. Conceptos básicos de **Erlang**:

    A continuación, te explico cada uno de estos conceptos en el contexto de Erlang:

    #### Inmutabilidad

    La inmutabilidad es una propiedad esencial en Erlang y en muchos lenguajes funcionales. Se refiere a que, una vez creado, un valor o dato no se puede modificar. Esto tiene varias implicaciones y ventajas:

    - **Sin efectos secundarios:** Al no poder modificarse un dato, no existen efectos laterales inesperados al compartir datos entre procesos o funciones. Cada operación que "modifica" una estructura, en realidad crea una nueva versión sin alterar la original.
    - **Facilita la concurrencia:** Dado que los datos no cambian, compartir información entre procesos es seguro, ya que no hay riesgo de que un proceso modifique un dato que otro proceso esté utilizando.  
    - **Simplifica el razonamiento:** La ausencia de estados mutables facilita la depuración y el mantenimiento del código, al reducir la complejidad en el manejo de estados internos.

    En Erlang, estructuras como listas, tuplas y otros tipos de datos son inmutables, lo que ayuda a construir sistemas robustos y predecibles.

    #### Concurrencia

    La concurrencia es uno de los pilares de Erlang y está diseñada para crear sistemas que puedan realizar múltiples tareas simultáneamente. Algunas características destacadas son:

    - **Modelo de actores:** Erlang implementa un modelo de concurrencia basado en actores. Cada actor es un proceso ligero con su propia memoria, lo que implica que no se comparte estado de forma directa entre procesos.  
    - **Comunicación mediante mensajes:** Los procesos se comunican exclusivamente mediante el envío y recepción de mensajes. Esto evita problemas comunes en entornos concurrentes, como condiciones de carrera o errores de sincronización.
    - **Escalabilidad y eficiencia:** Los procesos en Erlang son extremadamente livianos, lo que permite crear miles o incluso millones de ellos sin comprometer el rendimiento del sistema. Esto es crucial para aplicaciones de telecomunicaciones, sistemas distribuidos y otros entornos que requieren alta concurrencia.
  
    #### Tolerancia a Fallos

    La tolerancia a fallos es otra característica fundamental de Erlang, diseñada para construir sistemas altamente robustos y resilientes. Se basa en las siguientes ideas:

    - **Filosofía "Let It Crash":** En lugar de tratar de capturar y manejar cada posible error, Erlang adopta la mentalidad de "dejar que falle". Esto significa que se permite que un proceso falle sin que ello comprometa la integridad del sistema en general.
    - **Supervisión y reinicio automático:** Se utilizan árboles de supervisión (supervision trees) para monitorear los procesos. Cuando un proceso falla, su supervisor detecta el error y reinicia el proceso o toma otras acciones correctivas, garantizando que el sistema recupere su funcionamiento lo más rápidamente posible.
    - **Aislamiento de errores:** Gracias a la inmutabilidad y al modelo de procesos aislados, un fallo en un proceso no se propaga al resto del sistema. Cada proceso trabaja de forma independiente, lo que permite contener errores y reiniciar solo los componentes afectados.

    Esta capacidad de detectar y recuperarse de errores de manera automática es la razón principal por la que Erlang es tan utilizado en aplicaciones que requieren alta disponibilidad, como sistemas de telecomunicaciones y servicios en tiempo real.

     > Cada uno de estos conceptos—**inmutabilidad**, **concurrencia** y **tolerancia a fallos**—se complementa en Erlang para crear sistemas distribuidos, escalables y altamente resilientes, ideales para entornos donde la estabilidad y la capacidad de recuperación son críticas.

---

### Ejercicio:
- Crear un módulo sencillo que a través de varias funciones pueda crear usuarios, actualizar su edad y verificar si tiene un hobby en específico. Luego testear las funciones desde otro módulo, comprobando así el correcto uso de los las funciones definidas anteriormente. 

---

### **Consejos Clave**:
- **Erlang Shell**: Usa `eshell` para probar código rápidamente.
- **Inmutabilidad**: No forces el estilo imperativo (olvida los bucles `for`).
- **Recursos**:
  - [Erlang Documentation](https://www.erlang.org/doc/)
  - Ejercicios en [Exercism (Erlang Track)](https://exercism.org/tracks/erlang).

