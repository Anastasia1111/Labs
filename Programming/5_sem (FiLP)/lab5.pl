odd():-
    writeln('print X:'),
    read(X),nl,
    writeln('print Y:'),
    read(Y),nl,
    odd(X,Y).
odd(X,Y):-
    (Y >= X),
    (((Y mod 2) =:= 1) -> write(Y); write(' ')),
    Z is (Y - 1),
    odd(X, Z).
sum():-
    writeln('print X:'),
    read(X),nl,
    writeln('print Y:'),
    read(Y),nl,
    Z is 0,
    sum(X,Y,Z).
sum(X,Y,Z):-
    V is (Z + Y),
    W is (Y - 1),
    ((W >= X) -> true; write(V), !, fail),
    sum(X, W, V).
min():-
    writeln('print X:'),
    read(X),nl,
    Min = 10,
    min(X, Min).
min(X, M):-
    (X =\= 0 ->
    Y is (X mod 10),
    Xnew is (X//10),
    (Y < M -> min(Xnew, Y); min(Xnew, M));
    write(M)).
min(0,10) :- write('0').
fib():-
    repeat,
    writeln('print X'),
    read(X),nl,
    (X < 0 -> fail; write(fib(X))).
fib(X)=fib((X-1)) + fib((X-2)).
fib(0)=1:-!.
fib(1)=1:-!.
