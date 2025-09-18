¡Vamos al **Día 3: Funciones y Módulos**! Este día es crucial para organizar tu código como un verdadero desarrollador Erlang. Aquí tienes el cronograma detallado, con enfoque en lo práctico y esencial:

---

### **Cronograma del Día 3: Funciones y Módulos**
**Objetivo Principal**:  
Aprender a definir funciones, crear módulos reutilizables y usar herramientas básicas de compilación.

---

### **1. Mañana: Fundamentos (2-3 horas)**

### 1. Funciones Anónimas (fun)

**Concepto y sintaxis básica:**  
Las funciones anónimas (o *lambdas*) en Erlang son bloques de código que pueden definirse sin necesidad de un nombre explícito. Esto significa que se pueden asignar a variables, pasar como argumentos a otras funciones o incluso retornarlas. La sintaxis es muy directa. Por ejemplo:

```erlang
Suma = fun(A, B) -> A + B end.
Resultado = Suma(3, 5).  % Resultado tendrá el valor 8.
```

### **Características importantes:**  

#### **1. Primeras Ciudadanas**
En Erlang, las funciones son **valores de primera clase**, lo que significa que tienen el mismo peso que los datos tradicionales (como números, cadenas, etc.). Esto te permite:
- **Asignarlas a variables:** Puedes definir una función anónima y asignarla a una variable para reutilizarla, como hiciste con `Suma`:
  ```erlang
  Suma = fun(A, B) -> A + B end.
  Suma(3, 5).  % Resultado: 8
  ```
- **Pasarlas como argumentos:** Puedes enviarlas como parámetros a otras funciones. Por ejemplo, la función `lists:map/2` aplica una función a cada elemento de una lista:
  ```erlang
  Doblar = fun(X) -> X * 2 end.
  lists:map(Doblar, [1, 2, 3, 4]).  % Resultado: [2, 4, 6, 8]
  ```
- **Retornarlas desde funciones:** Es posible crear funciones dinámicamente y retornarlas desde otras funciones. Esto fomenta un estilo de programación muy modular y flexible, ideal para sistemas concurrentes.

Esto permite que tu código sea más **declarativo**, reutilizable y fácil de mantener. En lugar de escribir varias funciones específicas, puedes crear funciones genéricas y adaptarlas según necesites.

#### **2. Closures y captura del entorno**
Un *closure* se refiere a una función que puede **recordar el entorno en el que fue creada**, incluso si se utiliza fuera de ese entorno. Esto significa que las funciones anónimas pueden capturar y almacenar variables definidas en su contexto.

Ejemplo práctico:
```erlang
GenerarMultiplicador = fun(Factor) ->
    fun(X) -> X * Factor end
end.

MultiplicarPor3 = GenerarMultiplicador(3).
MultiplicarPor3(5).  % Resultado: 15
```
- Aquí, la variable `Factor` es parte del entorno donde se definió la función anónima interna, y esta “cierra” sobre su valor, reteniéndolo aunque se use después.

Esto es útil para crear funciones personalizadas y especializadas basadas en un contexto específico. Por ejemplo, puedes generar funciones con configuraciones dinámicas en tiempo de ejecución.

#### **3. Utilidad en operaciones sobre colecciones**
Las funciones anónimas son ideales para **trabajar con listas y otras estructuras de datos** de manera compacta. En lugar de definir una función nombrada, puedes pasar una anónima directamente. Esto resulta particularmente útil con funciones de la biblioteca estándar de Erlang como:
- **`lists:map/2`:** Aplica una función a cada elemento de una lista.
  ```erlang
  lists:map(fun(X) -> X * X end, [1, 2, 3, 4]).  % [1, 4, 9, 16]
  ```
- **`lists:filter/2`:** Selecciona elementos que cumplen una condición.
  ```erlang
  lists:filter(fun(X) -> X rem 2 == 0 end, [1, 2, 3, 4]).  % [2, 4]
  ```
- **Transformaciones y reducciones:** Puedes combinar operaciones como mapear y reducir listas para tareas complejas sin necesidad de definir múltiples funciones.

**Ventajas clave:**
- Simplificas el código eliminando la necesidad de crear funciones adicionales.
- Mantienes el enfoque en **qué** deseas hacer, en lugar de en **cómo** implementarlo.


