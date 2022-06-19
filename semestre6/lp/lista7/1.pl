parent(kim,holly).
parent(margaret,kim).
parent(margaret,kent).
parent(kent, jonas).
parent(esther,margaret).
parent(herbert,margaret).
parent(herbert,jean).
greatGrandParent(GGP,GGC) :- parent(GGP,GP), parent(GP,P), parent(P,GGC).
sibling(X,Y) :- parent(P,X), parent(P, Y), not(X=Y).

firstCousin(X,Y) :- parent(PX, X), parent(PY, Y), 
sibling(PX, PY), not(X=Y), not(sibling(X,Y)).

descendant(X,Y) :- parent(Y, X).
descendant(X,Y) :- parent(Y, Z), descendant(X,Z).
