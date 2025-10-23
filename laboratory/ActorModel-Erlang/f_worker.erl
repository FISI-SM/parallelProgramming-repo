-module(f_worker).
-export([start/2, task/2]).

start(Name, Msg) ->
    spawn(f_worker, task, [Name, Msg]).

task(Name, Msg) ->
    io:format("~p says: ~p~n", [Name, Msg]).