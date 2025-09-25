-module(test).
-export([test_circle_area/0, test_public/0]).

test_circle_area() ->
    Area = geo:area_circulo(4),
    % AreaInvalida = geo:area_circulo(), % ** exception error: undefined function geo:area_circulo/0
                                         %       in function  test:test_circle_area/0 (test.erl, line 6)
    % OtraAreaInvalida = geo:area_circulo("5"), 
    % 1> test:test_circle_area().
    % ** exception error: no function clause matching 
    %                 geo:area_circulo("5") (geo.erl, line 4)
    %  in function  test:test_circle_area/0 (test.erl, line 8)

    OtraAreaValida = geo:area_circulo(0),
    {Area, OtraAreaValida}.

test_public() -> 
    funciones:publica("Yan").
