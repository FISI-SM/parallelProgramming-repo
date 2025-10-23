-module(funciones).
-export([suma/0, clousure/0, publica/1]).

% funciones anónimas
suma() -> 
    Suma = fun(A, B) -> A + B end,
    Suma(3, 5). 
    
    % o se puede asignar el valor de la función a una variable 
    % Resultado = Suma(3, 5).

clousure() -> 
    GenerarMultiplicador = fun(Factor) ->
        fun(X) -> X * Factor end % generas una función que según su contexto, ejecute la expresión definida
        end,

    MultiplicarPor3 = GenerarMultiplicador(3),
    MultiplicarPor3(5).  % Resultado: 15


% Segunda Parte 
publica(Nombre) -> 
    privada(Nombre).

privada(Nombre) -> 
    io:format("Hola ~p, esto es una función privada a la que puedes acceder solo desde su función pública correspondiente.~n", [Nombre]).