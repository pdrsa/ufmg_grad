evenSize(X) :- X = [].
oddSize(X)  :- X = [_].
evenSize(X) :- X = [_|T], oddSize(T).
oddSize(X)  :- X = [_|T], evenSize(T).
