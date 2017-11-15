% #7

number_of_symbols(F, N):-
    see(F),
    num_of_symbols(N),
    seen.


num_of_symbols(N):-
    get0(X),
    ((X @> 32, X @< 127) ->
    num_of_symbols(N1),
    N is N1+1;
    ((X == -1) ->
    N is 0;
    num_of_symbols(N))).