Estas características hacen que las funciones anónimas sean una herramienta crucial en Erlang. Te ofrecen la posibilidad de escribir código **modular, expresivo y reutilizable**, lo que encaja perfectamente en el paradigma funcional del lenguaje.

Además, la capacidad de componer funciones y pasarlas como argumentos fomenta un estilo funcional muy declarativo, lo cual es una de las razones por las que Erlang es ideal para tareas concurrentes y distribuidas. Esta abstracción y modularidad permiten concentrarte en “qué” se quiere hacer, sin preocuparte por los detalles imperativos del control de flujo.

---

### 2. Módulos Básicos

**Estructura y composición:**  
En Erlang, el código se organiza en módulos, donde cada módulo es un archivo que contiene un conjunto de funciones relacionadas. Este enfoque modular te permite encapsular funcionalidades y estructurar mejor tus programas. Veamos un ejemplo básico que define un módulo para operaciones aritméticas:

```erlang
-module(aritmetica).    % Nota: el nombre del módulo debe coincidir con el nombre del archivo: aritmetica.erl
-export([suma/2]).      % Se hace público la función suma con aridad 2

suma(A, B) ->
    A + B.
```

**Pasos importantes en el desarrollo con módulos:**  
- **Declaración del módulo:** Se utiliza la directiva `-module(Nombre).` para indicar el nombre del módulo. Este nombre debe coincidir con el nombre del archivo fuente (ejemplo: `aritmetica.erl` para `aritmetica`).  
- **Exportación de funciones:** La directiva `-export([Función/Aridad]).` determina qué funciones estarán disponibles para ser usadas por otros módulos o desde shell. Esto permite ocultar detalles internos y exponer solo la interfaz pública del módulo.  
- **Compilación y ejecución:**  
  - Compila el módulo con:  
    ```bash
    erlc aritmetica.erl
    ```  
    Esto genera el archivo `aritmetica.beam`.  
  - Ejecuta la función exportada desde la terminal con:  
    ```bash
    erl -noshell -s aritmetica suma 3 5 -s init stop
    ```  
    Esto iniciará la máquina virtual de Erlang, ejecutará la función `suma(3,5)` y luego se detendrá.

El concepto de módulos es esencial no solo para organizar el código sino también para manejar de forma sólida el aislamiento de procesos y fallos en sistemas concurrentes, ya que cada módulo puede ser desarrollado, probado y mantenido de forma independiente.

---

### 3. Ejercicio práctico: Módulo para el área de un círculo

Para poner en práctica lo aprendido, puedes crear el módulo `geo.erl` con la siguiente estructura. El objetivo es definir la función `area_circulo/1`, que reciba el radio y calcule el área usando la fórmula π * r². Un ejemplo sería:

```erlang
-module(geo).
-export([area_circulo/1]).

area_circulo(Radio) when is_number(Radio), Radio >= 0 ->
    math:pi() * Radio * Radio;
area_circulo(_Radio) ->
    error(invalid_radius).
```

**Puntos a considerar en este ejercicio:**  
- **Validación:** Se añade una cláusula adicional para manejar casos donde el radio no sea un número o sea negativo, retornando un error.  
- **Uso de librerías estándar:** La función `math:pi()` te proporciona el valor de π, lo que es una manera limpia y eficiente de acceder a constantes matemáticas de la librería estándar.

Compílalo y ejecútalo de forma similar al ejemplo anterior. Esto te ayudará a familiarizarte tanto con la estructura de módulos como con el uso de funciones predefinidas en Erlang.

---

### Más allá de lo aprendido

Una vez que te sientas cómodo con funciones anónimas y la estructura modular, te recomiendo explorar otros conceptos esenciales en Erlang, como:

- **Concurrencia y comunicación de procesos:** Aprende a crear y gestionar procesos con `spawn` y a comunicarte mediante `send` y `receive`. Esto te permitirá diseñar sistemas altamente concurrentes y tolerantes a fallos.
- **Patrón de supervisión y OTP:** La plataforma OTP es fundamental para crear aplicaciones robustas en Erlang. Investiga sobre comportamientos genéricos como `gen_server` y árboles de supervisión para comprender cómo manejar la supervisión y recuperación de procesos.
- **Manejo de errores y tolerancia a fallos:** Erlang se basa en la filosofía de “fail fast” y en la supervisión de procesos. Explorar estos temas te abrirá la puerta a diseñar sistemas resilientes de manera natural.

