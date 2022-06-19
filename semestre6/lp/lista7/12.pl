ordered([]).
ordered([_]).
ordered([X|Tail]) :- Tail = [Y|_], X < Y, ordered(Tail).
