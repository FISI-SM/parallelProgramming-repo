# Ejemplos Básicos de Erlang

Este repositorio contiene ejemplos simples y separados para entender conceptos fundamentales de Erlang, como recursión, actores, paso de mensajes, listas y funciones de orden superior. Estos conceptos son claves para entender códigos más complejos como el método del trapecio paralelizado.

---

## 📘 1. Recursión simple

**Archivo:** `recursion.erl`  
Calcula la suma de los números de 1 a N usando recursión.

```erlang
sum(0) -> 0;
sum(N) when N > 0 -> N + sum(N - 1).
```

**Ejemplo en el shell:**

```erlang
1> c(recursion).
2> recursion:sum(5).
15
```

---

## 📘 2. Uso de listas y `foldl`

**Archivo:** `lista.erl`  
Suma los elementos de una lista usando `lists:foldl`.

```erlang
sum_list(List) ->
    lists:foldl(fun(X, Acc) -> X + Acc end, 0, List).
```

**Ejemplo:**

```erlang
1> lista:sum_list([1,2,3,4]).
10
```

---

## 📘 3. Creación de actores (procesos)

**Archivo:** `actor.erl`  
Crea un proceso que responde a mensajes.

```erlang
start() ->
    spawn(actor, loop, []).
```

**Ejemplo:**

```erlang
1> Pid = actor:start().
2> Pid ! {hello, self()}.
3> Pid ! stop.
```

---

## 📘 4. Paso de mensajes con respuesta

**Archivo:** `pingpong.erl`  
Simula un ping-pong entre procesos.

```erlang
pong() ->
    receive
        {ping, From} -> From ! pong
    end.
```

**Ejemplo:**

```erlang
1> pingpong:ping().
Received pong!
```

---

## 📘 5. Uso de `spawn` con argumentos

**Archivo:** `worker.erl`  
Crea un proceso que imprime un mensaje.

```erlang
start(Name, Msg) ->
    spawn(worker, task, [Name, Msg]).
```

**Ejemplo:**

```erlang
1> worker:start("Herminio", "Hola mundo").
"Herminio" says: "Hola mundo"
```

---

## 📘 6. Manejo de secuencias

**Archivo:** `secuencia.erl`  
Genera una lista con números consecutivos.

```erlang
lista(N) ->
    lists:seq(1, N).
```

**Ejemplo:**

```erlang
1> secuencia:lista(5).
[1,2,3,4,5]
```

---

## ✅ Tabla de referencia cruzada

| Concepto Erlang        | Archivo           | En código real de `trap.erl`                  |
|------------------------|-------------------|-----------------------------------------------|
| Recursión              | `recursion.erl`   | `trap2/6`                                     |
| `foldl` y listas       | `lista.erl`       | `trapFold/4`                                  |
| Actores (procesos)     | `actor.erl`       | `spawn(trap, go, [...])`                      |
| Paso de mensajes       | `pingpong.erl`    | `Src ! [Rank, LocalInt]`, `receive [...]`     |
| `spawn` con argumentos | `worker.erl`      | `spawn(trap, go, [self(), Rank, A, N, H, P])` |
| Secuencias             | `secuencia.erl`   | `lists:seq(1, TrapCount - 1)`                 |

---


# Aproximación Trapezoidal en Erlang

## Implementación

Para compilar e ejecutar:

```bash
$ erlc trap.erl
$ erl -noshell -s trap main A B N P
```

Donde `A` y `B` son los valores inicial y final para `f(x)`,  
`N` es el número de trapézios y `P` el número de procesos.