Profundizar en estos temas te dará una perspectiva completa de por qué Erlang es tan utilizado en telecomunicaciones, mensajería y otros campos donde la escalabilidad y la tolerancia a fallos son cruciales. ¿Te gustaría profundizar en alguno de estos aspectos o explorar cómo aplicar estos fundamentos en proyectos reales?

---

### **2. Tarde: Exportación y Organización (3-4 horas)**

### A. Exportación Selectiva

La **exportación selectiva** en Erlang es la técnica que te permite controlar qué funciones dentro de un módulo estarán disponibles para otros módulos. Esto se define mediante la directiva `-export([...])` al comienzo del archivo y sirve para establecer una **interfaz pública**, ocultando las implementaciones internas que no deseas exponer.

### Ejemplo y explicación

Considera el siguiente módulo:

```erlang
-module(utils).
-export([publica/0]). % Solo la función publica/0 es accesible desde fuera

publica() ->
    privada().

privada() ->
    "Secreto".
```

- **Interfaz Pública vs. Privada:**  
  La directiva `-export([publica/0])` indica que únicamente la función `publica/0` se puede llamar desde otros módulos. La función `privada/0`, al no estar exportada, es interna y solamente puede ser utilizada dentro del módulo `utils`.  
- **Beneficios:**  
  - **Encapsulamiento:** Permite ocultar detalles de implementación y exponer solo lo necesario, facilitando cambios internos sin afectar a otros módulos.  
  - **Seguridad y Mantenimiento:** Evita que otros desarrolladores o partes de la aplicación hagan uso indebido de funciones internas que podrían no estar preparadas para ser llamadas directamente, lo que disminuye posibles errores de ejecución.  

Un error común es intentar llamar a `utils:privada()` desde otro módulo o desde el intérprete interactivo de Erlang, lo cual generará un error de compilación o en tiempo de ejecución, ya que la función no es parte de la interfaz pública del módulo.

---

### B. Funciones con Múltiples Cláusulas

En Erlang, puedes definir una función con **varias cláusulas** utilizando *pattern matching*, lo que te permite describir diferentes comportamientos según el valor de los parámetros. Este mecanismo es muy poderoso, ya que:

- **Clarifica el flujo de datos:** Cada cláusula define un caso particular, lo que hace el código más legible y evita la necesidad de múltiples estructuras condicionales.
- **Aprovecha los guards:** Puedes definir condiciones adicionales (guards) para refinar cuándo debe aplicarse una determinada cláusula.

### Ejemplo del factorial

```erlang
-module(factorial).
-export([calcular/1]).

calcular(0) ->
    1;
calcular(N) when N > 0 ->
    N * calcular(N - 1).
```

Aquí se observa:

- **Cláusula Base:**  
  Cuando la función recibe `0`, retorna `1`. Esta es la condición de terminación en una función recursiva.
- **Cláusula Recursiva:**  
  Para cualquier `N` mayor que 0, se utiliza una guard `when N > 0` y se define la recursión.  
- **Importancia del Orden:**  
  El orden de las cláusulas es fundamental, ya que Erlang evalúa cada cláusula secuencialmente y utiliza la primera que haga match. Si se invirtieran, o se incluyera una cláusula demasiado general al inicio, los casos específicos podrían quedar inalcanzables.

El uso de múltiples cláusulas no solo mejora la legibilidad, sino que también permite definir comportamientos distintos de forma muy intuitiva, lo cual es especialmente útil en funciones recursivas o cuando se trabaja con estructuras de datos complejas.

---

### Ejercicio práctico: Extender `geo.erl` con `area/2`

Como ejercicio, extiende el módulo `geo.erl` para manejar el cálculo del área de dos tipos de figuras: círculos y rectángulos. Se pide definir una función `area/2` que entienda dos casos:

- **Para círculos:** Se llamará como `area(circulo, Radio)`.
- **Para rectángulos:** Se llamará como `area(rectangulo, {Ancho, Alto})`.

### Ejemplo de implementación

```erlang
-module(geo).
-export([area_circulo/1, area/2]).

%% Cálculo del área de un círculo
area_circulo(Radio) when is_number(Radio), Radio >= 0 ->
    math:pi() * Radio * Radio;
area_circulo(_) ->
    error(invalid_radius).

%% Cálculo del área para diferentes figuras
area(circulo, Radio) when is_number(Radio), Radio >= 0 ->
    area_circulo(Radio);
area(rectangulo, {Ancho, Alto})
    when is_number(Ancho), is_number(Alto),
         Ancho >= 0, Alto >= 0 ->
    Ancho * Alto;
%% Manejo de casos no soportados
area(_, _) ->
    error(forma_no_soportada).
```

