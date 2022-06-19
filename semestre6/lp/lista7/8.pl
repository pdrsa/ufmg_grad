isDifference([X], Y, Z) :- member(X,Y); member(X,Z).
isDifference([H|T], Y, Z) :- (member(H,Y);member(H,Z)),isDifference(T,Y,Z).
