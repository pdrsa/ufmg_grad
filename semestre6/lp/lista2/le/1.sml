datatype expr = 
IConst of int | 
Plus of expr * expr | 
Minus of expr * expr|
Multi of expr * expr|
Div of expr * expr  |
Max of expr * expr  |
Min of expr * expr  |
Eq  of expr * expr  |
Gt  of expr * expr;

fun 
eval(IConst x) = x |

eval(Plus(x, y)) = eval(x) + eval(y) |

eval(Minus(x, y)) = eval(x) - eval(y) |

eval(Multi(x, y)) = eval(x) * eval(y) |

eval(Div(x, y)) = 
if eval(y) = 0 then 0
else eval(x) div eval(y) |

eval(Max(x, y)) = 
if eval(x) > eval(y) then eval(x)
else eval(y) |

eval(Min(x, y)) = 
if eval(x) < eval(y) then eval(x)
else eval(y) |

eval(Eq(x, y)) = 
if eval(x) = eval(y) then 1
else 0 |

eval(Gt(x, y)) = 
if eval(x) > eval(y) then 1
else 0;

(*------------

val e2 = Div(Multi(IConst(5), IConst(4)), Minus(IConst(4), IConst (4)));

-------------*)