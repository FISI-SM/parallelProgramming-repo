-module(b_recursion).
-export([sum/1]).

sum(0) -> 0;
sum(N) when N > 0 -> N + sum(N - 1).