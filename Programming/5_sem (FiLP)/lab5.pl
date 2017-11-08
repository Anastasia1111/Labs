odd():-
    writeln('print X:'),
    read(X),
    writeln('print Y:'),
    read(Y),
    odd(X,Y).
odd(X, Y):-
    (Y >= X ->
    (((Y mod 2) =:= 1) -> write(Y); write(' ')),
    Z is (Y - 1),
    odd(X, Z); true).
sum():-
    writeln('print X:'),
    read(X),
    writeln('print Y:'),
    read(Y),
    Z is 0,
    sum(X, Y, Z).
sum(X, Y, Z):-
    V is (Z + Y),
    W is (Y - 1),
    ((W >= X) -> sum(X, W, V); write(V), !, true).
min():-
    writeln('print X:'),
    read(X),nl,
    Min is 10,
    min(X, Min).
min(0, 10):- write('0').
min(X, M):-
    (X =\= 0 ->
     Y is (X mod 10),
     Xnew is (X//10),
    (Y < M -> min(Xnew, Y); min(Xnew, M));
     write(M)).
fib():-
    repeat,
    writeln('print X'),
    read(X),
    fib(X, Y),
    writeln(Y),
    X < 0,
    !.
fib(X, Y):-
    (X =:= 0 -> Y is 1;
    (X =:= 1 -> Y is 1;
    (X < 0 -> Y = 'end';
     X1 is X - 1,
     X2 is X - 2,
     fib(X1, Y1),
     fib(X2, Y2),
     Y is Y1 + Y2))).
