parse([],[]).
parse([H|T], L):-
    eater(H, T, Count, L1),
    parse(L1, L2),
    append([[H, Count]], L2, L).
eater(_, [], 1, []):-!.
eater(H, [H1|T], Count, L):-
    eater(H, T, Count1, L1),
    ((H =:= H1) -> Count is Count1 + 1, L = L1;
    Count = Count1, append([H1], L1, L)).

