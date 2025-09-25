-module(g_secuencia).
-export([lista/1]).

lista(N) ->
    lists:seq(1, N).