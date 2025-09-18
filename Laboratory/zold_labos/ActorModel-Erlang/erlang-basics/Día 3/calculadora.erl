% Proyecto integrador
-module(calculadora).
-export([sumatoria/1, sumar/2, restar/2, multiplicar/2, potenciar/2, division/2, sumar_con_validaciones/2]).

sumar(N, N2) -> N + N2.

% funciones como estas no son óptimas, se debe usar tail recursion
sumatoria(0) -> 0;
sumatoria(N) when N > 0 -> sumar(N, sumatoria(restar(N, 1))). 

restar(N, N2) when is_number(N), is_number(N2) -> N - N2.

multiplicar(N, N2) -> N * N2.

potenciar(_, 0) -> 1;
potenciar(N, N2) when N2 > 0 ->
    multiplicar(N, potenciar(N, restar(N2, 1)));
potenciar(_, N2) when N2 < 0 -> {error, "Exponente negativo no soportado"}.

division(_, 0) -> {error, "División por cero"};
division(N, N2) when N2 > 0 -> N / N2.


% Función privada (no exportada)
validar_entrada(X) when is_number(X) -> true;
validar_entrada(_) -> false.


sumar_con_validaciones(X, Y) -> 
    case validar_entrada(X) and validar_entrada(Y) of
      true -> X + Y;
      false -> {error, "Ingrese valores numéricos"}
    end.


