eat(_, [], []):-!.
eat(H, [H1|T], L):-
    eat(H, T, L1),
    ((H =:= H1) ->  L = L1;
    append([H1], L1, L)).