### Ejemplo de prueba

```erlang
1> geo:area(circulo, 5).
78.53981633974483
2> geo:area(rectangulo,{2,4}).
8
```

### Detalles a destacar

- **Patrón en la Firma:**  
  La función `area/2` diferencia los casos utilizando el primer argumento. Cuando es el átomo `circulo`, se delega en la función `area_circulo/1`; cuando es `rectangulo`, se extraen `Ancho` y `Alto` del patrón `{Ancho, Alto}`.
- **Uso de Guards:**  
  Se validan los parámetros numéricos, asegurando que se puedan calcular correctamente las áreas y evitando errores en tiempo de ejecución.
- **Cláusula de Error por Defecto:**  
  La última cláusula captura cualquier llamada a `area/2` que no cumpla los patrones anteriores y retorna un error indicando que la forma no es soportada, lo que es importante para la robustez del módulo.
- **Modularidad y Encapsulación:**  
  La función `area_circulo/1` se mantiene separada pero es utilizada por `area/2`, permitiendo que cada responsabilidad se maneje en una función específica y se mantenga el código limpio y organizado.

---



Estos conceptos —la exportación selectiva y el uso de múltiples cláusulas con pattern matching— son pilares en la construcción de aplicaciones en Erlang. Permiten:
- **Organizar el código en módulos** con interfaces públicas bien definidas.
- **Escribir funciones claras y concisas** que se adapten intuitivamente a distintos patrones de entrada.
- **Crear aplicaciones robustas y escalables**, facilitando el mantenimiento y la extensión de funcionalidades con el tiempo.



---

### **3. Noche: Proyecto Integrador (1-2 horas)**
**Descripción**:  
Crea un módulo `calculadora` que:  
1. Exporte funciones para `suma`, `resta`, `multiplicacion` y `division`.  
2. Maneje errores (ej: división por cero con `{error, "División por cero"}`).  
3. Use funciones privadas para validaciones.

**Código de Ejemplo**:
```erlang
-module(calculadora).
-export([dividir/2]).

dividir(_, 0) -> {error, "División por cero"};
dividir(A, B) -> A / B.

% Función privada (no exportada)
validar_entrada(X) when is_number(X) -> true;
validar_entrada(_) -> false.
```

**Cómo probarlo**:
```erlang
% abrir consola de Erlang (erl) luego de compilar los módulos
1> calculadora:sumatoria(5).
2> calculadora:sumar(5, 0).
3> calculadora:restar(5, 0).
4> calculadora:multiplicar(5, 0).
5> calculadora:dividir(10, 2).  % 5.0
6> calculadora:dividir(5, 0).   % {error, "División por cero"}
7> calculadora:potenciar(5, 2). % 5 elevado a la potencia de 2
```

---

### **Errores Comunes (¡Evítalos!)**
1. **Olvidar exportar funciones**:
   ```erlang
   -module(test).
   hola() -> "Hola". % No exportada: test:hola() dará error.
   ```
2. **Módulo y archivo con nombres distintos**:
   - Si el módulo es `-module(mis_utils)`, el archivo **debe** ser `mis_utils.erl`.

---

### **Checklist del Día 3**
✅ Definir funciones anónimas con `fun`.  
✅ Crear módulos con `-module` y `-export`.  
✅ Compilar y ejecutar módulos desde el shell.  
✅ Usar pattern matching en funciones (múltiples cláusulas).  
✅ Diferenciar entre funciones públicas y privadas.  

---

### **Recursos Clave**
- **Documentación**: [Erlang Module Syntax](https://www.erlang.org/doc/reference_manual/modules.html).  
- **Libro**: *Learn You Some Erlang*, capítulos 4 y 5.  
- **Práctica**: Ejercicios en [Exercism (Erlang Track)](https://exercism.org/tracks/erlang).

---

**Próximo Paso**: Al terminar, estarás listo para el **Día 4: Recursión y Tail Recursion**, donde aprenderás a reemplazar bucles (¡que no existen en Erlang!) con recursión eficiente.  