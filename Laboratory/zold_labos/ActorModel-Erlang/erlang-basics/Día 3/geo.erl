-module(geo).
-export([area/2]).

%% Cálculo del área de un círculo
area_circulo(Radio) ->  % se puede eliminar el guard ya que se accede a esta función unicamente 
                        % por la función area/2 y ya esta realiza las validaciones
    math:pi() * Radio * Radio.

%% Cálculo del área para diferentes figuras
area(circulo, Radio) when is_number(Radio), Radio >= 0 ->
    area_circulo(Radio);
area(rectangulo, {Ancho, Alto})
    when is_number(Ancho), is_number(Alto), Ancho >= 0, Alto >= 0 ->
        Ancho * Alto;
%% Manejo de casos no soportados
area(_, _) ->
    error(forma_no_soportada).