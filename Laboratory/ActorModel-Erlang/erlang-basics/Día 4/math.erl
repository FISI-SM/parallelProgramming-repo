-module(math).
-export([sumatoria/1, factorial/1]).

sumatoria(List) -> sumatoria(List, 0). % inicializa la función con un acumulador igual a 0. 

sumatoria([], Acc) -> Acc;
sumatoria([ Head | Tail ], Acc) -> sumatoria(Tail, Head + Acc). % se inicializa la función de sumatoria con la nueva lista
                                                                % y se acumula en la variable Acc el valor totalde cada elemento 
                                                                % que se saca de la lista en cada iteración.


% Factorial 
factorial(N) -> factorial(N, 1).

factorial(0, Acc) -> Acc;
factorial(N, Acc) -> factorial(N - 1, N * Acc). 


% Ambas funciones sumatoria/2 y factorial/2 son privadas. Están siendo accedidas desde sus funciones públicas sumatoria/1 y factorial/1 


