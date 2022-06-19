hasBigger([X],   M) :- X > M.
hasBigger([X|T], M) :- X > M; hasBigger(T, M).

maxList([X],   M) :- X = M.
maxList([H|T], M) :- (not(hasBigger(T, H)) , M = H); maxList(T, M).
