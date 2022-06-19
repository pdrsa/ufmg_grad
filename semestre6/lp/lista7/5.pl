dupList(X,Y) :- X = [EX], Y = [EX|TY], TY = [EX].
dupList(X,Y) :- X = [EX|TX], Y = [EX|TYA], TYA = [EX|TY], dupList(TX,TY).
