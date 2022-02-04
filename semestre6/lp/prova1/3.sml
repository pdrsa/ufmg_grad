fun f([])   = false |
	f(x::t) = if(x mod 2 = 0) then true else f(t);