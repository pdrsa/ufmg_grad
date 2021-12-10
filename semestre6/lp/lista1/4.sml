fun max(x::y::t) = 
if x > y then max(x::t)
else max(y::t) |
max(x::xs) = x;

max([2, 1, 7, 3]);
max([2, 3, 4]);
max([2]);
max([~3, ~5, ~9]);