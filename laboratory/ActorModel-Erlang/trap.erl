%% Emilio Francesquini <e.francesquini@ufabc.edu.br>
%% 2019-03-21

-module(trap).
-export([main/1, go/6, trap/4, trapFold/4]).

-mode(native).

f(X) ->
    X * X.

%% ¡Solución artificial! Es mejor usar un fold. Sin embargo, la solución de abajo
%% es muy parecida a la hecha en MPI (ver la solución del libro de PP)
trap(Left, Right, TrapCount, BaseLen) ->
    BaseLen * trap2(
                Left, Right, TrapCount, BaseLen,
                (f(Left) + f(Right)) / 2.0, 1).

trap2 (Left, Right, TrapCount, BaseLen, Estimate, I) when I < TrapCount ->
    Estimate2 = Estimate + f(Left + I * BaseLen),
    trap2 (Left, Right, TrapCount, BaseLen, Estimate2, I + 1);
trap2 (_, _, _, _, Estimate, _) ->
    Estimate.

trapFold (Left, Right, TrapCount, BaseLen) ->
    F = fun (I, Acc) -> Acc + f(Left + I * BaseLen) end,
    L = lists:seq(1, TrapCount - 1),
    PartialInt = lists:foldl(F, (f(Left) + f(Right)) / 2.0, L),
    BaseLen * PartialInt.

go (Src, Rank, A, N, H, P) ->
    LocalN = N div P,
    LocalA = A + Rank * LocalN * H,
    LocalB = LocalA + LocalN * H,
    %% Descomente la línea de abajo para usar la otra implementación
    %% LocalInt = trap (LocalA, LocalB, LocalN, H),
    LocalInt = trapFold (LocalA, LocalB, LocalN, H),
    Src ! [Rank, LocalInt].

getResults (_From) ->
    %% Se puede esperar en orden para garantizar resultados siempre iguales
    %% receive [From, Val] ->
    receive [_, Val] -> %% O en cualquier orden
            Val
    end.

main([A, B, N, P]) ->
    A2 = list_to_float(atom_to_list(A)),
    B2 = list_to_float(atom_to_list(B)),
    N2 = list_to_integer(atom_to_list(N)),
    P2 = list_to_integer(atom_to_list(P)),
    H = (B2 - A2) / N2,
    Ranks = lists:seq(0, P2 - 1),

    [spawn(trap, go, [self(), Rank, A2, N2, H, P2]) || Rank <- Ranks],
    Int = lists:sum([getResults(Rank) || Rank <- Ranks]),

    io:fwrite(io_lib:format("~.16f\n", [Int])),
    init:stop().
