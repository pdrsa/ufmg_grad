datatype UnOp = Not;

datatype BinOp = Add | Sub | Mul | Gt | Eq | Or;

datatype Sexpr = IConst of int | Op1 of UnOp * Sexpr | Op2 of BinOp * Sexpr
* Sexpr;


fun
(* Rule 1 *)
simplify(Op2(Add, IConst 0, e)) =
simplify(e) |

(* Rule 2 *)
simplify(Op2(Add, e, IConst 0)) =
simplify(e) |

(* Rule 3 *)
simplify(Op2(Sub, e, IConst 0)) =
simplify(e) |

(* Rule 4 *)
simplify(Op2(Mul, IConst 1, e)) =
simplify(e) |

(* Rule 5 *)
simplify(Op2(Mul, e, IConst 1)) =
simplify(e) |

(* Rule 6 *)
simplify(Op2(Mul, IConst 0, e)) =
IConst 0 |

(* Rule 7 *)
simplify(Op2(Mul, e, IConst 0)) =
IConst 0 |

(* Rule 8 *)
simplify(Op2(Sub, e1, e2)) =
if e1 = e2 
then IConst(0)
else Op2(Sub, e1, e2)|

(* Rule 9 *)
simplify(Op2(Or, e1, e2)) =
if e1 = e2 
then simplify(e1)
else Op2(Or, e1, e2) |

(* Rule 10 *)
simplify(Op1(
Not, 
Op1(Not, e)
)) = 
simplify(e) |

(* Remainder Rules *)

simplify(Op2(O, x, y)) = 
if 
simplify(x) = x andalso simplify(y) = y
then Op2(O, x, y) 
else simplify(
Op2(O, simplify(x), simplify (y))
) |

simplify(Op1(O, x)) =
if
simplify(x) = x
then Op1(O, x)
else
simplify(Op1(O, simplify(x))) |

simplify(e) = e;