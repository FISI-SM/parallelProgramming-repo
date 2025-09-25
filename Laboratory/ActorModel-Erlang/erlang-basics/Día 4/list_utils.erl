-module(list_utils).
-export([map/2, filter/2]).

% ------------------------------------------------------------------------------------------ 
%  Función map/2: Aplica una función a cada elemento de una lista usando tail recursion.
% 
%  Se utiliza un acumulador que va recogiendo los resultados de aplicar la función
%  a cada elemento. Al terminar, se invierte el acumulador para mantener el orden original.
% ------------------------------------------------------------------------------------------
map(Fun, List) ->
    map(Fun, List, []).

map(_Fun, [], Acc) ->
    lists:reverse(Acc);
map(Fun, [H | T], Acc) ->
    map(Fun, T, [Fun(H) | Acc]).


% 1> Double = fun(X) -> X * 2 end.
% 2> list_utils:map(Double, [1, 2, 3]).

% -----------------------------------------------------------------------------------------
%  Función filter/2: Filtra los elementos de una lista según la condición de Pred.
% 
%  Se utiliza un acumulador para ir guardando los elementos que cumplen la condición.
%  Al finalizar, se invierte el acumulador para recuperar el mismo orden en la lista.
% -----------------------------------------------------------------------------------------
filter(Pred, List) ->
    filter(Pred, List, []).

filter(_Pred, [], Acc) ->
    lists:reverse(Acc);
filter(Pred, [H | T], Acc) ->
    NewAcc = case Pred(H) of
        true -> [H | Acc];
        false -> Acc
    end,
    filter(Pred, T, NewAcc).

% 1> IsEven = fun(X) -> X rem 2 =:= 0 end.
% 2> list_utils:filter(IsEven, [1, 2, 3, 4, 5, 6]).
