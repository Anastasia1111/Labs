% Определение родителей:
parent(X, Y):-
    X = mary,Y = bob;
    X = mary,Y = ann;
    X = bob,Y = liz;
    X = bob,Y = paul;
    X = bob,Y = sam;
    X = paul,Y = pat;
    X = jonh,Y = bob.
% Мужчины и женщины:
man(john).
man(bob).
man(sam).
man(paul).
man(pat).
woman(mary).
woman(liz).
woman(ann).
% Родственники:
diff(X,Y):- X=Y,!, fail; true.
father(X,Y):-parent(X,Y),man(X).
mother(X,Y):-parent(X,Y),woman(X).
brother(X,Y):-man(X),parent(Z,X),parent(Z,Y), diff(X,Y).
sister(X,Y):-parent(Z,X),parent(Z,Y), woman(X), diff(X,Y).
grandchilds(X, Y):-parent(Y,Z),parent(Z,X).
aunt(X,Y):-parent(Z,Y),sister(X, Z).
has_2_childs(X):-parent(X,Y),parent(X,Z),diff(Y,Z).
successor(X):-parent(X,Y),man(Y),man(X).
