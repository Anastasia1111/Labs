from_1_to_3():-
    write("List:"), nl,
    read(S),
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
    append([Hs], T1d, T1).

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
    numbers_of_max(X, Y, -1, Z),
    write(Z).

numbers_of_max([],_,_,[]):-!.
numbers_of_max([H|T], Max, Count, Tr):-
    Count1 is Count + 1,
    ((H =:= Max) ->
    numbers_of_max(T, Max, Count1, Tr1),
    append([Count1], Tr1, Tr);
    numbers_of_max(T, Max, Count1, Tr)).

freq():-
    write("Enter the list"), nl,
    read(X),
    msort(X, Y),
    freq(Y, Z),
    write(Z).

freq([], []).
freq([H|T], Res):-
    freq([H|T], _, Res, _).

freq([], 0, [], 0).
freq([H], 1, [H], 1).
freq([H, H1|T], Count, Res, Max):-
    freq([H1|T], Count1, Res1, Max1),
    Count2 is Count1 + 1,
    ((H =:= H1)->
         (Count = Count2,
         ((Count2 > Max1)->
          Max = Count2,
          Res = [H];
          (Max = Max1,
          ((Count2 =:= Max1)->
              append([H], Res1, Res);
          Res = Res1
          ))));
    Count = 1,
    Max = Max1,
    Res = Res1).

freqinv([H, H1|T], Count, Res, Max):-
    freqinv([H1|T], Count1, Res1, Max1),
    Count2 is Count1 + 1,
    ((H \== H1)->
         (Count = Count2,
         ((Count1 < Max1)->
          Max = Count1,
          Res = [H1];
          (Max = Max1,
          ((Count2 =:= Max1)->
              append([H1], Res1, Res);
          Res = Res1
          ))));
    Count = Count2,
    Max = Max1,
    Res = Res1).
