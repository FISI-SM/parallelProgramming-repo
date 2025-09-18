-module(test).
-export([test_users_funct/0]).

test_users_funct() ->
    Usuario = home:crear_usuario("Yan", 22, [programar]),
    UsuarioActualizado = home:actualizar_edad(Usuario, 23),
    TieneHobby = home:tiene_hobby(UsuarioActualizado, programar),
    {UsuarioActualizado, TieneHobby}.
