-module(a_hello).
-export([start/0]).

start() ->
    io:format("Hello, World!~n").
