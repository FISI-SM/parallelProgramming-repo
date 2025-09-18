-module(d_actor).
-export([start/0, loop/0]).

start() ->
    spawn(d_actor, loop, []).

loop() ->
    receive
        {hello, From} ->
            io:format("Hello from ~p!~n", [From]),
            loop();
        stop ->
            io:format("Stopping...~n")
    end.