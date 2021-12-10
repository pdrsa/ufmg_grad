fun 
sum([], []) = [] |
sum(hx::tx, hy::ty) = [hx+hy] @ sum(tx,ty);

sum([2, 5, 10], [1, 15, 4]);