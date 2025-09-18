-module(funciones).
-export([crear_usuario/3, actualizar_edad/2, tiene_hobby/2]).

crear_usuario(Nombre, Edad, Hobbies) -> 
    {usuario, Nombre, Edad, Hobbies}.

actualizar_edad({usuario, Nombre,_, Hobbies}, NuevaEdad) ->
    {usuario, Nombre, NuevaEdad, Hobbies}.

tiene_hobby({usuario, _, _, Hobbies}, HobbyBuscado) -> 
    lists:member(HobbyBuscado, Hobbies).