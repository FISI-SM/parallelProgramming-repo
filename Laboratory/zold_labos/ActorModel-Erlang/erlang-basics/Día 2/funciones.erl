-module(funciones).
-export([crear_usuario/2, extraer_edad/1, factorial/1, separador_cons/1, suma/1]).

% Primera parte
crear_usuario(Nombre, Edad) -> 
    {usuario, Nombre, Edad}.

extraer_edad({usuario, _Nombre, Edad}) -> 
    Edad.

% Segunda parte
factorial(0)-> 1;
factorial(N)-> N * factorial(N - 1). % Pequeño ejemplo de recursividad. Se verá más acerca de este tema más adelante

separador_cons([]) ->
    io:format("La cola está vacía.~n"),
    ok;
separador_cons([Elemento | Resto]) ->
    io:format("Procesando elemento: ~p~n", [Elemento]),
    io:format("Lista restante: ~p~n~n", [Resto]),
    separador_cons(Resto).

% Suma los elementos de una lista
suma([]) ->0;
suma([Cabeza | Cola]) ->
    Cabeza + suma(Cola).
