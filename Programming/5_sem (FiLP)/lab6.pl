from_1_to_3(S):-
    write("First number:"), nl,
    read(N1),
    write("Second number:"), nl,
    read(N2),
    from_1_to_3(S, T1, T2, T3, N1, N2),
    write(T1),
    write(T2),
    write(T3).



from_1_to_3([], [], [], [], _, _):-!.

from_1_to_3(S, T1, T2, T3, S1, S2):-
    S1 > S2 ->
    !,
    from_1_to_3(S, T1, T2, T3, S2, S1).

from_1_to_3([Hs|Ts], T1, T2, T3, S1, S2):-
    (Hs > S2)->
    from_1_to_3(Ts, T1, T2, T3d, S1, S2),
    append([Hs], T3d, T3);
    (Hs >= S1)->
    from_1_to_3(Ts, T1, T2d, T3, S1, S2),
    append([Hs], T2d, T2);
    (Hs < S1)->
    from_1_to_3(Ts, T1d, T2, T3, S1, S2),
    append([Hs], T1d, T1);
    from_1_to_3(Ts, T1, T2, T3, S1, S2).

max([X], X).
max([X|T], X):-
    max(T, M),
    X > M,
    !.
max([_|T], X):-
    max(T, X).

numbers_of_max():-
    write("Enter the list:"), nl,
    read(X),
    max(X, Y),
    numbers_of_max(X, Y, 0, Z),
    write(Z).

numbers_of_max([],_,_,[]):-!.
numbers_of_max([H|T], Max, Count, Tr):-
    (H =:= Max) ->
    Count1 is Count + 1,
    numbers_of_max(T, Max, Count1, Tr1),
    append([Count1], Tr1, Tr);
    Count1 is Count + 1,
    numbers_of_max(T, Max, Count1, Tr).

freq():-
    write("Enter the list"), nl,
    read(X),
    msort(X, Y),
    freq(Y).

freq([]):- write([]).
freq([H|T]):-
    freq(T, H, 1, [H], 1).

freq([], _, _, A, _):- write(A).
freq([H|T], Prev, Count, A, Max):-
    Count1 is Count+1,
    (H =:= Prev)->
          ((Count1 > Max)->
          freq(T, H, Count1, [H], Count1);
          (Count1 =:= Max)->
              append(A, [H], A1),
              freq(T, H, Count1, A1, Max);
              freq(T, H, Count1, A, Max));
    freq(T, H, 1, A, Max).
