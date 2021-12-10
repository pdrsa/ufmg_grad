fun
cumSum(x::y::t) = [x] @ cumSum(x+y::t) |
cumSum(x::t) = [x];

cumSum([6, 10, 3, 11]);