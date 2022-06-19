containsAll([X], Y) :- member(X,Y).
containsAll([H|T],Y)  :- member(H,Y), containsAll(T,Y).
isEqual(X,Y)        :- containsAll(X,Y), containsAll(Y,X). 
