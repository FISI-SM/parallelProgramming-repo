-module(c_lista).
-export([sum_list/1]).

sum_list(List) ->
    lists:foldl(fun(X, Acc) -> X + Acc end, 0, List).