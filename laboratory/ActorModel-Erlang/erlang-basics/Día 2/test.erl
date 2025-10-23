-module(test).
-export([test_get_age/0, test_factorial_funct/0, test_separator_cons_funct/0, test_sum/0]).

% Primera parte
test_get_age() -> 
    Usuario = funciones:crear_usuario("Yan", 22),
    Edad = funciones:extraer_edad(Usuario),
    {Usuario, Edad}.
    % {{usuario, "Yan", 22}, 22}

% Segunda parte
test_factorial_funct() ->
    Factorial1 = funciones:factorial(6),
    Factorial2 = funciones:factorial(8),
    Factorial3 = funciones:factorial(0),
    {Factorial1, Factorial2, Factorial3}.
    % {720,40320,1}

test_separator_cons_funct() ->
    funciones:separador_cons([10, 9, 8, 7, 6, 5, 4, 3, 2, 1]).

test_sum() -> 
    funciones:suma([10, 9, 8, 7, 6, 5, 4, 3, 2, 1]).


% Parte opcional

% -module(user_handler).
% -export([crear_usuario/3, manejar_respuesta/1, procesar_usuario/3]).
% 
% %% Crea el usuario y retorna la tupla con el resultado.
% crear_usuario(Nombre, Edad, Hobbies) when is_list(Hobbies) ->
%     %% En un escenario real se podrían hacer validaciones adicionales,
%     %% y si algo falla se retornaría {error, "alguna razón"}.
%     {ok, {usuario, Nombre, Edad, Hobbies}}.
% 
% %% Maneja la respuesta, imprimiendo en pantalla un mensaje de éxito o error.
% manejar_respuesta({ok, Data}) ->
%     io:format("Éxito: ~p~n", [Data]);
% manejar_respuesta({error, Msg}) ->
%     io:format("Error: ~s~n", [Msg]).
% 
% %% Función que integra ambas operaciones: crea el usuario y maneja la respuesta.
% procesar_usuario(Nombre, Edad, Hobbies) ->
%     %% Llamamos a crear_usuario/3 para obtener una respuesta.
%     Respuesta = crear_usuario(Nombre, Edad, Hobbies),
%     %% Pasamos esa respuesta a manejar_respuesta/1.
%     manejar_respuesta(Respuesta).
